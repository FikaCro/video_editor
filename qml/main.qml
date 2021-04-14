import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Window {
    id: root

    width: 1200
    height: 780

    visible: true
    visibility: "Maximized"

    Material.theme: Material.Dark
    Material.accent: Material.Grey

    title: qsTr("Video browser and editor")

    Item {
        id: itemIndex
        property int index: -1
    }

    MainView {
        id: mainView
        visible: itemIndex.index == -1

        onShowRaw: itemIndex.index = 0
        onShowEdited: itemIndex.index = 1
    }
    VideoPreview {
        id: videoPreviewRaw
        visible: itemIndex.index == 0
        onBackTriggered: itemIndex.index = -1
    }
    VideoPreview {
        id: videoPreviewEdited
        visible: itemIndex.index == 1
        onBackTriggered: itemIndex.index = -1
    }
}
