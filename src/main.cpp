#include <QtQuick>
#include <sailfishapp.h>
#include "camerahelper.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
    qmlRegisterType<CameraHelper>("camera.test", 1, 0, "CameraHelper");
    view->setSource(SailfishApp::pathTo("qml/main.qml"));
    view->show();
    return application->exec();
}
