#include "editor.h"
int main(int argc, char *argv[]){
  char * filename = argv[1];
  int openfile = open(filename, O_RDWR | O_CREAT, 0666);
  if(openfile < 0){
    err();
  )
  int readfile = read(openfile, )
}
