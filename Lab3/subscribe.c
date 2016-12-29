#include <xinu.h>

syscall subscribe(topic16 topic, void (*handler)(topic16, uint32)){

	intmask	mask;			
	struct	topics *topicptr;	


	mask = disable();
	
	if (isbadtopic(topic)) {
		restore(mask);
		return SYSERR;
	}

	topicptr = &topicTable[topic];
	topicptr->pids[topicptr->index] = currpid; 
	topicptr->handler[topicptr->index] =  (*handler);
	topicptr->index = topicptr->index +1;
	
	restore(mask);
	return OK;
}
