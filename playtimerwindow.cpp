#include "playtimerwindow.h"
#include "ui_playtimerwindow.h"
#include <QTime>
#include <QDebug>
PlayTimerWindow::PlayTimerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayTimerWindow),
    detector(parent),
    timer(),
    playtime_sec(0),
    settings("amiq11", "playtimer")
{
    ui->setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(&detector, SIGNAL(processStarted()), this, SLOT(startTimer()));
    connect(&detector, SIGNAL(processStopped()), this, SLOT(stopTimer()));
    connect(&detector, SIGNAL(targetChanged(QString)), ui->lineEdit, SLOT(setText(QString)));
    connect(&detector, SIGNAL(targetChanged(QString)), this, SLOT(changeName(QString)));

    // restore name
    QString name = settings.value("default/name", "ffxiv.exe").toString();
    detector.setProcessName(name);
    // restore time
    playtime_sec = settings.value(name+"/second", 0).toULongLong();
    QTime t (playtime_sec/3600, (playtime_sec/60)%60, playtime_sec%60);
    QString str = t.toString("HH:mm:ss");
    ui->timeEdit->setText(str);
    timer.setInterval(1000);
    detector.start();
}

PlayTimerWindow::~PlayTimerWindow()
{
    delete ui;
}

void PlayTimerWindow::startTimer()
{
    timer.start();
    qDebug() << "start: " << detector.getTarget();
}
void PlayTimerWindow::stopTimer()
{
    timer.stop();
}
void PlayTimerWindow::updateTime()
{
    playtime_sec++;
    QTime t (playtime_sec/3600, (playtime_sec/60)%60, playtime_sec%60);
    QString str = t.toString("HH:mm:ss");
    ui->timeEdit->setText(str);
    settings.setValue(detector.getTarget() + "/second", playtime_sec);
    qDebug() << str;

}
void PlayTimerWindow::changeName(QString name)
{
    settings.setValue("default/name", name);
    // restore time
    playtime_sec = settings.value(name+"/second", 0).toULongLong();
    QTime t (playtime_sec/3600, (playtime_sec/60)%60, playtime_sec%60);
    QString str = t.toString("HH:mm:ss");
    ui->timeEdit->setText(str);
}

void PlayTimerWindow::on_lineEdit_editingFinished()
{
    detector.setProcessName(ui->lineEdit->text());
}

