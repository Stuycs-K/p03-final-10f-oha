#include "editor.h"
int main(int argc, char *argv[]){
  char * filename = argv[1];
  int openfile = open(filename, O_RDWR | O_CREAT, 0666);
  if(openfile < 0){
    err();
  )
  struct stat
  stat(filename, )
  int readfile = read(openfile, )
}
