/*  main.c  - main */

#include <xinu.h>


int32 head, tail;
pid32 *pids;

sid32 empty,full,mutex,mutex_receive;


//Function to test sendMsg()
process sendMessage(pid32 receiveMessage_id)
{
	umsg32 msg = 1;
	
	sendMsg(receiveMessage_id, msg);
	
	msg= 2 ;
	sendMsg(receiveMessage_id, msg);
	
	msg= 3 ;
	sendMsg(receiveMessage_id, msg);
	
	msg= 4 ;
	sendMsg(receiveMessage_id, msg);
	
}

//Function to test receiveMsg()
process receiveMessage()
{

	wait(mutex);
	int32 msg;
	msg = receiveMsg();
	printf("message: %d received in function receiveMsg()\n ", msg);
	msg = receiveMsg();
	printf("message: %d received in function receiveMsg()\n ", msg);
	msg = receiveMsg();
	printf("message: %d received in function receiveMsg()\n ", msg);	
	msg = receiveMsg();	
	printf("message: %d received in function receiveMsg()\n ", msg);
	signal(mutex);

}


// function to test sendnMsg()
// Sending messages to receiveMessageB and receiveMessageB1
process sendMessageB()
{
	umsg32 msg = 1;
	uint32 count = sendnMsg(2,pids,msg);
	wait(mutex);
	printf("Number of successful messages sent from sendnMsg() is : %d\n", count);
	signal(mutex);	
}

//function to test sendnMsg()
//receive message from sendMessageB
process receiveMessageB()
{
	umsg32 msg ;
	msg = receive();
	wait(mutex);
	printf("received message %d for process id: %d\n in function receive()",msg, getpid());
	signal(mutex);
}

//function to test sendnMsg()
//receive message from sendMessageB
process receiveMessageB1()
{
	umsg32 msg ;
	msg = receive();
	wait(mutex);
	printf("received message %d for process id: %d\n in function receive()",msg, getpid());
	signal(mutex);
}

//Function to test sendMsgs()
//sending multiple messages to receiveMessageMultiple
process sendMessageMultiple(pid32 receiveMessageMultiple_id){

	umsg32 *msgs;
	umsg32 temp[16] = {1,2};
	uint32 r;
	
	msgs = (umsg32 *)&temp;
	r=sendMsgs(receiveMessageMultiple_id,msgs,2);
	wait(mutex);
	printf("Total number of success for function sendMsgs() is  %d \n",r);
	signal(mutex);
}

//receive multiple messages from sendMessageMultiple
process receiveMessageMultiple(){
	
	//umsg32 msg = receiveMsg();
	//printf("Received message: %d\n",msg);

//	msg = receiveMsg();
//	printf("Received message: %d\n",msg);
	sleep(5);
	umsg32 *msgs;
	umsg32 temp[16] = {};
	msgs = (umsg32 *)&temp;
	receiveMsgs(msgs,2);
	uint32 i;
	for(i=0;i<2;i++){
		printf("Messages received in function receivedMsgs() %d\n", msgs[i]);
	}
}

process	main(void)
{

	pid32 sendMessage_id;
	pid32 receiveMessage_id;
	pid32 sendMessage_idB;
	pid32 receiveMessage_idB;
	pid32 receiveMessage_idB1;
	pid32 sendMessageMultiple_id;
	pid32 receiveMessageMultiple_id;
	recvclr();
	
	mutex = semcreate(1);

	receiveMessage_id= create(receiveMessage, 4096, 40, "receiveMessage",0);
	sendMessage_id= create(sendMessage, 4096, 40, 		"sendMessage",1,receiveMessage_id);
		
	//////////////
	
	receiveMessageMultiple_id = create(receiveMessageMultiple, 4096, 40, 		"sendMessageMultiple",0);

	sendMessageMultiple_id= create(sendMessageMultiple, 4096, 40, 		"sendMessageMultiple",1,receiveMessageMultiple_id);	

	// For sendMsgs() and receiveMsgs()
	resume(receiveMessageMultiple_id);
	resume(sendMessageMultiple_id);

	//Part B

	sendMessage_idB= create(sendMessageB, 4096, 40, "sendMessageB",0);
	receiveMessage_idB= create(receiveMessageB, 4096, 40, "receiveMessageB",0);
	receiveMessage_idB1= create(receiveMessageB1, 4096, 40, "receiveMessageB1",0);
	pid32 temp[10] = {};

	pids = (pid32 *)&temp;
	pids[0] = receiveMessage_idB;
	pids[1] = receiveMessage_idB1;
	//For sendnMsg()
	resume(receiveMessage_idB);
	resume(receiveMessage_idB1);
	resume(sendMessage_idB);
	//For sendMsgs() and receiveMsgs()
	resume(receiveMessage_id);
	resume(sendMessage_id);

	return OK;
}
