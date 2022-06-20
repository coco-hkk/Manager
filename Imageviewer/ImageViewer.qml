import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs

Rectangle {
    id: root;
    visible: true;
    width: parent.width
    height: parent.height

    objectName: "qmlWin";

    property var localComp;
    property var localView;
    property var netComp;
    property var netView;

    function backKeyProcess(){
        if(root.localView !== undefined){
            root.localView.destroy();
            root.localView = undefined;
        }else if(root.netView !== undefined){
            root.netView.destroy();
            root.netView = undefined;
        }else{
            Qt.quit();
        }
    }

    Column {
        id: actionPanel;
        anchors.centerIn: parent;
        spacing: 4;

        FlatButton {
            id: find;
            iconSource: "icons/ic_find.png";
            text: qsTr("Search Internet");
            font.pointSize: 14;
            onClicked: {
                if(root.netComp === undefined){
                    root.netComp = Qt.createComponent("ImageDigger.qml");
                }
                if(root.netView === undefined){
                    root.netView = root.netComp.createObject(root, {"focus": true});
                    root.netView.back.connect(root.onNetViewBack);
                }
            }
        }
        FlatButton {
            id: local;
            iconSource: "icons/ic_archive.png";
            text: qsTr("Local Image");
            font.pointSize: 14;
            onClicked: {
                if(root.localComp === undefined){
                    root.localComp = Qt.createComponent("LocalViewer.qml");
                }
                if(root.localView === undefined && root.localComp.status === Component.Ready){
                    root.localView = root.localComp.createObject(root, {"focus": true});
                    root.localView.initInteractive();
                    root.localView.back.connect(root.onLocalViewBack);
                }
            }
        }
    }

    function onLocalViewBack(){
        localView.destroy();
        localView = undefined;
    }

    function onNetViewBack(){
        netView.destroy();
        netView = undefined;
    }
}
