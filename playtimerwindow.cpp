#include "playtimerwindow.h"
#include "ui_playtimerwindow.h"
#include <QTime>
#include <QDebug>
PlayTimerWindow::PlayTimerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayTimerWindow),
    timer(),
    playtime_sec(0),
    settings("amiq11", "playtimer")
{
    ui->setupUi(this);
    createActions();
    createTrayIcon();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    detector = new ProcessDetector( this );
    connect(detector, SIGNAL(processStarted()), this, SLOT(startTimer()));
    connect(detector, SIGNAL(processStopped()), this, SLOT(stopTimer()));
    connect(detector, SIGNAL(processStarted()), this, SLOT(showMessage()));
    connect(detector, SIGNAL(processStopped()), this, SLOT(showMessage()));
    connect(detector, SIGNAL(targetChanged(QString)), ui->lineEdit, SLOT(setText(QString)));
    connect(detector, SIGNAL(targetChanged(QString)), this, SLOT(changeName(QString)));

    // restore name
    QString name = settings.value("default/name", "ffxiv.exe").toString();
    detector->setProcessName(name);
    // restore time
    playtime_sec = settings.value(name+"/second", 0).toULongLong();
    QString str = secToString(playtime_sec);
    ui->timeEdit->setText(str);
    // timer settings
    timer.setInterval(1000);

    // start
    trayIcon->show();
    showMessage();
    detector->start();
}

PlayTimerWindow::~PlayTimerWindow()
{
    delete ui;
    delete detector;
    delete openAction;
    delete timeAction;
    delete quitAction;
    delete trayIconMenu;
    delete trayIcon;

}

void PlayTimerWindow::startTimer()
{
    timer.start();
    qDebug() << "start: " << detector->getTarget();
}
void PlayTimerWindow::stopTimer()
{
    timer.stop();
}
void PlayTimerWindow::updateTime()
{
    playtime_sec++;
    QString str = secToString(playtime_sec);
    ui->timeEdit->setText(str);
    settings.setValue(detector->getTarget() + "/second", playtime_sec);
    qDebug() << str;

}
void PlayTimerWindow::changeName(QString name)
{
    settings.setValue("default/name", name);
    // restore time
    playtime_sec = settings.value(name+"/second", 0).toULongLong();
    QString str  = secToString(playtime_sec);
    ui->timeEdit->setText(str);
}

QString PlayTimerWindow::secToString(quint64 sec)
{
    //QTime t (sec/3600, (sec/60)%60, sec%60);
    return QString("%1:%2:%3")
            .arg(sec/3600, 3, 10, QChar('0'))
            .arg((sec/60)%60, 2, 10, QChar('0'))
            .arg(sec%60, 2, 10, QChar('0'));
}

void PlayTimerWindow::on_lineEdit_editingFinished()
{
    detector->setProcessName(ui->lineEdit->text());
}

void PlayTimerWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
        //showMessage();
    }
}

void PlayTimerWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}

void PlayTimerWindow::showMessage()
{
    trayIcon->showMessage(tr("PlayTime: ")+detector->getTarget(),
                         secToString(playtime_sec),
                         QSystemTrayIcon::Information,
                         1000);
}

void PlayTimerWindow::messageClicked()
{
    show();
}

void PlayTimerWindow::createActions()
{
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    timeAction = new QAction(tr("&Time"), this);
    connect(timeAction, SIGNAL(triggered()), this, SLOT(showMessage()));
    openAction = new QAction(tr("&Open"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(show()));
}

void PlayTimerWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(timeAction);
    trayIconMenu->addAction(openAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/img/icon.png"));
    trayIcon->setContextMenu(trayIconMenu);
}
