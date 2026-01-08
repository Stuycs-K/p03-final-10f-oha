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
int start(char * buff, struct stat *statbuff);
int movecursor(int x, int y, char **lines, int maxy, int ch);
int quit(char * buff, struct stat *statbuff);
#endif
