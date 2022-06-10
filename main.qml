import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs

Window {
    width: 640
    height: 480
    visible: true
    minimumWidth: 480
    minimumHeight: 380
    title: qsTr("Image View")

    BusyIndicator {
        id: busy
        running: false
        anchors.centerIn: parent
        z: 2
    }

    Text {
        id: stateLabel
        visible: false
        anchors.centerIn: parent
        z: 3
    }

    Image {
        id: imageView
        asynchronous: true
        cache: false
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        onStatusChanged: {
            if (imageView.status === Image.Loading) {
                busy.running = true
                stateLabel.visible = false
            }
            else if (imageView.status === Image.Ready) {
                busy.running = false
            }
            else if (imageView.status === Image.Error) {
                busy.running = false
                stateLabel.visible = true
                stateLabel.text = "ERROR"
            }
        }
    }

    Button {
        id: openFile
        text: "Open"
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        background: Rectangle {
            implicitWidth: 70
            implicitHeight: 25
            color: openFile.hovered ? "#c0c0c0" : "#a0a0a0"
            border.width: openFile.pressed ? 2 : 1
            border.color: (openFile.hovered || openFile.pressed) ? "green" : "#888888"
        }
        onClicked: fileDialog.open()
        z: 4
    }

    Text {
        id: imagePath
        anchors.left: openFile.right
        anchors.leftMargin: 8
        anchors.verticalCenter: openFile.verticalCenter
        font.pixelSize: 18
    }

    FileDialog {
        id: fileDialog
        title: "请选择文件"
        nameFilters: ["Image Files (*.jpg *.png *.gif)",
            "Bitmap File (*.bmp)", "* (*.*)"]
        selectedNameFilter.index: 0
        onAccepted: {
            imageView.source = fileDialog.currentFile
            var imageFile = imageView.source.toString()
            imagePath.text = imageFile.slice(7)
        }
    }
}
