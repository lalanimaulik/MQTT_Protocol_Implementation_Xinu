# System_Calls_for_Xinu

This project was part of the Distributed Operating Systems course and was given as 3 lab assignments. For testing purposes, I installed Xinu on beagle bone black board. 


Lab 2: I have extended basic messaging system call and also created new ones in C language to send multiple messages to single receiver process and to send single message to multiple receiver processes keeping in mind the message queue, synchronization and overflow problem. 

System Calls: 

1. extern syscall sendMsg (pid32, umsg32); 

2. extern unit32 sendMsgs (pid32, umsg32*, uint32);

3. extern unit32 sendnMsg (uint32, pid32*, umsg32,); 

4. extern umsg32 receiveMsg (void); 

5. extern syscall receiveMsgs (umsg32*, unit32);



Lab 3: I have implemented MQTT messaging protocol for Xinu operating systems and created system calls for subscribe, unsubscribe and publish. Also created broker process to execute handlers for the given topic. Tables were used to store topics, handlers and messages.

1. syscall subscribe(topic16 topic, void (*handler)(topic16, uint32)); 

2. syscall unsubscribe(topic16 topic); 

3. syscall publish(topic16 topic, uint32 data);
