#include "guiwidget.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>

GuiWidget::GuiWidget(QWidget *parent)
    : QWidget(parent)
{   
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFixedSize(640,480);
    this->initUi();
    this->setMouseTracking(true);
    this->setAcceptDrops(true);         //设置窗口支持拖拽
    this->setWindowTitle("Qt快速打包——公众号:C语言Plus");
    this->setWindowIcon(QIcon("://image/icon.png"));

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

void GuiWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void GuiWidget::dropEvent(QDropEvent *event)
{
   deployfilePath = event->mimeData()->urls().first().path();
   deployfilePath.remove(0,1);
   cout<<deployfilePath;
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

    label_version = new QLabel("选择Qt版本",this);
    label_kits = new QLabel("选择编译套件",this);

    btn_openFile = new QPushButton("拖拽/选择要打包的exe",this);
    btn_deploy = new QPushButton("生成",this);

    cBox_version->setGeometry(250,20,this->width()-280,35);
    cBox_kits->setGeometry(250,cBox_version->height()+25,this->width()-280,35);

    label_version->setGeometry(50,cBox_version->y(),200,35);
    label_kits->setGeometry(50,cBox_kits->y(),200,35);


    btn_openFile->setFixedSize(550,260);
    int x = (this->width()-btn_openFile->width())/2;
    int y = (this->height() - btn_openFile->height())/2;
    btn_openFile->move(x,y);

    btn_deploy->setFixedSize(200,35);
    int x1 = (this->width()-btn_deploy->width())/2;
    btn_deploy->move(x1,this->height()-btn_deploy->height()-20);
    //此处如果再style.css中设置无效，为啥？QPushButton#btn_deploy:hover{}
    btn_deploy->setStyleSheet("QPushButton:hover\
    {\
       background-color: aquamarine;\
    }");

    //先设置版本
    cBox_versionAddItems();
    //通过第一个版本设置编译套件
    cBox_kitsAddItems(cBox_version->currentText());


    connect(cBox_version,&QComboBox::currentTextChanged,this,&GuiWidget::On_cBox_version_Change);
    connect(btn_deploy,&QPushButton::clicked,this,&GuiWidget::On_btn_deploy_clicked);
    connect(btn_openFile,&QPushButton::clicked,this,&GuiWidget::On_btn_openFile_clicked);

}
