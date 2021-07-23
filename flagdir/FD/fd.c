#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

  if (argc > 1) {
  
    int arg = atoi(argv[1]);
    arg -= 4660; 
   
    char buffer[32];
    read(arg, buffer, 32);

    if (strncmp(buffer, "LETMEWIN", 8) == 0) {
      puts("good job :)");
      system("/bin/cat flag");
      exit(0);
    } else {
      puts("learn about Linux file IO");
    }
    
  } else {
    puts("pass argv[1] a number");
  }

}
