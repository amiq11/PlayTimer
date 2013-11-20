#include "processdetector.h"
#include <QDebug>

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <tlhelp32.h>
#include <string>
void ProcessDetector::checkProcess()
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapshot, &entry)) {
        do {
            QString pname = QString::fromWCharArray(entry.szExeFile);
            if (pname == target) {
                if (!detected) {
                    qDebug() << "Started!!";
                    detected = true;
                    emit processStarted();
                }
                return;
            }
        } while(Process32Next(hSnapshot,&entry));
        if (detected) {
            qDebug() << "Stopped!!";
            detected = false;
            emit processStopped();
        }
    }
}
#endif

const int ProcessDetector::interval_ms = 1000;

ProcessDetector::ProcessDetector(QObject *parent, QString name) :
    QObject(parent), detected(false)
{
    target = name;

    timer.setInterval(interval_ms);
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkProcess()));
//    if ( !target.isEmpty() ) {
//        timer.start();
//    }
    emit targetChanged(target);
}

void ProcessDetector::setProcessName(QString &name)
{
    bool status = timer.isActive();
    timer.stop();
    detected = false;
    emit processStopped();
    target = name;
    qDebug() << "target is changed to " << target;
    if (status) timer.start();
    emit targetChanged(target);
}

void ProcessDetector::start()
{
    if (!target.isEmpty()) timer.start();
}

void ProcessDetector::stop()
{
    timer.stop();
}

