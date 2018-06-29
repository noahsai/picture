#include "picture.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    picture w;
    w.setWindowIcon(QIcon(":/pic.png"));
    if(argv[1]){
        w.openafile(QString(argv[1]));
    }
    w.show();

    return a.exec();
}
