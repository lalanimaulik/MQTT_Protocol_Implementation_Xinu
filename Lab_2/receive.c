/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	restore(mask);
	return msg;
}


/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32  receiveMsg(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg32 msg;			/* Message to return		*/
	
	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {	
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	
	int32 tail = prptr -> prtail;
	int32 head = prptr->prhead;
		
	head = head +1;	
	prptr->prhead =head;	
	if(head == tail){
		prptr->prhasmsg = FALSE;	/* Reset message     flag*/			
	}	
	msg = prptr->prmsgarray[head];	
	
	restore(mask);
	return msg;
}

syscall receiveMsgs(umsg32* msgs, uint32 msg_count){

	umsg32 msg[11] = {};

	int32 i;
	for(i=0;i<msg_count;i++){	
		msgs[i]=receiveMsg();			

	}		
}




