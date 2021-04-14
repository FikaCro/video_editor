import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.2

import VideoModel 1.0

ApplicationWindow {
    id: root

    width: 1200
    height: 780

    minimumWidth: 600
    minimumHeight: 390

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
        model: VideoModel{
            editable: true
        }
        onBackTriggered: itemIndex.index = -1
        onLoadVideoTriggered: videoDialog.open()
    }
    VideoPreview {
        id: videoPreviewEdited
        visible: itemIndex.index == 1
        model: VideoModel
        {
            editable: false
        }
        onBackTriggered: itemIndex.index = -1
    }

    FileDialog {
        id: videoDialog

        title: "Load video"
        folder: shortcuts.home
        nameFilters: [ "Videos (*.avi *.mp4 *.mkv)" ]
        defaultSuffix: ".mp4"
        selectExisting: true

        onAccepted: videoPreviewRaw.model.addVideo(videoDialog.fileUrl.toString())
    }

}
