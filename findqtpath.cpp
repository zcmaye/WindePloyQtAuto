#include "findqtpath.h"
#include<QProcess>
FindQtPath::FindQtPath()
{
    startMenu = getStartMenuPath();
    cout<<startMenu;
}

QString FindQtPath::getStartMenuPath()
{
    return QDir::homePath()+ "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs";
}

QStringList FindQtPath::getQtAllVer()
{
    QDir dir(startMenu);
    QStringList dir_list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    //获取所有的Qt版本
    QStringList qtVer_list;
    for(QString dir : dir_list)
    {
        if(dir.left(2) == "Qt")
        {
            qtVer_list.push_back(dir);
        }
    }
    return qtVer_list;
}

QStringList FindQtPath::getQtCompileKits(const QString &qtVer)
{
    QDir dir(startMenu);
    //进入$startMenu/Qt 5.14.2/5.14.2
    bool ret = dir.cd(qtVer + "/" + qtVer.mid(3));
    if(!ret)
    {
        cout<<"[error]"<<"进入Qt快捷方式目录失败~";
        return QStringList();
    }
    //获取5.14.2目录下面所有的目录
    QStringList compilerKits = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    return compilerKits;
}

QString FindQtPath::getWindePloyQtPath(const QString& qtVer,const QString& compilerKit)
{
    QDir dir(startMenu);
    //进入$startMenu/Qt 5.14.2/5.14.2/MinGW 7.3.0 (64-bit)
    bool ret = dir.cd(qtVer + "/" + qtVer.mid(3) + "/" + compilerKit);
    if(!ret)
    {
        return QString();
    }
    //获取$startMenu/Qt 5.14.2/5.14.2/MinGW 7.3.0 (64-bit)下面的文件
    QStringList dir_list = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
//    for(QString val : dir_list)
//    {
//        cout<<val;
//    }
    //随便找一个快捷方式，进入快捷方式指向的目录
    QFileInfo info(dir.path() + "/" + dir_list.first());
    if(!info.isSymLink())
    {
        return QString();
    }
    QDir qtPath = info.symLinkTarget();
    qtPath.cdUp();
    QString windeploayPath = qtPath.path() + "/windeployqt.exe";

    return windeploayPath;
}

bool FindQtPath::ApplicationPackage(const QString& windeployqt,const QString &exeFile)
{
    QProcess process;
    process.start(windeployqt,QStringList(exeFile));
    if(!process.waitForStarted())
    {
        //cout<<"[process start error]"<<process.readAllStandardError().toStdString().data();
        cout<<"[error]"<<process.errorString();
        return false;
    }
    if(process.waitForFinished())
    {
        cout<<"[esult output]"<<process.errorString()<<" "<<process.exitCode()<<"  "
           <<process.exitStatus()<<" "<<process.error();
    }
    cout<<"[result output]"<<process.readAllStandardOutput().toStdString().data();
    cout<<"[process start error]"<<process.readAllStandardError().toStdString().data();
    return true;
}
