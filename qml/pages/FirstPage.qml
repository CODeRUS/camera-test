import QtQuick 2.1
import Sailfish.Silica 1.0
import QtMultimedia 5.0
import camera.test 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    Component.onCompleted: {
        _complete = true
    }

    Component.onDestruction: {
        if (camera.cameraState != Camera.UnloadedState) {
            camera.cameraState = Camera.UnloadedState
        }
    }

    property bool _complete: false
    property bool _unload: false

    function reload() {
        if(_complete) {
            _unload = true;
        }
    }

    VideoOutput {
        id: viewfinder

        anchors.centerIn: page
        height: page.isPortrait ? page.height : page.width
        width: page.isPortrait ? page.width : page.height

        source: camera
    }

    CameraHelper {
        id: cameraHelper

        camera: camera
        device: "primary"
        viewfinderResolution: Qt.size(Screen.height, Screen.width)

        onDeviceChanged: page.reload()
        onViewfinderResolutionChanged: page.reload()
    }

    Camera {
        id: camera

        captureMode: Camera.CaptureStillImage
        cameraState: page._complete && !page._unload ? Camera.ActiveState : Camera.UnloadedState

        exposure.exposureMode: Camera.ExposureAuto

        focus.focusMode: Camera.FocusContinuous
        focus.focusPointMode: Camera.FocusPointAuto

        flash.mode: Camera.FlashAuto

        imageCapture {

            onImageCaptured: {
                console.log(preview)
            }

            onImageSaved: {
                console.log(path)
            }
        }

        onCameraStatusChanged: {
            if (cameraStatus == Camera.LoadedStatus) {
                camera.exposure.setAutoAperture()
                camera.exposure.setAutoIsoSensitivity()
                camera.exposure.setAutoShutterSpeed()
            }
        }
    }

    Timer {
        id: reloadTimer

        interval: 10
        running: page._unload && camera.cameraStatus == Camera.UnloadedStatus

        onTriggered: {
            page._unload = false
        }
    }

    MouseArea {
        id: captureButton
        property bool down: pressed && containsMouse

        anchors {
            bottom: parent.bottom
            right: parent.right
            rightMargin: page.isLandscape ? 0 : (Screen.width / 2 - width / 2)
        }

        enabled: camera.cameraState == Camera.ActiveState && camera.cameraStatus == Camera.ActiveStatus

        height: Theme.itemSizeExtraLarge
        width: Theme.itemSizeExtraLarge
        z: 1

        Rectangle {
            anchors.centerIn: parent

            height: Theme.itemSizeSmall
            width: height

            radius: height / 2

            color: Theme.highlightDimmerColor
            opacity: 0.6
        }

        Image {
            id: icon

            anchors.centerIn: parent

            opacity: parent.down ? 0.5 : 1.0
            source: "image://theme/icon-camera-shutter-release?" + Theme.highlightColor
        }

        onClicked: {
            camera.imageCapture.captureToLocation("/tmp/PF_Camera.jpg")
        }
    }
}


