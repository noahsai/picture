#include "picture.h"
#include "ui_picture.h"

void sort(QStringList& str);//文件名排序，解决自带排序出现1,10,11,2,3的问题，按1，2,3,10,11实际数字大小排序.


picture::picture(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::picture)
{
    initpicture();
}

picture::picture(QWidget *parent,const QStringList& imglist) :
    QMainWindow(parent),
    ui(new Ui::picture)
{
    initpicture();
    list=imglist;
    openimg(list.at(0));


}

picture::picture(QWidget *parent,const QString& filename_or_dir) :
    QMainWindow(parent),
    ui(new Ui::picture)
{
    initpicture();
    openafile(filename_or_dir);
}

void picture::initpicture(){
    ui->setupUi(this);
    ui->menuBar->hide();
    ui->listWidget->hide();
    //========
    QGraphicsOpacityEffect *m_pGraphicsOpacityEffect = new QGraphicsOpacityEffect(this);
    ui->widget->setGraphicsEffect(m_pGraphicsOpacityEffect );
    m_pGraphicsOpacityEffect ->setOpacity(1.0);
    //==========
    ui->widget->installEventFilter(this);
    ui->listWidget->setItemDelegate(new IconDelegate(this));
    ui->scrollAreaWidgetContents->installEventFilter(this);
    ui->scrollArea->installEventFilter(this);
    ui->scrollArea->setLayout(ui->docklayout);
    setCentralWidget(ui->scrollArea);
    mod=0;
    pic=NULL;
    info = NULL;
    position=0;
    //all=0;
    newwidth=ui->scrollArea->width();
    newheight=ui->scrollArea->height();
    mousex=0;
    mousey=0;
    mousepress=false;
    scale=100;
    upcount=0;
    downcount=0;
    degree = 0.0;
    rotateed = false;
    isresize = false;
    timer.setSingleShot(true);
    read();
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
        list=img.split("/");
        list.removeLast();
        QString path=list.join("/");
        getimglist(path);//里面会清空list，重置position和all
        getposition(img);//获取该图片在列表中的位置
        openimg(img);
    }
    else if(QFileInfo(img).isDir())
    {
        getimglist(img);
        openimg(list.first());
    }
}

void picture::openimg(const QString& img)//调用这个时，必须确保position与img对应
{
    if(!img.isEmpty())
    {
        if(pic == NULL) pic = new QImage;
        QString type = formatlist[position];
        if( type.isEmpty() ){
            QMimeDatabase db;
            QMimeType mime = db.mimeTypeForFile(list.at(position),QMimeDatabase::MatchContent	);  //
            type = mime.name().split("/").takeLast();
            formatlist.replace(position,type);//保存已知的
            qDebug()<<"Format:"<<img<<type;
        }
        if(pic->load(img,type.toLatin1()))
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
    formatlist.clear();
    ui->listWidget->clear();//清空！
    position = 0;
    QDirIterator someone(path,QDir::Files|QDir::NoSymLinks);
    while(someone.hasNext())
    {
        QString file=someone.next();
        QStringList tmp=file.split(".");
        QString fomat=tmp.last().toLower();
        if(fomat=="jpg"||fomat=="png"||fomat=="bmp"||fomat=="gif"||fomat=="tif"||fomat=="jpeg")
        {
            list.append(file);
            formatlist.append(QString());
        }
    }
    //all=list.count()-1;
    //list.sort();
    sort(list);

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


void picture::on_action_width_toggled(bool arg1)
{
    if(!arg1) return;
    mod=0;
    ui->action_height->setChecked(false);
    ui->action_real->setChecked(false);

    ui->action_width->setEnabled(false);//自锁
    ui->action_height->setEnabled(true);
    ui->action_real->setEnabled(true);

    if(pic)
    {
        //注意：窗口大小为某个范围时会出现黑边的问题不用解决了,有进度条时height不足以产生进度条，死循环来的。
        imgScaled = pic->scaled(newwidth,pic->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        //qDebug()<<imgScaled.height()<<newheight<<pic->height();
        if(imgScaled.height()>newheight)
        {
            imgScaled = pic->scaled(newwidth- ui->scrollArea->verticalScrollBar()->width(),pic->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->label->setPixmap(QPixmap::fromImage(imgScaled));
        scale = imgScaled.width()*100/pic->width();//记录已缩放程度

    }
}


void picture::on_action_height_toggled(bool arg1)
{
    if(!arg1) return;
    mod=1;
    ui->action_width->setChecked(false);
    ui->action_real->setChecked(false);

    ui->action_height->setEnabled(false);//自锁
    ui->action_width->setEnabled(true);
    ui->action_real->setEnabled(true);

    if(pic)
    {
        //注意：窗口大小为某个范围时会出现黑边的问题不用解决了,有进度条时width不足以产生进度条，死循环来的。
        imgScaled = pic->scaled(pic->width(),newheight,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        //qDebug()<<imgScaled.width()<<imgScaled.height()<<newwidth<<newheight<<pic->width()<<pic->height();
        if(imgScaled.width()> newwidth )
        {
            imgScaled = pic->scaled(pic->width(),newheight-ui->scrollArea->horizontalScrollBar()->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->label->setPixmap(QPixmap::fromImage(imgScaled));
        scale = imgScaled.height()*100/pic->height();//记录已缩放程度

       //qDebug()<<scale;

    }
}


void picture::on_action_real_toggled(bool arg1)
{
    if(!arg1) return;
    mod=2;
    ui->action_width->setChecked(false);
    ui->action_height->setChecked(false);

    ui->action_real->setEnabled(false);//自锁
    ui->action_height->setEnabled(true);
    ui->action_width->setEnabled(true);

    if(pic)
    {
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
    scale = 100;//放在前面
    switch(mod)
    {
    case 0:on_action_width_toggled(true);break;
    case 1:on_action_height_toggled(true);break;
    case 2:on_action_real_toggled(true);break;
    default:break;
    }
    setWindowTitle(list.at(position).split("/").last());
    if(info != NULL && info->isVisible()) fileinfo();

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
                    if(upcount==3) {
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
                    if(downcount==3) {
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
        if(position<list.length()-1)
        {
            position++;
        }
        else {
            position=0;
        }
        QString type = formatlist[position];
        if( type.isEmpty() ){
            QMimeDatabase db;
            QMimeType mime = db.mimeTypeForFile(list.at(position),QMimeDatabase::MatchContent	);  //
            type = mime.name().split("/").takeLast();
            formatlist.replace(position,type);//保存已知的
            //qDebug()<<"Format:"<<list.at(position)<<type;
        }
        pic->load(list.at(position),type.toLatin1());
        if(rotateed && (degree!=0.0)){
            rotate(degree);
        }
        refresh();
        ui->scrollArea->verticalScrollBar()->setValue(0);
        if(ui->listWidget->isVisible()) {
            int n = position-(ui->listWidget->width()/2/80);
            if(n<0) n=0;
            ui->listWidget->horizontalScrollBar()->setValue(n*80);
            ui->listWidget->item(position)->setSelected(true);
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
        }
        else  {
            position=list.length()-1;
        }
        QString type = formatlist[position];
        if( type.isEmpty() ){
            QMimeDatabase db;
            QMimeType mime = db.mimeTypeForFile(list.at(position),QMimeDatabase::MatchContent	);  //
            type = mime.name().split("/").takeLast();
            formatlist.replace(position,type);//保存已知的
            //qDebug()<<"Format:"<<list.at(position)<<type;
        }
        pic->load(list.at(position),type.toLatin1());
        if(rotateed && (degree!=0.0)){
            rotate(degree);
        }
        refresh();
        if(ui->listWidget->isVisible()){
            int n = position-(ui->listWidget->width()/2/80);
            if(n<0) n=0;
            ui->listWidget->horizontalScrollBar()->setValue(n*80);
            ui->listWidget->item(position)->setSelected(true);
        }
    }
}


void picture::toscale()
{
    disconnect(&timer , SIGNAL(timeout()),this , SLOT(timeout()));
    imgScaled = pic->scaled(pic->width()*(scale/100.0),pic->height()*(scale/100.0),Qt::KeepAspectRatio,Qt::FastTransformation);
    ui->label->setPixmap(QPixmap::fromImage(imgScaled));
    connect(&timer , SIGNAL(timeout()),this , SLOT(timeout()));
    timer.start(200);
}

void picture::timeout(){
    qDebug()<<"time out";//<<timer.isActive();
    imgScaled = pic->scaled(pic->width()*(scale/100.0),pic->height()*(scale/100.0),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(imgScaled));
    isresize = false;
}

bool picture::eventFilter(QObject *obj, QEvent *event)
{
//    qDebug()<<obj<<event;
        if(pic)
        {
            if(obj==ui->scrollArea )
            {
                QMouseEvent *press=static_cast<QMouseEvent*>(event);

                //qDebug()<<"....";
                if(event->type()==QEvent::MouseButtonPress )
                {
                    ui->listWidget->hide();
                   mousex=press->pos().x();
                   mousey=press->pos().y();
                   mousepress=true;
                   setCursor(Qt::OpenHandCursor);
                   event->accept();
                   return true;

                }
                else if(event->type()==QEvent::MouseButtonRelease)
                {
                   mousepress=false;
                   setCursor(Qt::ArrowCursor);
                   event->accept();
                   return true;

                }
                else if(event->type()==QEvent::MouseMove)
                {
                    //qDebug()<<"move";
                    if(mousepress)
                    {
                        setCursor(Qt::ClosedHandCursor);
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
                            event->accept();
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
                    event->accept();
                    return true;
                }
                else {
                    return QMainWindow::eventFilter(obj,event);

                }            }
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
                            scale+=5;
                            if(scale>300) scale=300;
                        }
                        else{
                            scale-=5;
                            if(scale<10) scale=10;
                        }
                        toscale();
                        event->accept();
                        return true;
                    }

                }

                else {
                    return QMainWindow::eventFilter(obj,event);
                }
            }
            else if(obj==ui->widget) {
                if(event->type()==QEvent::Enter ){
//                    qDebug()<<"enter";
                    QGraphicsOpacityEffect *m_pGraphicsOpacityEffect = new QGraphicsOpacityEffect(this);
                    ui->widget->setGraphicsEffect(m_pGraphicsOpacityEffect );
                    m_pGraphicsOpacityEffect ->setOpacity(1.0);
                }
                else if(event->type()==QEvent::Leave ){
                    //qDebug()<<"leave";
                    QGraphicsOpacityEffect *m_pGraphicsOpacityEffect = new QGraphicsOpacityEffect(this);
                        ui->widget->setGraphicsEffect(m_pGraphicsOpacityEffect );
                        m_pGraphicsOpacityEffect ->setOpacity(0);
                }
            }
        }
        else {
            return QMainWindow::eventFilter(obj,event);
        }
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
    save();
}

void picture::save()
{
    QSettings settings("LitePic","cfg");
    settings.setValue("isauto", ui->action_4->isChecked());
    settings.setValue("size", this->size());
    settings.setValue("rotateed", rotateed);
    settings.setValue("mod", mod);

    qDebug()<<"savecfged";

}
void picture::read()
{
    QSettings settings("LitePic","cfg");
    bool isauto = true;
    isauto = settings.value("isauto", isauto).toBool();
    if(isauto){
        ui->action_4->setChecked(true);

    }
    else
    {
        ui->action_4->setChecked(false);
    }
    QSize s = settings.value("size", QSize(550, 450)).toSize();
    int x=QApplication::desktop()->width()/2-s.width()/2;
    int y=QApplication::desktop()->height()/2-s.height()/2;
    setGeometry(x , y , s.width() , s.height() );
    rotateed  = settings.value("rotateed", false).toBool();

    ui->action_lock->setChecked(rotateed);

    mod = settings.value("mod", 0).toInt();
    switch(mod)
    {
    case 0:ui->action_width->setChecked(true);break;//会触发槽函数
    case 1:ui->action_height->setChecked(true);break;
    case 2:ui->action_real->setChecked(true);break;
    }
}

void picture::on_action_9_triggered()
{
    degree += 90.0;//这里是翻页时用的，需要累加
    rotate(90);//这里直接用90,;rotate别放在refresh里，否则每次refresh都会旋转。
    refresh();
}

void picture::on_action_10_triggered()
{
    degree -= 90.0;//这里是翻页时用的，需要累加
    rotate(-90);//这里直接用-90,;rotate别放在refresh里，否则每次refresh都会旋转。
    refresh();
}

void picture::rotate(qreal d){
    QMatrix matrix;
    matrix.rotate(d);
    *pic=pic->transformed(matrix,Qt::FastTransformation);
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
    event->accept();
}

void sort(QStringList& str){
    QString one ,sec;
    for(int i=0;i<str.length()-1;i++)
    {
        for(int j=i+1 ;j<str.length();j++){
            one = str[i];
            sec = str[j];
            for(int m =0,n=0 ; m<one.length() && n<sec.length() ; m++,n++){
                QChar c1 = one.at(m);
                QChar c2 = sec.at(n);
                if(c1.isDigit()&&c2.isDigit()){
                    QString a,b;
                    for(m ;m<one.length()&&one.at(m).isDigit();m++)
                    {
                        a.append(one.at(m));
                    }
                    for(n ;n<sec.length()&&sec.at(n).isDigit();n++)
                    {
                        b.append(sec.at(n));
                    }
                    int c,d;
                    c = a.toInt();
                    d = b.toInt();
                    if(c > d){
                        str.swap(i , j);
                    }
                    else if(c < d) break;
                    else if((m!=(one.length()-1))&&(n==(sec.length()-1)))
                    {
                        str.swap(i , j);
                    }
                }
                else if(c1 > c2){
                    str.swap(i , j);
                }
                else if(c1 < c2) break;
            }
        }
    }
}


void picture::on_action_lock_toggled(bool checked)
{
    rotateed = checked;
}

void picture:: openpath(){
    QProcess pro;
    QString path = list[position];
    path = path.remove(QRegularExpression("/[^/]+$"));
    QString cmd = "xdg-open \""+ path +"\"";
    pro.startDetached(cmd);
}

void picture:: delfile(){
    if(position == -1 ) {
        QMessageBox::warning(this,"没图片了","该文件夹已经没有图片了。");
        return;
    }
    int result;
    result = QMessageBox::question(this,"删除图片？","删除\n["+list[position]+"]\n后将无法恢复!\n您确定要删除？","否","是");
    if (result!=0) {
        QFile file(list[position]);
        if(file.remove()){
            list.removeAt(position);
            //all = list.length()-1;
            formatlist.removeAt(position);
            ui->listWidget->takeItem(position);
            if(list.length() == position) position = (list.length()-1);
            if(list.length() == 0) QMessageBox::warning(this,"没图片了","该文件夹已经没有图片了。");
            else openimg(list[position]);
        }
    }
}

void picture:: fileinfo(){
    if(position == -1 ) {
        QMessageBox::warning(this,"没图片了","该文件夹已经没有图片了。");
        return;
    }
    if(info == NULL)    info = new QLabel(this);
    info->setWordWrap(true);
    info->setTextInteractionFlags(Qt::TextSelectableByMouse);
    info->setWindowTitle("图片信息");
    QString text = "文件名：" + QString(list[position]).split("/").last() + "\n";
    text += "格式：" +ui->label->whatsThis()+ "\n";
    text += "分辨率：" + QString().setNum( pic->width()) + "×" + QString().setNum(pic->height()) + "\n";
    text += "偏移：" + QString().setNum( pic->offset().x())+"," +QString().setNum( pic->offset().y())+ "\n";
    QString alp = pic->hasAlphaChannel()?"是":"否" ;
    text += "Alpha通道：" + alp + "\n";
    text += "大小：" + QString().setNum(QFile(list[position]).size()/1024.0) + "KB\n";
    QFileInfo i(list[position]);
    text += "创建：" + i.created().toString("yyyy-MM-dd hh:mm:ss") + "\n";
    text += "修改：" + i.lastModified().toString("yyyy-MM-dd hh:mm:ss") + "\n";
    text += "访问：" + i.lastRead().toString("yyyy-MM-dd hh:mm:ss") + "\n";
    text += "路径："+list[position] ;

    qDebug()<<info;
    info->setMargin(5);
    info->setText(text);
    info->adjustSize();
    info->setWindowFlags(Qt::Window);
    info->setVisible(true);
}

void picture::on_listWidget_clicked(const QModelIndex &index)
{
    QString img = ui->listWidget->item(index.row())->data(Qt::UserRole).toString();
    getposition(img);//设置position
    openimg(img);
}

void picture::on_openfile_clicked()
{
    on_action_triggered();
}

void picture::on_width_clicked()
{
    ui->action_width->setChecked(true);
}

void picture::on_height_clicked()
{
    ui->action_height->setChecked(true);
}

void picture::on_real_clicked()
{
    ui->action_real->setChecked(true);
}

void picture::on_full_clicked()
{
    on_action_2_triggered();
}

void picture::on_shun_clicked()
{
    on_action_9_triggered();
}

void picture::on_ni_clicked()
{
    on_action_10_triggered();
}

void picture::on_openfile_2_clicked()
{
    ui->menuBar->setVisible(!ui->menuBar->isVisible());
}

void picture::on_openfile_3_clicked()
{
    if(list.length()>0&&ui->listWidget->count()==0)
    {
        ui->listWidget->clear();
        for(int i=0;i<list.length();i++)
        {
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            item->setIcon(QIcon(list[i]));
            item->setSizeHint(QSize(80,100));
            item->setData(Qt::DecorationRole,QVariant(item->icon()));
            item->setData(Qt::UserRole,QString(list[i]));
        }
    }
    ui->listWidget->setVisible(!ui->listWidget->isVisible());
}

void picture::contextMenuEvent(QContextMenuEvent *event){
    if(!pic) return;
    //qDebug()<<event->pos()<<ui->scrollArea->pos()<<event->globalPos();
    if(event->pos().x()<ui->scrollArea->pos().x() ||event->pos().y()<ui->scrollArea->pos().y() ) return;
    QMenu *pMenu = new QMenu(this);
    QAction *pAddGroupAct = new QAction(tr("打开文件位置"), pMenu);
    connect(pAddGroupAct ,SIGNAL(triggered(bool)),this,SLOT(openpath()) );
    pMenu->addAction(pAddGroupAct);
    pMenu->addSeparator();
    pAddGroupAct = new QAction(tr("删除"), pMenu);
    connect(pAddGroupAct ,SIGNAL(triggered(bool)),this,SLOT(delfile()) );
    pMenu->addAction(pAddGroupAct);
    pMenu->addSeparator();
    pAddGroupAct = new QAction(tr("属性"), pMenu);
    connect(pAddGroupAct ,SIGNAL(triggered(bool)),this,SLOT(fileinfo()) );
    pMenu->addAction(pAddGroupAct);

    pMenu->popup(cursor().pos());
    event->accept();
}
