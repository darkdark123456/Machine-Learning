#include "mainwindow.h"
#include "showwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    setWindowTitle(tr("编译器"));

    showWidget = new showwidget (this);
     //怎么在一个窗口里设置一个子类窗口?创建一个新的窗口用this继承，
    //在子类中用一个mainlayout，在子类的构造函数中添加子类想要的控件
    setCentralWidget(showWidget);
    setfont();
    creatActions();
    creatMenus();
    creatToolBar();
}


MainWindow::~MainWindow()
{
}


void MainWindow::creatActions(){

    openfile=new QAction(QIcon("open.png"),tr("打开"),this);
    openfile->setShortcut(tr("ctrl+o"));
    openfile->setStatusTip(tr("打开一个文件"));


    newfile = new QAction (QIcon("new.jpg"),tr("新建"),this);
    newfile->setShortcut(tr("ctrl+n"));
    newfile->setStatusTip(tr("新建一个文件"));

    printtext = new QAction (QIcon("print.png"),tr("打印文本"),this);
    printtext->setStatusTip(tr("打印一个文本"));

    printimage = new QAction (QIcon("print.png"),tr("打印图像"),this);
    printimage->setStatusTip(tr("打印一个图像"));

    exit = new QAction (tr("退出"),this);
    exit->setShortcut(tr("ctrl+q"));
    exit->setStatusTip(tr("退出程序"));
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    copy = new QAction (tr("复制"),this);
    copy->setShortcut(tr("ctrl+c"));
    copy->setStatusTip(tr("复制文本"));
    connect(copy,SIGNAL(triggered()),showWidget->text,SLOT(copy()));

    cut = new QAction (tr("剪切"),this);
    cut->setShortcut(tr("ctrl+x"));
    cut->setStatusTip(tr("剪切文本"));
    connect(cut,SIGNAL(triggered()),showWidget->text,SLOT(cut()));

    save = new QAction (tr("保存"),this);
    save->setShortcut(tr("ctrl+s"));
    save->setStatusTip(tr("保存文本"));
    connect(save,SIGNAL(triggered()),showWidget->text,SLOT(save()));




    paste = new QAction (tr("粘贴"),this);
    paste->setShortcut(tr("ctrl+v"));
    paste->setStatusTip(tr("粘贴文本"));
    connect(paste,SIGNAL(triggered()),showWidget->text,SLOT(paste()));

    about = new QAction (tr("关于"),this);
    connect(about,SIGNAL(triggered()),this,SLOT(Qapplication::aboutQt()));

    undoAction = new QAction (tr("撤销操作"),this);
    connect(undoAction,SIGNAL(triggered()),showWidget->text,SLOT(undo()));
    redoAction = new QAction (tr("恢复操作"),this);
    connect(redoAction,SIGNAL(triggered()),showWidget->text,SLOT(redo()));





}


void MainWindow::creatMenus(){
    fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(openfile); // openfile 添加菜单里，显示的是tr后面的内容
    fileMenu->addAction(newfile);
    fileMenu->addAction(save);
    fileMenu->addAction(printtext);
    fileMenu->addAction(printimage);

    zoomMenu=menuBar()->addMenu(tr("编辑"));
    zoomMenu->addAction(exit);
    zoomMenu->addAction(copy);
    zoomMenu->addAction(paste);
    zoomMenu->addAction(about);
    zoomMenu->addAction(undoAction);
    zoomMenu->addAction(redoAction);


    connect(newfile,SIGNAL(triggered()),this,SLOT(creatNewFile()));
    connect(openfile,SIGNAL(triggered()),this,SLOT(openNewFile()));
    connect(save,SIGNAL(triggered()),this,SLOT(saveNewFile()));
    connect(printtext,SIGNAL(triggered()),this,SLOT(printNewText()));
    connect(sizeComBox,SIGNAL(activated(QString)),this,SLOT(showSizeBox(QString))); // 设置字号 sizeComBox里有填充的字体尺寸，被激活时返回这个尺寸，
    connect(sizeComBox,SIGNAL(activated(QString)),this,SLOT(showTextSize(QString)));    //用两个响应函数接受它

}


void  MainWindow::creatToolBar(){
    // 文件工具栏 一些常用的操作
    fileTool = addToolBar("file");
    fileTool->addAction(openfile);//openfile 添加在工具栏里，会用到图片参数，显示的是图片
    fileTool->addAction(newfile);
    fileTool->addAction(printtext);
    fileTool->setMovable(false);

    zoomBarTool=addToolBar("Edit");
    zoomBarTool->addAction(copy);
    zoomBarTool->addAction(cut);
    zoomBarTool->addAction(paste);
    zoomBarTool->setMovable(false);

    doToolBar = addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);
    doToolBar->setMovable(false);

    // font
    fontbar = addToolBar("font");
//    fontbar->addWidget(fontlabel_1);
//    fontbar->addSeparator();
//    fontbar->addWidget(fontlabel_2);
//    fontbar->addWidget(fontComBox);
   fontbar->addWidget(fontlabel_2);
//   fontbar->addSeparator();
    fontbar->addWidget(sizeComBox);

//    fontbar->addWidget(italicbtn);
//    fontbar->addWidget(underlineBtn);
//    fontbar->addSeparator();
//    fontbar->addWidget(colorBtn);

}


// 创建一个新文件
void MainWindow::creatNewFile(){
    MainWindow *newimgprocesser = new MainWindow();
    newimgprocesser->show();
}

// 打开一个新文件
void MainWindow::openNewFile(){
    filename = QFileDialog::getOpenFileName(this);
    if(!filename.isEmpty()){
        if(showWidget->text->document()->isEmpty()){ //text里没有文本直接读
                loadFile(filename);
        }
        else { // 如果窗口的text里有文本 ,新创建一个窗口，用新窗口去读文件，用到this指针；
            MainWindow *newwidget= new MainWindow ();
            newwidget->show();
            newwidget->loadFile(filename);
        }
    }

}

void MainWindow::loadFile(QString filename){
    QFile filein(filename);
    Q_ASSERT(filein.open(QIODevice::ReadOnly));
     QTextStream intext(&filein);
     while(!intext.atEnd()){
         showWidget->text->append(intext.readLine());
     }
}


// 保存文件

void MainWindow::saveNewFile(){
    filename = QFileDialog::getSaveFileName(this);
    if(!(showWidget->text->document()->isEmpty())){
        saveFile(filename);
    }
}


void MainWindow::saveFile(QString filename){
    QFile fileout(filename);
    fileout.open(QFile::WriteOnly);
    QTextStream outtext(&fileout);
    outtext<<showWidget->text->toPlainText(); // 获取到我呢本内容并写入
}




//打印文件


void MainWindow::printNewText(){
    QPrinter printer;
    QPrintDialog printerDialog (&printer,this);
    if(printerDialog.exec()){
        QTextDocument *doc = showWidget->text->document();
        doc->print(&printer);
    }

}

// 设置字号
void MainWindow::setfont(){
    sizeComBox = new QComboBox (this);
    fontlabel_2 = new QLabel (tr("字号"),this);
    QFontDatabase db;
    foreach(int size,db.standardSizes())
        sizeComBox->addItem(QString::number(size)); // 将字号填充进去

}



    // 选定文本改字号
void MainWindow::showSizeBox(QString sp){
    QTextCharFormat fmt;
    fmt.setFontPointSize(sp.toFloat());
    showWidget->text->mergeCurrentCharFormat(fmt);
}
    //选定字号改文本
void MainWindow::showTextSize(QString sp ){
    showWidget->text->setFontPointSize(sp.toFloat());

}







