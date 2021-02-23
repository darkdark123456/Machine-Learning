#include "showwidget.h"
#include"mainwindow.h"

showwidget::showwidget(QWidget *parent) : QWidget(parent)
{
    mainlayout=new QGridLayout(this);
    text = new QTextEdit();
    pbtn = new QPushButton();
    pbtn->setText(tr("btn"));
    mainlayout->addWidget(text,0,0);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);


}
