#include "playtimerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayTimerWindow w;
    w.show();
    
    return a.exec();
}
