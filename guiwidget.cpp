#include "guiwidget.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>

GuiWidget::GuiWidget(QWidget *parent)
    : QWidget(parent)
{
    this->initUi();
    this->setFixedSize(640,480);
    QFile read("://css/style.css");
    if(read.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&read);
        this->setStyleSheet(stream.readAll());
        read.close();
    }


}

GuiWidget::~GuiWidget()
{
}

void GuiWidget::cBox_versionAddItems()
{
    QStringList qtVer_list =  findQtPath.getQtAllVer();
    cBox_version->addItems(qtVer_list);
}

void GuiWidget::cBox_kitsAddItems(const QString& qtVer)
{
    //根据版本选择框选择的版本，添加编译套件
    QStringList qtCompiler_list = findQtPath.getQtCompileKits(qtVer);
    cBox_kits->addItems(qtCompiler_list);
}

void GuiWidget::On_cBox_version_Change()
{
    //改变Qt版本，编译套件需要重新检测并添加
    cBox_kits->clear();
    cBox_kitsAddItems(cBox_version->currentText());
}

void GuiWidget::On_btn_deploy_clicked()
{
    QString  WindePloyQtPath= findQtPath.getWindePloyQtPath(cBox_version->currentText(),cBox_kits->currentText());
    cout<<WindePloyQtPath;
    int ret = findQtPath.ApplicationPackage(WindePloyQtPath,deployfilePath);
    if(ret)
    {
        cout<<"打包成功";
    }
}

void GuiWidget::On_btn_openFile_clicked()
{
    //获取待打包文件的全路径
    QString title ="选择"+cBox_version->currentText()+"生成的exe";
    deployfilePath = QFileDialog::getOpenFileName(this,title,"./","Exe(*.exe);;All(*.*)");
    cout<<deployfilePath;
}
void GuiWidget::initUi()
{
    cBox_version = new QComboBox(this);
    cBox_kits = new QComboBox(this);

    cBox_version->move(150,20);
    cBox_kits->move(150,80);

    btn_deploy = new QPushButton("生成",this);
    btn_deploy->move(this->width()-200,this->height()-100);

    btn_openFile = new QPushButton("选择要打包的exe",this);
    btn_openFile->move(this->width()/2,this->height()/2);

    //先设置版本
    cBox_versionAddItems();
    //通过第一个版本设置编译套件
    cBox_kitsAddItems(cBox_version->currentText());


    connect(cBox_version,&QComboBox::currentTextChanged,this,&GuiWidget::On_cBox_version_Change);
    connect(btn_deploy,&QPushButton::clicked,this,&GuiWidget::On_btn_deploy_clicked);
    connect(btn_openFile,&QPushButton::clicked,this,&GuiWidget::On_btn_openFile_clicked);

}
