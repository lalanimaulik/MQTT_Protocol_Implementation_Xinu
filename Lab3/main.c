/*  main.c  - main */

#include <xinu.h>

sid32 mutex;

//broker for Question 1
process broker(){
	
	while(TRUE){
	
		if(head ==NULL)
			suspend(bID);
		else{
			struct	topics	*topicptr;	
			struct	msgqueue *node;
			node = head;

			int32 i;
	
			topicptr = &topicTable[head-> topic];
			head = head-> next;	
		
			if(topicptr->index==0){
				wait(mutex);
				printf("NO data published");
				signal(mutex);
			}
			else{
				for(i=0; i<topicptr->index; i++){
    (*topicptr->handler[i]) (node->topic ,node->prmsg);				
				}
			}
			if(head==NULL)
				tail=NULL;
		}
	}

}

/*For question 2
process broker(){

while(TRUE){
	
		printf("In broker HEad");
		if(head ==NULL){
			printf("Head Null");
			suspend(bID);
		}
		else{
			struct	topics	*topicptr;	
			struct	msgqueue *node;
			node = head;
			head= head->next;
			int32 i;
			int32 j;
			topic16 forQ2=256;
			printf("In broker");
			if(node->topic<forQ2){
				printf("LESS THAN 256");
				for(j=0;j<256;j++){	
					topic16 newTopic = j*256 + node->topic;
					topicptr = &topicTable[newTopic];
					if(topicptr->index==0){
						wait(mutex);
						printf("NO data published");
						signal(mutex);
					}
					else{
						for(i=0; i<topicptr->index; i++){
						(*topicptr->handler[i]) (newTopic ,node->prmsg);				
						}
					}
				}
			}
			else{	
				printf("GREATER THAN 256");
				topicptr = &topicTable[node-> topic];	
		
				if(topicptr->index==0){
					wait(mutex);
					printf("NO data published");
					signal(mutex);
				}
				else{
					for(i=0; i<topicptr->index; i++){
	    (*topicptr->handler[i]) (node->topic ,node->prmsg);				
					}
				}
			}
			if(head==NULL)
				tail=NULL;
		}
	}

}

*/

void foo(topic16 t, uint32 data){

	wait(mutex);
	printf("Function foo() is called with topic %d and data %d\n",t,data);
	signal(mutex);
}

void bar(topic16 t, uint32 data){
	
	wait(mutex);
	printf("Function bar() is called with topic %d and data %d\n",t,data);
	signal(mutex);
}


process A(){

	subscribe(10, foo);
	wait(mutex);
	printf("Process A subscribed t topic %d and function foo() \n",10);
	signal(mutex);
	return OK;
}

process B(){

	publish(10,77);
	wait(mutex);
	printf("Process B published in topic %d and data %d\n",10, 77);
	signal(mutex);
	sleep(3);
	publish(10,42);
	wait(mutex);
	printf("Process B published in topic %d and data %d\n",10, 42);
	signal(mutex);
	return OK;
}

process C(){

	subscribe(10, bar);
	wait(mutex);
	printf("Process C subscribed t topic %d and bar\n",10);
	signal(mutex);	

	return OK;
}

process D(){

	
	publish(7,17);
	wait(mutex);
	printf("Process D published in topic %d and data %d\n",7, 17);
	signal(mutex);
	return OK;
}



process	main(void)
{


	bID= create(broker, 4096, 40, "broker",0);

	pid32 pidA = create(A, 4096, 40, "A",0);
	resume(pidA);
	
	pid32 pidB = create(B, 4096, 40, "B",0);
	resume(pidB);
	
	pid32 pidC = create(C, 4096, 40, "C",0);
	resume(pidC);
	
	pid32 pidD = create(D, 4096, 40, "D",0);
	resume(pidD);
	
	
	return OK;
}
