#ifndef GUIWIDGET_H
#define GUIWIDGET_H

#include <QWidget>
#include<QComboBox>
#include<QLabel>
#include<QPushButton>
#include"findqtpath.h"

#include<QDragEnterEvent>
#include<QDropEvent>
#include<QMimeData>

class GuiWidget : public QWidget
{
    Q_OBJECT

public:
    GuiWidget(QWidget *parent = nullptr);
    ~GuiWidget();
    // exe拖到窗口
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void cBox_versionAddItems();
    void cBox_kitsAddItems(const QString& qtVer);
private slots:
    void On_cBox_version_Change();
    void On_btn_deploy_clicked();
    void On_btn_openFile_clicked();
private:
    FindQtPath findQtPath;
    QString deployfilePath;                     //待打包的文件全路径
private:
    void initUi();
    QComboBox* cBox_version = nullptr;         //选择Qt版本按钮
    QComboBox* cBox_kits = nullptr;            //选择编译套件按钮

    QLabel* label_version = nullptr;
    QLabel* label_kits =nullptr;

    QPushButton* btn_deploy = nullptr;          //生成按钮
    QPushButton* btn_openFile = nullptr;        //选择打包的exe 按钮



};
#endif // GUIWIDGET_H
