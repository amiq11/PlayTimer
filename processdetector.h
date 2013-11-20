#ifndef PROCESSDETECTOR_H
#define PROCESSDETECTOR_H

#include <QObject>
#include <QTimer>

class ProcessDetector : public QObject
{
    Q_OBJECT
public:
    explicit ProcessDetector(QObject *parent = 0, QString name = QString());
    bool isDetected() { return detected; };
    QString &getTarget() { return target; };
signals:
    void processStarted();
    void processStopped();
    void targetChanged(QString name);
public slots:
    void setProcessName(QString &name);
    void checkProcess();
    void start();
    void stop();
private:
    bool detected;
    static const int interval_ms;
    QTimer timer;
    QString target;
};

#endif // PROCESSDETECTOR_H
