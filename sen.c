// message queue

// rec
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_TEXT 512
#define QUEUE_KEY 1234
// Message structure
struct msg_buffer {
  long msg_type;
  char msg_text[MAX_TEXT];
};
int main() {
  int msgid;
  // Create or get the message queue
  msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
  if (msgid == -1) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }
  struct msg_buffer message;
  printf("Waiting for a message...\n");
  // Receive message of type 1
  if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
    perror("msgrcv");
    exit(EXIT_FAILURE);
  }
  printf("Received message: %s\n", message.msg_text);
  // Delete the queue after receiving the message
  if (msgctl(msgid, IPC_RMID, NULL) == -1) {
    perror("msgctl (IPC_RMID)");
    exit(EXIT_FAILURE);
  }
  printf("Message queue deleted.\n");
  return 0;
}

// sen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_TEXT 512
#define QUEUE_KEY 1234
// Define the message buffer structure (same as receiver)
struct msg_buffer {
  long msg_type;
  char msg_text[MAX_TEXT];
};
int main() {
  int msgid;
  // Get the message queue (must exist)
  msgid = msgget(QUEUE_KEY, 0666);
  if (msgid == -1) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }
  struct msg_buffer message;
  message.msg_type = 1; // Required by System V
  printf("Enter message to send: ");
  if (fgets(message.msg_text, MAX_TEXT, stdin) == NULL) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }
  // Send the message (excluding msg_type size)
  if (msgsnd(msgid, &message, strlen(message.msg_text) + 1, 0) == -1) {
    perror("msgsnd");
    exit(EXIT_FAILURE);
  }
  printf("Message sent: %s\n", message.msg_text);
  return 0;
}
