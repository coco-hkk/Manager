import QtQuick
import QtQuick.Window
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    minimumWidth: 320
    minimumHeight: 240
    title: qsTr("Manager")

    header: Label {
        text: view.currentItem.title
        font.pixelSize: 25
        horizontalAlignment: Text.AlignHCenter
    }

    SwipeView {
        id: view
        anchors.fill: parent

        Page {
            title: qsTr("Home")

            Label {
                text: qsTr("Manger Tool")
                anchors.centerIn: parent
                font.pixelSize: 40
            }
        }
        Page {
            id: img
            title: qsTr("Image")

            Component.onCompleted: {
                var component = Qt.createComponent("qrc:/ImageViewer.qml");
                //console.log("status: " + component.status + " err: " + component.errorString());
                if (component.status === Component.Ready)
                {
                    component.createObject(img);
                }
            }
        }
    }
}
