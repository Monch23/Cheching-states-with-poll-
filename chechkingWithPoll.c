#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/poll.h>
#include <stdlib.h>
#define TIMEOUT 3

int main() {
  const int descsCount = 6;
  struct pollfd fdescs[descsCount];
  int fd1, fd2, fd3, fd4, fd5, fd6;
  
  fd1 = open("1.txt", O_RDONLY);
  fd2 = open("2.txt", O_WRONLY);
  fd3 = open("3.txt", O_WRONLY);
  fd4 = open("4.txt", O_RDONLY);
  fd5 = open("5.txt", O_WRONLY);
  fd6 = open("6.txt", O_RDONLY);

  int fdsIndex = fd1;

  for (int i = 0; i < descsCount; ++i) {
    fdescs[i].fd = fdsIndex++;
  }

  fdescs[0].events = POLLIN; // fd1
  fdescs[1].events = POLLOUT; // fd2
  fdescs[2].events = POLLOUT; // fd3
  fdescs[3].events = POLLIN; // fd4
  fdescs[4].events = POLLOUT; // fd5
  fdescs[5].events = POLLIN; // fd6
  
  int pl = poll(fdescs, descsCount, TIMEOUT);
  if (pl < 0) {
    perror("poll()");
    return 1;
  }

  for (int i = 0; i < descsCount; ++i) {
    if (fdescs[i].revents & POLLIN) {
      printf("file with descriptor <%d> is readable \n", fdescs[i].fd);
    } else if (fdescs[i].revents & POLLOUT) {
      printf("file with descriptor <%d> is writable \n", fdescs[i].fd);
    } 
  }

  for (int i = 0; i < descsCount; ++i) {
    close(fd1++);
  }

  return 0;
}