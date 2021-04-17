import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.2

import VideoModel 1.0

ApplicationWindow {
    id: root

    width: 1200
    height: 780

    minimumWidth: 700
    minimumHeight: 700

    visible: true
    visibility: "Maximized"

    Material.theme: Material.Dark
    Material.accent: Material.Grey

    title: qsTr("Video browser and editor")

    Item {
        id: viewIndex
        property int index: -1
    }

    MainView {
        id: mainView

        anchors.fill: parent

        visible: viewIndex.index == -1

        onShowRaw: viewIndex.index = 0
        onShowEdited: viewIndex.index = 1
    }
    VideoView {
        id: videoViewRaw

        anchors.fill: parent

        visible: viewIndex.index == 0

        model: VideoModel{
            editable: true
        }

        onBackTriggered: viewIndex.index = -1
        onLoadVideoTriggered: videoDialog.open()
        onVideoEditingFinished: videoViewEdited.model.addVideo(path)
    }
    VideoView {
        id: videoViewEdited

        anchors.fill: parent

        visible: viewIndex.index == 1

        model: VideoModel {
            editable: false
        }

        onBackTriggered: viewIndex.index = -1
    }

    FileDialog {
        id: videoDialog

        title: "Load video"
        folder: shortcuts.home
        nameFilters: [ "Videos (*.avi *.mov *.mp4 *.mkv)" ]
        defaultSuffix: ".mp4"
        selectExisting: true

        onAccepted: videoViewRaw.model.addVideo(videoDialog.fileUrl.toString())
    }
}
