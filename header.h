#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED
//Libraries
#include <bits/stdc++.h>
#include <filesystem>
#include <sys/stat.h>
#include<pwd.h>
#include <grp.h>
#include <termios.h>
#include <sys/ioctl.h>
#include<spawn.h>
#include<sys/wait.h>
#include <fstream>
using namespace std;
using namespace std::filesystem;
//External variables
extern char **environ;
//Constants
#define INVERTCOLOR "\033[7m"
#define RESETCOLOR "\033[0m"
#define CLEAR "\033c"
#define GREEN "\033[0;32m"
//function declaration
void openFile(string filename);
bool enterCommandMode();
void printDir(path p);

#endif
