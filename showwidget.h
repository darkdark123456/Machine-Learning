#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QImage>
#include <QLayout>
#include <QPushButton>
#include <QGridLayout>
class showwidget : public QWidget
{
    Q_OBJECT
public:
    explicit showwidget(QWidget *parent = nullptr);
    QImage image;
    QLabel *imagelabel;
    QTextEdit *text;
    QGridLayout *mainlayout;
    QPushButton *pbtn;
};

#endif // SHOWWIDGET_H
