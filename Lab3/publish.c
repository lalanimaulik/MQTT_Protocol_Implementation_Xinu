#include <xinu.h>

syscall publish(topic16 topic, uint32 data){
	
	intmask	mask;			
	struct	msgqueue *queue= getmem(10);	
	
	mask = disable();
	
	if (isbadtopic(topic)) {
		restore(mask);
		return SYSERR;
	}
	
	queue-> prmsg = data;
	queue-> topic = topic;
	queue-> next = NULL;
	
	if(tail==NULL){
		head = queue;
		tail = queue;
	}
	else{
		tail = queue;
		tail = tail->next ;
		
	}
	resume(bID);
	restore(mask);
}
