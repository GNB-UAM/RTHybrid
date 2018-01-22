#include "../includes/queue_functions.h"


/*int open_queue (void ** msqid) {
	int ret = 0;
	key_t key_q;

	*msqid = (void *)malloc(sizeof(int));

	key_q = ftok("/bin/ls", 28);
    if (key_q == (key_t) -1) {
        perror("Error obtaining message queue key.");
        return ERR;
    }

    ret = msgget(key_q, 0600 | IPC_CREAT);
    *(int*)(*msqid) = ret;
    if (ret == -1) {
        perror("Error obtaining message queue ID.");
        return ERR;
    }

    return OK;
}

int send_to_queue (void * msqid, message * msg) {
	int id = *(int*)msqid;

	if (msgsnd(id, (struct msgbuf *) msg, sizeof((*msg)) - sizeof(long), IPC_NOWAIT) == -1) {
		return ERR;
	}

	return OK;
}



int receive_from_queue (void * msqid, message * msg) {
	int id = *(int*)msqid;

	if (msgrcv(id, (struct msgbuf *) msg, sizeof((*msg)) - sizeof(long), 1, 0) == -1) {
		return ERR;
	}

	return OK;
}

int close_queue (void ** msqid) {
	int id = *(int*)(*msqid);


	if (msgctl(id, IPC_RMID, (struct msqid_ds *)NULL) != 0) {
		return ERR;
	}

	free(*msqid);

	return OK;
}*/


int integer_length (pid_t id) {
    int count = 0;

    while(id != 0)
    {
        id /= 10;
        ++count;
    }

    return count;

}


int open_queue (void ** msqid) {
	mqd_t id;
	struct mq_attr attr, *attrp;
    int size = integer_length(getpid()) + 10;
	char name[size];

    sprintf(name, "/rt_queue%d", getpid());

	attrp = NULL;
    attr.mq_maxmsg = 2000;
    attr.mq_msgsize = sizeof(message);
    attrp = &attr;

	//id = mq_open("rt_queue", O_CREAT|O_RDWR|O_NONBLOCK, S_IRWXU, attrp);
	id = mq_open(name, O_CREAT | O_RDWR | O_NONBLOCK, 0666, attrp);

	if (id == -1) {
		perror("Error opening queue");
		return ERR;
	}

	*msqid = (void *)malloc(sizeof(mqd_t));
	*(mqd_t*)(*msqid) = id;

    return OK;
}

int send_to_queue (void * msqid, message * msg) {
	mqd_t id = *(mqd_t*)msqid;

	if (mq_send(id, (const char *) msg, sizeof(*msg), 0) == -1) {
		//perror("Error sending message to queue");
		return ERR;
	}

	return OK;
}



int receive_from_queue (void * msqid, message * msg) {
	mqd_t id = *(mqd_t*)msqid;

	while(1) {
		if (mq_receive(id, (char *) msg, sizeof(*msg), 0) != -1) {
			break;
		}
	}

	return OK;
}

int close_queue (void ** msqid) {
	mqd_t id = *(mqd_t*)(*msqid);
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

	free(*msqid);

	return OK;
}
