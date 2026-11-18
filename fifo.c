 // writer
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

  const char *fifo = "/tmp/myfifo";

  // Create FIFO if it doesn't exist

  mkfifo(fifo, 0666);

  // Message to send
  const char *message = "Hello from writer process!";

  // Open FIFO for writing
  int fd = open(fifo, O_WRONLY);

  if (fd == -1) {
    perror("open writer");
    return 1;
  }

  // Write message to FIFO
  write(fd, message, strlen(message));

  // Close FIFO
  close(fd);

  return 0;
}
//reader 


#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

  const char *fifo = "/tmp/myfifo";

  mkfifo(fifo, 0666);

  char buf[100];

  int fd = open(fifo, O_RDONLY);

  if (fd == -1) {
    perror("open reader");
    return 1;
  }

  int n = read(fd, buf, sizeof(buf) - 1);

  printf("%d\n", n);

  if (n > 0) {
    buf[n] = '\0';

    printf("Reader got: %s\n", buf);
  }

  close(fd);

  return 0;
}

