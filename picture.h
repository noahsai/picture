#ifndef PICTURE_H
#define PICTURE_H

#include <QMainWindow>
#include<QFile>
#include<QFileDialog>
#include<QDebug>
#include<QMessageBox>
#include <QScrollBar>
#include <QResizeEvent>
#include<QDir>
#include<QDirIterator>
#include<QWheelEvent>
#include<QEvent>
#include<QMouseEvent>
#include<QTimer>
#include<QDropEvent>
#include<QMimeData>
#include<QDragEnterEvent>
#include<QSettings>
#include<QDesktopWidget>
namespace Ui {
class picture;
}

class picture : public QMainWindow
{
    Q_OBJECT

public:
    explicit picture(QWidget *parent = 0);
    picture(QWidget *parent,const QStringList& imglist);
    picture(QWidget *parent,const QString&) ;
    ~picture();

    void openafile(const QString& img);
private slots:
    void openimg(const QString& img);
    void getimglist(const QString& path);
    void getposition(const QString& img);
    void refresh();
    void nextimg();
    void previmg();
    void toscale();
    void setfullscreen(bool);
    void save();
    void read();
    void timeout();

    void on_action_triggered();
    void on_action_3_triggered();
    void on_action_5_triggered();
    void on_action_6_triggered();

    void on_action_2_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_action_4_triggered(bool checked);

    void on_action_9_triggered();

    void on_action_10_triggered();

    void dropEvent(QDropEvent *event);//配套使用
    void dragEnterEvent(QDragEnterEvent *event);//配套使用
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    Ui::picture *ui;
    QImage *pic;
    QString img;
    int mod;
    int newwidth;
    int newheight;
    void resizeEvent(QResizeEvent *even);
    void wheelEvent(QWheelEvent*);
    bool eventFilter(QObject *, QEvent *);
//    void keyPressEvent(QKeyEvent *);
    QStringList list;
    int position;
    int all;
    int mousex,mousey;
    int upcount,downcount;
    bool mousepress;
    int scale;
    QImage* imgScaled;
    QTimer timer;
};

#endif // PICTURE_H
