/**
 * @file xddp_functions.c
 * @brief Source file with functions to manage IPC between a Xenomai thread and a non real-time thread.
 */

#include "../includes/queue_functions.h"
#include <rtdm/ipc.h>


#define XDDP_PORT 0

unsigned static int first = 0;
static int fd_rt = -1;
static int fd_nrt = -1;

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
	if (open_queue_rt(rt_msqid) == ERR || open_queue_nrt(nrt_msqid) == ERR) return ERR;
}


/**
 * @brief Opens an IPC message queue.
 * @param[out] msqid Pointer to a void pointer that will be casted and filled to the queue descriptor type (mqd_t) and filled with the queue ID 
 * @return #OK if it works, #ERR if there is an error
 */

int open_queue_rt (void ** msqid) {
    struct sockaddr_ipc saddr;
    int ret, s, n = 0, len;
    size_t poolsz;


    if (first != 0) {
    	*msqid = (void *)malloc(sizeof(int));
		*(int*)(*msqid) = fd_rt;
 		return OK;  	
    }

	/*
	* Get a datagram socket to bind to the RT endpoint. Each
	* endpoint is represented by a port number within the XDDP
	* protocol namespace.
	*/
    s = socket(AF_RTIPC, SOCK_DGRAM, IPCPROTO_XDDP);
    if (s < 0) {
        perror("Error opening socket");
		return ERR;
    }


    /*
    * Set a local 16k pool for the RT endpoint. Memory needed to
    * convey datagrams will be pulled from this pool, instead of
    * Xenomai's system pool.
    */
    poolsz = 16384; /* bytes */
    ret = setsockopt(s, SOL_XDDP, XDDP_POOLSZ, &poolsz, sizeof(poolsz));
    if (ret) {
    	perror("Error setting socket");
		return ERR;
	}


    /*
    * Bind the socket to the port, to setup a proxy to channel
    * traffic to/from the Linux domain.
    *
    * saddr.sipc_port specifies the port number to use.
    */
    memset(&saddr, 0, sizeof(saddr));
    saddr.sipc_family = AF_RTIPC;
    saddr.sipc_port = XDDP_PORT;
    ret = bind(s, (struct sockaddr *)&saddr, sizeof(saddr));

    if (ret == -1) {
    	perror("Error binding socket");
		return ERR;
	}


    *msqid = (void *)malloc(sizeof(int));
	*(int*)(*msqid) = s;

	fd_rt = s;
	first = 1;

    return OK;
}


/**
 * @brief Opens an IPC message queue.
 * @param[out] msqid Pointer to a void pointer that will be casted and filled to the queue descriptor type (mqd_t) and filled with the queue ID 
 * @return #OK if it works, #ERR if there is an error
 */

int open_queue_nrt (void ** msqid) {
    int fd;

    if (first > 1) {
    	*msqid = (void *)malloc(sizeof(int));
		*(int*)(*msqid) = fd_nrt;
 		return OK;  	
    }

    char * devname;
    if (asprintf(&devname, "/dev/rtp%d", XDDP_PORT) < 0) {
    	perror("Error opening queue");
		return ERR;
    }
            
    fd = open(devname, O_RDWR);
    free(devname);
    if (fd < 0) {
    	perror("Error opening queue");
		return ERR;
	}

    *msqid = (void *)malloc(sizeof(int));
	*(int*)(*msqid) = fd;

	fd_nrt = fd;
	first = 2;

    return OK;
}


/**
 * @brief Sends a message to the queue pointed by msqid. It is non-blocking: if the queue is full, the message will not be sended and the function will continue.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int send_to_queue_rt_no_block (void * msqid, message * msg) {
	int id = *(int*)msqid;

    if (sendto(id, (const char *) msg, sizeof(*msg), MSG_DONTWAIT, NULL, 0) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}

	return OK;
}


/**
 * @brief Sends a message to the queue pointed by msqid. It is blocking: if the queue is full, the function will wait until the message can be sent.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int send_to_queue_rt_block (void * msqid, message * msg) {
	int id = *(int*)msqid;
	int ret = ERR;

	if (sendto(id, (const char *) msg, sizeof(*msg), 0, NULL, 0) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}

	return OK;
}


/**
 * @brief Sends a message to the queue pointed by msqid. It is non-blocking: if the queue is full, the message will not be sended and the function will continue.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int send_to_queue_nrt_no_block (void * msqid, message * msg) {
	int id = *(int*)msqid;

    /*if (sendto(id, (const char *) msg, sizeof(*msg), MSG_DONTWAIT, NULL, 0) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}*/

	return OK;
}


/**
 * @brief Sends a message to the queue pointed by msqid. It is blocking: if the queue is full, the function will wait until the message can be sent.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int send_to_queue_nrt_block (void * msqid, message * msg) {
	int id = *(int*)msqid;

    if (write(id, (char *) msg, sizeof(*msg)) <= 0) {
		//perror("Error sending message to queue");
		return ERR;
	}

	return OK;
}


/**
 * @brief Sends a message to the queue pointed by msqid. It is non-blocking: if the queue is full, the message will not be sended and the function will continue.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int receive_from_queue_rt_no_block (void * msqid, message * msg) {
	int id = *(int*)msqid;

    if (recvfrom(id, (const char *) msg, sizeof(*msg), MSG_DONTWAIT, NULL, 0) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}

	return OK;
}


/**
 * @brief Sends a message to the queue pointed by msqid. It is blocking: if the queue is full, the function will wait until the message can be sent.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int receive_from_queue_rt_block (void * msqid, message * msg) {
	int id = *(int*)msqid;

    if (recvfrom(id, (const char *) msg, sizeof(*msg), 0, NULL, 0) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}

	return OK;
}


/**
 * @brief Sends a message to the queue pointed by msqid. It is non-blocking: if the queue is full, the message will not be sended and the function will continue.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int receive_from_queue_nrt_no_block (void * msqid, message * msg) {
	int id = *(int*)msqid;

    /*if (sendto(id, (const char *) msg, sizeof(*msg), MSG_DONTWAIT, NULL, 0) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}*/

	return OK;
}


/**
 * @brief Sends a message to the queue pointed by msqid. It is blocking: if the queue is full, the function will wait until the message can be sent.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @param[in] msg Pointer to the message
 * @return #OK if it works, #ERR if there is an error inserting the message in the queue (e.g. the queue is full)
 */

int receive_from_queue_nrt_block (void * msqid, message * msg) {
	int id = *(int*)msqid;

    if (read(id, (char *) msg, sizeof(*msg)) <= 0) {
		perror("Error sending message to queue");
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

	if (is_rt == RT_QUEUE) {
		if (is_blocking == BLOCK_QUEUE) {
			ret = send_to_queue_rt_block (msqid, msg);
		} else if (is_blocking == NO_BLOCK_QUEUE) {
			ret = send_to_queue_rt_no_block (msqid, msg);
		}
	} else if (is_rt == NRT_QUEUE) {
		if (is_blocking == BLOCK_QUEUE) {
			ret = send_to_queue_nrt_block (msqid, msg);
		} else if (is_blocking == NO_BLOCK_QUEUE) {
			ret = send_to_queue_nrt_no_block (msqid, msg);
		}
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

	if (is_rt == RT_QUEUE) {
		if (is_blocking == BLOCK_QUEUE) {
			ret = receive_from_queue_rt_block (msqid, msg);
		} else if (is_blocking == NO_BLOCK_QUEUE) {
			ret = receive_from_queue_rt_no_block (msqid, msg);
		}
	} else if (is_rt == NRT_QUEUE) {
		if (is_blocking == BLOCK_QUEUE) {
			ret = receive_from_queue_nrt_block (msqid, msg);
		} else if (is_blocking == NO_BLOCK_QUEUE) {
			ret = receive_from_queue_nrt_no_block (msqid, msg);
		}
	}

	return ret;
}


/**
 * @brief Closes the queue pointed by msqid.
 * @param[in] msqid Pointer to the message queue descriptor 
 * @return #OK if it works, #ERR if there is an error
 */

int close_queue (void ** rt_msqid, void ** nrt_msqid) {
	int rt_id = *(int*) rt_msqid;
	int nrt_id = *(int*) nrt_msqid;

	//shutdown(rt_id, 2);
	//close(nrt_id);

	free(*rt_msqid);
	free(*nrt_msqid);

	return OK;
}