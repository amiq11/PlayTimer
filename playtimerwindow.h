#ifndef PLAYTIMERWINDOW_H
#define PLAYTIMERWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QtGui>
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

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    // Timer
    void startTimer();
    void stopTimer();
    void updateTime();
    // Detector
    void changeName(QString name);
    void on_lineEdit_editingFinished();
    // TrayIcon
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void messageClicked();

private:
    QString currentTimeString();
    QString secToString(quint64 sec);
    void createActions();
    void createTrayIcon();

    Ui::PlayTimerWindow *ui;
    ProcessDetector *detector;
    QTimer timer;
    quint64 playtime_total_sec;
    quint64 playtime_now_sec;
    QSettings settings;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *quitAction;
    QAction *timeAction;
    QAction *openAction;
};

#endif // PLAYTIMERWINDOW_H
