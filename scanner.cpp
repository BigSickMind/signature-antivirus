#include <dirent.h>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

fstream& Line(fstream& file, int num){
    file.seekg(ios::beg);
    string skip;
    for(int i = 0; i < num - 1; i++)
        getline(file, skip);
    return file;
}

int scan(string file_name)
{
    pair<int, int> flag = make_pair(0,0);
    fstream in, inpt;
    inpt.open(file_name);
    if(inpt.is_open())
    {
        in.open("VirusBase.txt");

        for(;;)
        {
            string pattern = "";
            in >> pattern;
            if(pattern == "<-")
            {
                in >> pattern;
                if(pattern == "End")
                {
                    inpt.close();
                    in.close();
                    return -1;
                }
                else
                    if(pattern == "virus")
                    {
                        if(flag.first >= (flag.second * 3 + 1) / 2)
                        {
                            inpt.close();
                            in.close();
                            return 1;
                        }
                        else
                        {
                            flag = make_pair(0,0);
                            continue;
                        }
                    }
            }
            else
                if(pattern == "Line")
                {
                    flag.second++;
                    int linenum = 0;
                    in >> linenum;
                    Line(inpt, linenum);
                    string line;
                    getline(inpt, line);
                    for(int j = 0; j < 3; j++)
                    {
                        int colnum;
                        char file_ch;
                        in >> colnum;
                        in >> file_ch;
                        if(file_ch == line[colnum - 1])
                            flag.first++;
                    }
                }
        }
    }
    else
        return 0;
    inpt.close();
    in.close();
}
