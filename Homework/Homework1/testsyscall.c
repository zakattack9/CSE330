#include<unistd.h>
#include<sys/syscall.h>

int main() {
  syscall(548);
  return 0;
}