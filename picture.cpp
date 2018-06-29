#include "picture.h"
#include "ui_picture.h"

picture::picture(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::picture)
{
    ui->setupUi(this);
    ui->scrollArea->installEventFilter(this);
    ui->scrollAreaWidgetContents->installEventFilter(this);
    setCentralWidget(ui->scrollArea);
    ui->scrollArea->setLayout(ui->docklayout);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    imgScaled = new QImage;
    mod=0;
    pic=NULL;
    position=0;
    all=0;
    newwidth=ui->scrollArea->width();
    newheight=ui->scrollArea->height();
    mousex=0;
    mousey=0;
    mousepress=false;
    scale=100;
    upcount=0;
    downcount=0;
    timer.setSingleShot(true);
    read();

}

picture::picture(QWidget *parent,const QStringList& imglist) :
    QMainWindow(parent),
    ui(new Ui::picture)
{
    ui->setupUi(this);
    ui->scrollArea->installEventFilter(this);
    setCentralWidget(ui->scrollArea);
    ui->scrollArea->setLayout(ui->docklayout);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    imgScaled = new QImage;
    mod=0;
    pic=NULL;
    position=0;
    all=0;
    newwidth=ui->scrollArea->width();
    newheight=ui->scrollArea->height();
    mousex=0;
    mousey=0;
    mousepress=false;
    scale=100;
    read();

    list=imglist;
    openimg(list.at(0));


}

picture::picture(QWidget *parent,const QString& filename_or_dir) :
    QMainWindow(parent),
    ui(new Ui::picture)
{
    ui->setupUi(this);
    ui->scrollArea->installEventFilter(this);
    setCentralWidget(ui->scrollArea);
    ui->scrollArea->setLayout(ui->docklayout);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    imgScaled = new QImage;
    mod=0;
    pic=NULL;
    position=0;
    all=0;
    newwidth=ui->scrollArea->width();
    newheight=ui->scrollArea->height();
    mousex=0;
    mousey=0;
    mousepress=false;
    scale=100;
    read();

    openafile(filename_or_dir);


}

picture::~picture()
{
    save();
    delete ui;
}

void picture::on_action_triggered()
{
    img=QFileDialog::getOpenFileName(this,tr("打开图片"),"",tr("Images (*.png *.bmp *.jpg *.tif *.gif *jpeg)"));
    openafile(img);

}

void picture::openafile(const QString &img)
{
    if(QFileInfo(img).isFile())
    {
        qDebug()<<img;

        list.clear();
        list=img.split("/");
        list.removeLast();
        QString path=list.join("/");
        getimglist(path);
        getposition(img);
        openimg(img);
    }
    else if(QFileInfo(img).isDir())
    {
        getimglist(img);
        openimg(list.first());
    }
}

void picture::openimg(const QString& img)
{
    if(!img.isEmpty())
    {
        pic=new QImage;
        if(pic->load(img))
        {
            refresh();
        }
        else
        {
            QMessageBox::information(this,tr("打开失败"),tr("图片打开失败！"));
            qDebug()<<"open error"<<img;
        }
        ui->scrollArea->setLayout(ui->docklayout);

    }
}

void picture::getimglist(const QString& path)
{
    list.clear();
    QDirIterator someone(path,QDir::Files|QDir::NoSymLinks);
    while(someone.hasNext())
    {
        QString file=someone.next();
        QStringList tmp=file.split(".");
        QString fomat=tmp.last().toLower();
        if(fomat=="jpg"||fomat=="png"||fomat=="bmp"||fomat=="gif"||fomat=="tif"||fomat=="jpeg")
        {
            list.append(file);
        }
    }
    all=list.count()-1;
    list.sort();
    //qDebug()<<list;
}
void picture::getposition(const QString& img)
{
    if(!list.isEmpty())
    {
        position=list.indexOf(img);
    }
    //qDebug()<<"position:"<<position;
}

void picture::on_action_3_triggered()
{
    mod=0;
    if(pic)
    {
        scale=newwidth*100/pic->width();
        *imgScaled = pic->scaled(newwidth,pic->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        //qDebug()<<imgScaled->height()<<newheight<<pic->height();
        if(imgScaled->height()>newheight)
        {
            *imgScaled = pic->scaled(newwidth-15,pic->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->label->setPixmap(QPixmap::fromImage(*imgScaled));

    }

}


void picture::on_action_5_triggered()
{
    mod=1;
    if(pic)
    {
        scale=newwidth*100/pic->width();
        *imgScaled = pic->scaled(pic->width(),newheight,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        //qDebug()<<imgScaled->width()<<newwidth<<pic->width();
        if(imgScaled->width()>newwidth)
        {
            *imgScaled = pic->scaled(pic->width(),newheight-15,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->label->setPixmap(QPixmap::fromImage(*imgScaled));
       // //qDebug()<<wid<<ui->label->width()<<imgScaled->width();

    }

}

void picture::on_action_6_triggered()
{
    mod=2;
    if(pic)
    {
        pic->load(list.at(position));
        ui->label->setPixmap(QPixmap::fromImage(*pic));
    }
}

void picture::resizeEvent(QResizeEvent *even)
{

    newwidth=even->size().width();
    if(ui->menuBar->isVisible())
        newheight=even->size().height()-ui->menuBar->height();
    else
        newheight=even->size().height();
    if(pic)
    {
        refresh();
    }
    QMainWindow::resizeEvent(even);

}

void picture::refresh()
{
    switch(mod)
    {
    case 0:on_action_3_triggered();break;
    case 1:on_action_5_triggered();break;
    case 2:on_action_6_triggered();break;
    default:break;
    }
    setWindowTitle(list.at(position).split("/").last());
}
void picture::wheelEvent(QWheelEvent* event)
{
    if(pic&&ui->action_4->isChecked())
    {
        int degrees=event->delta();//上为正，下为负
        if(!(ui->scrollArea->verticalScrollBar()->isVisible() && (ui->scrollArea->verticalScrollBar()->value()!=ui->scrollArea->verticalScrollBar()->maximum() && ui->scrollArea->verticalScrollBar()->value()!=ui->scrollArea->verticalScrollBar()->minimum())))
        {
            if(degrees>0)
            {
                if(ui->scrollArea->verticalScrollBar()->isVisible())
                {
                    upcount++;
                    if(upcount==4) {
                        previmg();
                        upcount=0;
                    }
                }
                else
                {
                    previmg();
                    upcount=0;

                }
                downcount=0;

            }
            else
            {
                if(ui->scrollArea->verticalScrollBar()->isVisible())
                {
                    downcount++;
                    if(downcount==4) {
                        nextimg();
                        downcount=0;
                    }
                }
                else
                {
                    nextimg();
                    downcount=0;
                }
                upcount=0;

            }
            event->accept();
        }
    }
    else QMainWindow::wheelEvent(event);


}

//void picture::keyPressEvent(QKeyEvent *event)
//{
//    switch(event->key())
//    {
//    case Qt::Key_F11: setfullscreen(!isFullScreen());break;
//    case Qt::Key_Escape: setfullscreen(false);break;
//    case Qt::Key_Left: previmg();break;
//    case Qt::Key_Right: nextimg();break;
//    default:break;
//    }
//}

void picture::setfullscreen(bool full)
{
    if(full)
    {
        showFullScreen();
    }
    else showNormal();
}

void picture::nextimg()
{
    if(list.count()>1)
    {
        if(position<all)
        {
            position++;
            pic->load(list.at(position));
            refresh();
            ui->scrollArea->verticalScrollBar()->setValue(0);
        }
        else if(position==all){
            position=0;
            pic->load(list.at(position));
            refresh();
            ui->scrollArea->verticalScrollBar()->setValue(0);
        }
    }
}

void picture::previmg()
{
    if(list.count()>1)
    {
        if(position>0)
        {
            position--;
            pic->load(list.at(position));
            refresh();


        }
        else if(position==0) {
            position=all;
            pic->load(list.at(position));
            refresh();
        }
    }
}

void picture::toscale()
{
    disconnect(&timer , SIGNAL(timeout()),this , SLOT(timeout()));
    *imgScaled = pic->scaled(pic->width()*(scale/100.0),pic->height()*(scale/100.0),Qt::KeepAspectRatio,Qt::FastTransformation);
    ui->label->setPixmap(QPixmap::fromImage(*imgScaled));
    connect(&timer , SIGNAL(timeout()),this , SLOT(timeout()));
    timer.start(200);
}

void picture::timeout(){
    qDebug()<<"time out"<<timer.isActive();
    *imgScaled = pic->scaled(pic->width()*(scale/100.0),pic->height()*(scale/100.0),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(*imgScaled));
}

bool picture::eventFilter(QObject *obj, QEvent *event)
{
    if(pic)
    {
        if(obj==ui->scrollArea)
        {
            if(event->type()==QEvent::MouseButtonPress)
            {
               QMouseEvent *press=static_cast<QMouseEvent*>(event);
               mousex=press->pos().x();
               mousey=press->pos().y();
               mousepress=true;
               setCursor(Qt::OpenHandCursor);
               return true;

            }
            else if(event->type()==QEvent::MouseButtonRelease)
            {
               mousepress=false;
               setCursor(Qt::ArrowCursor);
               return true;

            }
            else if(event->type()==QEvent::MouseMove)
            {
                if(mousepress)
                {
                    setCursor(Qt::ClosedHandCursor);
                    QMouseEvent *press=static_cast<QMouseEvent*>(event);
                    if(ui->scrollArea->verticalScrollBar()->isVisible()||ui->scrollArea->horizontalScrollBar()->isVisible())
                    {
                        int y=ui->scrollArea->verticalScrollBar()->value();
                        int x=ui->scrollArea->horizontalScrollBar()->value();
                        y+=-(press->pos().y()-mousey);
                        x+=-(press->pos().x()-mousex);

                        ui->scrollArea->verticalScrollBar()->setValue(y);
                        ui->scrollArea->horizontalScrollBar()->setValue(x);

                        mousex=press->pos().x();//移动中不断刷新mousex，y
                        mousey=press->pos().y();
                        return true;
                    }
                }
            }
            else if(event->type()==QEvent::KeyPress)
            {
                QKeyEvent *e=static_cast<QKeyEvent*>(event);
                switch(e->key())
                {
                case Qt::Key_F11: setfullscreen(!isFullScreen());break;
                case Qt::Key_Escape: setfullscreen(false);break;
                case Qt::Key_Up:
                case Qt::Key_Left: previmg();break;
                case Qt::Key_Down:
                case Qt::Key_Right: nextimg();break;
                default:return QMainWindow::eventFilter(obj,event);break;
                }
            }
            else return QMainWindow::eventFilter(obj,event);
        }
        else if(obj==ui->scrollAreaWidgetContents)
        {
            if(event->type()==QEvent::Wheel)
            {
                if(QApplication::keyboardModifiers() == Qt::ControlModifier)
                {
                    QWheelEvent *e=static_cast<QWheelEvent*>(event);
                    int degrees=e->delta();//上为正，下为负
                    if(degrees>0)
                    {
                        scale+=10;
                        if(scale>300) scale=300;
                    }
                    else{
                        scale-=10;
                        if(scale<10) scale=10;
                    }
                    toscale();
                    event->accept();
                }
                else
                {
                    QWheelEvent *e=static_cast<QWheelEvent*>(event);
                    int degrees=e->delta();//上为正，下为负
                    if(degrees>0)
                    {
                        if(!ui->menuBar->isVisible())
                        {
                            ui->menuBar->setVisible(true);
                        }
                        else return QMainWindow::eventFilter(obj,event);

                    }
                    else
                    {
                        if(ui->menuBar->isVisible())
                        {
                            ui->menuBar->setVisible(false);
                        }
                        else return QMainWindow::eventFilter(obj,event);

                    }
                }
            }

            else return QMainWindow::eventFilter(obj,event);
        }
    }
    else return QMainWindow::eventFilter(obj,event);
}

void picture::on_action_2_triggered()
{
    setfullscreen(!isFullScreen());
}

void picture::on_pushButton_clicked()
{
    previmg();
}

void picture::on_pushButton_2_clicked()
{
    nextimg();
}

void picture::on_action_4_triggered(bool checked)
{
    if(pic)
    {
        ui->pushButton->setVisible(!checked);
        ui->pushButton_2->setVisible(!checked);
    }
    save();
}

void picture::save()
{
    QSettings settings("LitePic","cfg");
    settings.setValue("isauto", ui->action_4->isChecked());
    settings.setValue("size", this->size());
    qDebug()<<"savecfged";

}
void picture::read()
{
    QSettings settings("LitePic","cfg");
    bool isauto = true;
    isauto = settings.value("isauto", isauto).toBool();
    if(isauto){
        ui->action_4->setChecked(true);
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);

    }
    else
    {
        ui->action_4->setChecked(false);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
    }
    QSize s = settings.value("size", QSize(550, 450)).toSize();
    int x=QApplication::desktop()->width()/2-s.width()/2;
    int y=QApplication::desktop()->height()/2-s.height()/2;
    setGeometry(x , y , s.width() , s.height() );

}

void picture::on_action_9_triggered()
{
    QMatrix matrix;
    matrix.rotate(90.0);
    *pic=pic->transformed(matrix,Qt::FastTransformation);
    refresh();
}

void picture::on_action_10_triggered()
{
    QMatrix matrix;
    matrix.rotate(-90.0);
    *pic=pic->transformed(matrix,Qt::FastTransformation);
    refresh();
}



void picture::dropEvent(QDropEvent *event)
{

    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }
    qDebug()<<fileName;
    openafile(fileName);

}

void picture::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"dragenter!";
        event->acceptProposedAction();
}


void picture::mouseDoubleClickEvent(QMouseEvent* event){
    setfullscreen(!isFullScreen());
}
