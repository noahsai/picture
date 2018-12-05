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
#include<QMimeDatabase>
#include<QCursor>
#include<QProcess>
#include<QMetaEnum>
#include<QDateTime>
#include<icondelegate.h>
#include<QGraphicsOpacityEffect>
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
    void openpath();
    void delfile();
    void fileinfo();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_action_4_triggered(bool checked);

    void on_action_9_triggered();

    void on_action_10_triggered();

    void dropEvent(QDropEvent *event);//配套使用
    void dragEnterEvent(QDragEnterEvent *event);//配套使用
    void mouseDoubleClickEvent(QMouseEvent* event);

    void on_action_lock_toggled(bool checked);

    void on_action_width_toggled(bool arg1);

    void on_action_height_toggled(bool arg1);

    void on_action_real_toggled(bool arg1);


    void on_listWidget_clicked(const QModelIndex &index);

    void on_openfile_clicked();

    void on_width_clicked();

    void on_height_clicked();

    void on_real_clicked();

    void on_full_clicked();

    void on_shun_clicked();

    void on_ni_clicked();

    void on_openfile_2_clicked();

    void on_openfile_3_clicked();

private:
    Ui::picture *ui;
    QImage *pic;
    QString img;
    int mod;
    int newwidth;
    int newheight;
    void initpicture();
    void resizeEvent(QResizeEvent *even);
    void wheelEvent(QWheelEvent*);
    bool eventFilter(QObject *, QEvent *);
    void contextMenuEvent(QContextMenuEvent *event);
    void rotate(qreal);
//    void keyPressEvent(QKeyEvent *);
    QStringList list;
    QStringList formatlist;//必须跟list同清同增同减！
    int position;
    //int all;不需要了
    int mousex,mousey;
    int upcount,downcount;
    bool mousepress,mousemove;
    int scale;
    QImage imgScaled;
    QTimer timer;
    qreal degree;
    bool rotateed;
    bool isresize;
    QLabel *info;
};



#endif // PICTURE_H
