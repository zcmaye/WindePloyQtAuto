#ifndef FINDQTPATH_H
#define FINDQTPATH_H

#include<QString>
#include<QDir>
#include<QDebug>
#define cout qDebug()<<"line: "<<__LINE__
class FindQtPath
{
public:
    FindQtPath();
    QString getStartMenuPath();                                 //获取开始菜单的路径
    QStringList getQtAllVer();                                  //获取本机安装的所有Qt版本
    QStringList getQtCompileKits(const QString& qtVer);         //获取指定Qt版本的所有编译套件
    //根据指定的Qt版本和Qt编译套件，获取WindePloyQt.exe的全路径
    QString getWindePloyQtPath(const QString& qtVer,const QString& compilerKit);
    bool ApplicationPackage(const QString& windeployqt,const QString& exeFile);
private:
    QString startMenu;      //开始菜单目录
    QString qtSymLinkPath;  //保存这个目录 Start Menu\Programs\Qt 5.14.2\5.14.2\MinGW 7.3.0 (64-bit)
};

#endif // FINDQTPATH_H
