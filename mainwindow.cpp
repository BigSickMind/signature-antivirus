#include "mainwindow.h"
#include <string>
#include <fstream>
#include <scanner.h>
#include <cstdlib>
#include <QFileDialog>
#include "ui_mainwindow.h"

using namespace std;

string directory;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString convert = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "C:", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    directory = convert.toStdString();
    ui->label->setText(convert);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->insertPlainText("Start scanning\n");
    ui->textEdit->insertPlainText("\n");
    string com = "";
    ifstream in;
    string s = '"' + directory + '"';
    string str = s;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == 47)
            str[i] = 92;
    com += "dir " + s + " /S > tmp.txt";
    char c_pr;
    for (int i = 0; i < com.length(); i++)
        if (com[i]== ' ' && com[i+1] =='/' && com[i+2] =='S' && i!= 3)
        {
            c_pr = i;
            break;
        }
    for (int i = 0; i < c_pr; i++)
        if (com[i] == 47)
            com[i] = 92;
    system(com.c_str());

    in.open("tmp.txt");
    string file_name = "";
    string directory_copy = s;
    for (int i = 0; i < 5; i++)
        getline(in, file_name);
    int count = 0;
    while(count != 2)
    {
        getline(in, file_name);
        if (file_name == "")
        {
            count++;
            continue;
        }
        count = 0;\
        if (file_name.substr(18,2) == "D:" || file_name.substr(18,2) == "C:")
        {
            directory_copy = file_name.substr(18, file_name.length() - 18);
            s = '"' + directory_copy + '"';
        }
        if (file_name[0] != ' ')
        {
                if (file_name[21] != '<')
                {
                    file_name = file_name.substr(36, file_name.length() - 36);
                    str = s;
                    str.erase(s.length() - 1, 1);
                    str += "/";
                    str[s.length()-1] = 92;
                    str += file_name + '"';
                    string str_out = str;
                    //for (int i = 0; i < str.length(); i++)
                       //if (str[i] == 47)
                           //str[i] = 92;
                    for (int i = 0; i < str.length(); i++)
                       if (str[i] == 92)
                           str[i] = 47;
                    int res = scan(str);
                    if(res == 1)
                    {
                        ui->textEdit->insertPlainText("Problem!!!! Virus detected!\n");
                        ui->textEdit->insertPlainText("Path: ");
                        ui->textEdit->insertPlainText(str_out.c_str());
                        ui->textEdit->insertPlainText("\n");
                        ui->textEdit->insertPlainText("\n");
                    }
                }
        }
    }
    ui->textEdit->insertPlainText("Finish scanning\n");
    ui->textEdit->insertPlainText("\n");
    in.close();
}
