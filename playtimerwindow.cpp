#include "playtimerwindow.h"
#include "ui_playtimerwindow.h"

PlayTimerWindow::PlayTimerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayTimerWindow)
{
    ui->setupUi(this);
}

PlayTimerWindow::~PlayTimerWindow()
{
    delete ui;
}
