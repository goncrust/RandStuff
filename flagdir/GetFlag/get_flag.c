#include <stdio.h>
#include <unistd.h>
#include <string.h>

void winner() {

  puts("Congratulations");

}


void pass2(char *buffer) {

  char *command = buffer+10;

  system(command);

}


void pass1(char *buffer) {

  if (strncmp(buffer, "iamahacker", 10) == 0) {
    pass2(buffer);
  } else {
    puts("try again");    
  }

}


int main() {
  
  char buffer[64];
  read(0, buffer, 64);

  pass1(buffer);

}
