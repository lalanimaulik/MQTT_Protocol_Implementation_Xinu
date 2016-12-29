#include <xinu.h>

syscall unsubscribe(topic16 topic){

	intmask	mask;			
	struct	topics	*topicptr;	

	mask = disable();
	
	if (isbadtopic(topic)) {
		restore(mask);
		return SYSERR;
	}

	topicptr = &topicTable[topic];
	topicptr->pids[topicptr->index] = 0; 
	topicptr->handler[topicptr->index] =  NULL;
	topicptr->index = topicptr->index - 1;
	
	restore(mask);
}
