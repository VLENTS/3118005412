#ifndef MAIN_H
#define MAIN_H

#include <io.h>
#include <direct.h>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <codecvt>
#include <vector>
#include <ctime>
#include <string>

std::wstring UTF8ToUnicode(const std::string& str);
void build(int n);
void mod(int x, int y, int n);
int ask(int x);
void init();
int dp();
bool check(int argc, char* argv[]);
void CreatDir(std::string dir);
double solve(int argc, char* argv[]);

#endif // !MAIN_H
