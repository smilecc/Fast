#ifndef FASTBIN_H
#define FASTBIN_H

#pragma once
#include <QApplication>
#include <iostream>
#include <string>
#include <QString>
#include <fstream>
#include <windows.h>

#include "atlbase.h"
#include "atlstr.h"

#pragma comment(lib,"Advapi32.lib")

#define MAX_BUF 1024

struct SoftInfo{
    QString name;
    QString path;
};

class FastBin{
public:

    void run(QString command);
    QString topy(QString qsChinese);
    bool LoadPro();
private:
    char convert(wchar_t n);
    bool In(wchar_t start, wchar_t end, wchar_t code);
    void searchDir(QString sPath);
public:
    std::vector<SoftInfo> m_SoftInfo;
};



#endif // FASTBIN_H
