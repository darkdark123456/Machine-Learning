#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include  <QMenuBar>
#include  <QAction>
#include  <QComboBox>
#include   <QSpinBox>
#include    <QToolBar>
#include    <QFontComboBox>
#include    <QToolBar>
#include    <QTextCharFormat>
#include    <QDockWidget>
#include    <QPushButton>
#include     <QFileDialog>
#include     <QTextStream>
#include     <QTextBlock>
#include     <QDebug>
 #include   <QDialog>
#include<QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
#include<QToolButton>
#include    "showwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void creatActions();
    void creatMenus();
    void creatToolBar();
    void loadFile(QString filename);
    void saveFile(QString filename);
    void mergeFormat(QTextCharFormat);
    void setfont();
private:
    QLabel *label1;
    QMenu *fileMenu;
    QMenu *zoomMenu;
    QMenu *rotateMenu;
    QMenu *mirrorMenu;
     // fileMenu
    QImage image;
    QString filename;
    showwidget *showWidget;
    QAction *openfile;
    QAction *newfile;
    QAction *printtext;
    QAction *printimage;
    //zoomMenu
    QAction *exit;
    QAction *copy;
    QAction *cut;
    QAction *paste;
    QAction *save;
    QAction *about;
    QAction *zoomIn;
    QAction *zoomOut;
    // rotateMenu
    QAction *rotate90;
    QAction *rotate180;
    QAction*rotate270;
    //mirrorMenu
    QAction *H_mirror;
    QAction *V_mirror;
    QAction *undoAction;
    QAction*redoAction;
    // tool
    QToolBar *fileTool;
    QToolBar *zoomBarTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;
    QToolBar *doToolBar;
    QDockWidget *dock;
    //font
//    QLabel *fontlabel_1;
    QLabel*fontlabel_2;
//    QFontComboBox *fontComBox;
    QComboBox *sizeComBox;
//    QToolButton *boldbtn;
//    QToolButton *italicbtn;
//    QToolButton *underlineBtn;
//    QToolButton *colorBtn;
    QToolBar *fontbar;

protected slots:
    //file
    void creatNewFile();
    void openNewFile();
    void saveNewFile();
    void printNewText();

    //font
//    void showFontComBox(QString s);
    void showSizeBox(QString s);
    void showTextSize(QString s);
//    void showBoldbtn();
//    void showColorbtn();
//    void showUnderlinebtn();
//    void showItalicbtn();


};


#endif // MAINWINDOW_H
