#ifndef FASTBIN_H
#define FASTBIN_H

#pragma once
#include <QApplication>
#include <iostream>
#include <string>
#include <QDebug>
#include <QUrl>
#include <QString>
#include <fstream>
#include <windows.h>
#include <QIcon>
#include <QFileIconProvider>
#include <QDir>
#include <QDesktopServices>
#include <QSettings>


#define MAX_BUF 1024

struct SoftInfo{
    QString name;
    QString path;
    QIcon icon;
};

class FastBin{
public:
    bool LoadPro(QString Path, bool searchFromLnk);
    bool runPro(QString Path);
    QString topy(QString qsChinese);
    std::vector<SoftInfo> findPro(QString ProName);
private:
    bool searchDir(QString sPath);
public:
    std::vector<SoftInfo> m_SoftInfo; //用于存储软件的信息
};



#endif // FASTBIN_H
