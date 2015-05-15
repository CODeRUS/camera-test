#include "camerahelper.h"

#include <QMediaObject>
#include <QMediaService>
#include <QVideoDeviceSelectorControl>
#include <QCameraViewfinderSettingsControl>

CameraHelper::CameraHelper(QObject *parent) :
    QObject(parent),
    m_camera(NULL),
    m_device("primary"),
    m_viewfinderResolution(-1, -1)
{
}

QObject *CameraHelper::camera()
{
    return m_camera;
}

void CameraHelper::setCamera(QObject *camera)
{
    if (m_camera != camera) {
        m_camera = camera;
        Q_EMIT cameraChanged();
    }
}

QString CameraHelper::device() const
{
    return m_device;
}

void CameraHelper::setDevice(const QString &device)
{
    if (m_device != device) {
        m_device = device;

        if (m_camera) {
            QMediaObject *mediaObject =
                    m_camera ? qobject_cast<QMediaObject *>(m_camera->property("mediaObject").value<QObject*>())
                             : 0;

            if (mediaObject) {
                QVideoDeviceSelectorControl *videoDevice =
                        mediaObject->service()->requestControl<QVideoDeviceSelectorControl*>();

                if (videoDevice) {
                    const int value = (m_device == "primary") ? 0 : 1;

                    if (videoDevice->selectedDevice() != value) {
                        videoDevice->setSelectedDevice(value);
                    }
                }
            }
        }

        Q_EMIT deviceChanged();
    }
}

QSize CameraHelper::viewfinderResolution() const
{
    return m_viewfinderResolution;
}

void CameraHelper::setViewfinderResolution(const QSize &viewfinderResolution)
{
    if (m_viewfinderResolution != viewfinderResolution) {
        m_viewfinderResolution = viewfinderResolution;

        if (m_camera) {
            QMediaObject *mediaObject =
                    m_camera ? qobject_cast<QMediaObject *>(m_camera->property("mediaObject").value<QObject*>())
                             : 0;

            if (mediaObject) {
                QCameraViewfinderSettingsControl *viewfinderSettings =
                        mediaObject->service()->requestControl<QCameraViewfinderSettingsControl*>();

                if (viewfinderSettings)
                {
                    if (viewfinderSettings->viewfinderParameter(QCameraViewfinderSettingsControl::Resolution).toSize() != m_viewfinderResolution) {
                        viewfinderSettings->setViewfinderParameter(QCameraViewfinderSettingsControl::Resolution, m_viewfinderResolution);
                    }
                }
            }
        }

        Q_EMIT viewfinderResolutionChanged();
    }
}

void CameraHelper::classBegin()
{

}

void CameraHelper::componentComplete()
{

}
