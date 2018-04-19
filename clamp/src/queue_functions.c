/**
 * @file queue_functions.c
 * @brief Source file with functions to manage POSIX IPC message queues.
 */

#include "../includes/queue_functions.h"
#include <mqueue.h>


/**
 * @brief Returns the number of digits of a process ID.
 * @param[in] id Process ID
 * @return Number of digits of the ID
 */

int integer_length (pid_t id) {
    int count = 0;

    while(id != 0)
    {
        id /= 10;
        ++count;
    }

    return count;

}


/**
 * @brief Opens an IPC message queue that can be used both in real-time and non real-time environments
 * @param[out] rt_msqid Pointer to a void pointer that will be casted and filled to the queue descriptor type and filled with the queue real-time end ID
 * @param[out] nrt_msqid Pointer to a void pointer that will be casted and filled to the queue descriptor type and filled with the queue non real-time ID 
 * @return #OK if it works, #ERR if there is an error
 */

int open_queue (void ** rt_msqid, void ** nrt_msqid) {
	if (open_queue_rt(rt_msqid) == ERR) return ERR;

	*nrt_msqid = *rt_msqid;

	return OK;
}


/**
 * @brief Opens an IPC message queue.
 * @param[out] msqid Pointer to a void pointer that will be casted and filled to the queue descriptor type (mqd_t) and filled with the queue ID 
 * @return #OK if it works, #ERR if there is an error
 */

int open_queue_rt (void ** msqid) {
	mqd_t id;
	struct mq_attr attr, *attrp;
    int size = integer_length(getpid()) + 10;
	char name[size];

    sprintf(name, "/rt_queue%d", getpid());

	attrp = NULL;
    attr.mq_maxmsg = 2000;
    attr.mq_msgsize = sizeof(message);
    attrp = &attr;

    id = mq_open(name, O_CREAT | O_RDWR, 0666, attrp);

	if (id == -1) {
		perror("Error opening queue");
		return ERR;
	}

	*msqid = (void *)malloc(sizeof(mqd_t));
	*(mqd_t*)(*msqid) = id;

    return OK;
}



/**
 * @brief Sends a message to the queue pointed by msqid. It is non-blocking: if the queue is full, the message will not be sended and the function will continue.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int send_to_queue_no_block (void * msqid, message * msg) {
	mqd_t id = *(mqd_t*)msqid;
    struct timespec ts1;

    clock_gettime(CLOCK_MONOTONIC, &ts1);

    if (mq_timedsend(id, (const char *) msg, sizeof(*msg), 0, &ts1) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}

	return OK;
}

/**
 * @brief Sends a message to the queue pointed by msqid. It is non-blocking: if the queue is full, the functions will wait until the message can be send.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int send_to_queue_block (void * msqid, message * msg) {
	mqd_t id = *(mqd_t*)msqid;

    if (mq_send(id, (const char *) msg, sizeof(*msg), 0) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}

	return OK;
}


/**
 * @brief Receives a message from the queue pointed by msqid. It is non blocking: if the queue is empty the function will continue.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[out] msg Pointer where the message will be stored
 * @return #OK if it works, #ERR if there is an error
 */

int receive_from_queue_no_block (void * msqid, message * msg) {
	mqd_t id = *(mqd_t*)msqid;
	struct timespec ts1;

    clock_gettime(CLOCK_MONOTONIC, &ts1);

    if (mq_timedreceive(id, (char *) msg, sizeof(*msg), NULL, &ts1) < 0) {
        //perror("Error receiving message in queue");
        return ERR;
    }

	return OK;
}

/**
 * @brief Receives a message from the queue pointed by msqid. It is blocking: if the queue is empty, the functions will wait until there is a message.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[out] msg Pointer where the message will be stored
 * @return #OK if it works, #ERR if there is an error
 */

int receive_from_queue_block (void * msqid, message * msg) {
	mqd_t id = *(mqd_t*)msqid;

    if (mq_receive(id, (char *) msg, sizeof(*msg), NULL) < 0) {
        perror("Error receiving message in queue");
        return ERR;
    }

	return OK;
}




/**
 * @brief Sends a message to the queue pointed by msqid.
 * @param[in] msqid Pointer to the message queue descriptor
 * @param[in] is_rt Specifies if the queue is working in a real-time (RT_QUEUE) or non real-time (NRT_QUEUE) environment
 * @param[in] is_blocking Specifies if the function must block (BLOCK_QUEUE) or not (NO_BLOCK_QUEUE) when the queue is full
 * @param[in] msg Pointer to the message to be sent
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int send_to_queue (void * msqid, unsigned int is_rt, unsigned int is_blocking, message * msg) {
	int ret = ERR;

	if (is_blocking == BLOCK_QUEUE) {
		ret = send_to_queue_block (msqid, msg);
	} else if (is_blocking == NO_BLOCK_QUEUE) {
		ret = send_to_queue_no_block (msqid, msg);
	}

	return ret;
}


/**
 * @brief Sends a message to the queue pointed by msqid.
 * @param[in] msqid Pointer to the message queue descriptor
 * @param[in] is_rt Specifies if the queue is working in a real-time (RT_QUEUE) or non real-time (NRT_QUEUE) environment
 * @param[in] is_blocking Specifies if the function must block (BLOCK_QUEUE) or not (NO_BLOCK_QUEUE) when the queue is full
 * @param[in] msg Pointer to the message to be sent
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int receive_from_queue (void * msqid, unsigned int is_rt, unsigned int is_blocking, message * msg) {
	int ret = ERR;

	if (is_blocking == BLOCK_QUEUE) {
		ret = receive_from_queue_block (msqid, msg);
	} else if (is_blocking == NO_BLOCK_QUEUE) {
		ret = receive_from_queue_no_block (msqid, msg);
	}

	return ret;
}


/**
 * @brief Closes the queue pointed by msqid.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @return #OK if it works, #ERR if there is an error
 */

int close_queue (void ** rt_msqid, void ** nrt_msqid) {
	mqd_t id = *(mqd_t*)(*rt_msqid);
	int size = 11 + sizeof(pid_t);
	char name[size];

    sprintf(name, "/rt_queue%d", getpid());

	printf("Closing queue with id: %d\n", id);


	if (mq_close(id) != 0) {
		perror("Error closing queue");
		return ERR;
	}

	if (mq_unlink(name) != 0) {
		perror("Error removing queue");
		return ERR;
	}

	free(*rt_msqid);

	return OK;
}
