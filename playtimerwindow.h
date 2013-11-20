#ifndef PLAYTIMERWINDOW_H
#define PLAYTIMERWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSettings>
#include "processdetector.h"

namespace Ui {
class PlayTimerWindow;
}

class PlayTimerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PlayTimerWindow(QWidget *parent = 0);
    ~PlayTimerWindow();
private slots:
    void startTimer();
    void stopTimer();
    void updateTime();
    void on_lineEdit_editingFinished();
    void changeName(QString name);

private:
    Ui::PlayTimerWindow *ui;
    ProcessDetector detector;
    QTimer timer;
    quint64 playtime_sec;
    QSettings settings;
};

#endif // PLAYTIMERWINDOW_H
