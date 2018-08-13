#include <string>
#include <limits>
#include <fstream>
#ifndef SCANNER_H
#define SCANNER_H

using namespace std;

int scan(string file_name);
fstream& GotoLine(fstream& file, unsigned int num);

#endif // SCANNER_H
