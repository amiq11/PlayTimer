#ifndef PLAYTIMERWINDOW_H
#define PLAYTIMERWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlayTimerWindow;
}

class PlayTimerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PlayTimerWindow(QWidget *parent = 0);
    ~PlayTimerWindow();
    
private:
    Ui::PlayTimerWindow *ui;
};

#endif // PLAYTIMERWINDOW_H
