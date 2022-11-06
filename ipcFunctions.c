#include "ipcFunctions.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct message_type{
   long type;
   int action;
}ipcMessage;

int semaphoreWait(int semid, int semindex){
   struct sembuf sops[1];
   int result;
   sops[0].sem_num = semindex;
   sops[0].sem_op = -1;
   sops[0].sem_flg = 0;

   if( -1 == (result = semop(semid,sops,1))){
      perror("wait -> semop error");
      return -1;
   }
   return result;
}

int semaphoreSignal(int semid, int semindex){
   struct sembuf sops[1];
   int result;

   sops[0].sem_num = semindex;
   sops[0].sem_op = 1;
   sops[0].sem_flg = 0;

   if( -1 == (result = semop(semid,sops,1))){
      perror("signal -> semop error");
      return -1;
   }
   return result;
}


int messageSend(long type, int action, int messageBox){
   ipcMessage message;
   int send;
   message.type=1;
   message.action=0;
   send = msgsnd(messageBox,&message,sizeof(ipcMessage) - sizeof(long),0);
   if(send == -1){
      perror("error sending message");
      return -1;
   }
   return send;
}

ipcMessage messageRecieve(int messageBox){
   int sent;
   ipcMessage message;

   sent = msgrcv(messageBox,&message,sizeof(ipcMessage) - sizeof(long),0,IPC_NOWAIT);
   if(sent == -1){
      perror("Error recieving message");
      exit(sent);
   }
   return message;
}
