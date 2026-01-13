#ifndef EDITOR_H
#define EDITOR_H
#include <stdio.h>
#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
int err();
int start(char * buff, int size);
int movecursor(int x, int y, char **lines, int maxy, int ch);
int quit(char * buff, int size, int fd, char * filename);
char * insert(char * line, int i, char ch);
char * getnewbuff(char ** lines, int size, int buffsize);
char * deletech(char * line, int i);
char ** enterkey(char ** lines, int y, int x, int size);
#endif
