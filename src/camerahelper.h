#ifndef CAMERAHELPER_H
#define CAMERAHELPER_H

#include <QObject>
#include <QSize>
#include <QQmlParserStatus>

class CameraHelper : public QObject, public QQmlParserStatus
{
    Q_OBJECT
public:
    explicit CameraHelper(QObject *parent = 0);

    Q_PROPERTY (QObject *camera READ camera WRITE setCamera NOTIFY cameraChanged)
    QObject *camera();
    void setCamera(QObject *camera);

    Q_PROPERTY(QString device READ device WRITE setDevice NOTIFY deviceChanged)
    QString device() const;
    void setDevice(const QString &device);

    Q_PROPERTY(QSize viewfinderResolution READ viewfinderResolution WRITE setViewfinderResolution NOTIFY viewfinderResolutionChanged)
    QSize viewfinderResolution() const;
    void setViewfinderResolution(const QSize &viewfinderResolution);

    void classBegin();
    void componentComplete();

private:
    QObject *m_camera;
    QString  m_device;
    QSize    m_viewfinderResolution;

signals:
    void cameraChanged();
    void deviceChanged();
    void viewfinderResolutionChanged();

public slots:

};

#endif // CAMERAHELPER_H
