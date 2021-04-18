import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {
    id: root

    property real progress: 0 // property used for updating progress bar

    signal abortTriggered() // signal triggered on abort button clicked

    closePolicy: Popup.NoAutoClose // popup can only be closed by pressing the cancel button

    Label {
        id: labelProgress

        text: "Progress..."

        width: parent.width
        height: parent.height / 5

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop

        minimumPointSize: 8
        font.pointSize: 72
        fontSizeMode: Text.Fit
    }

    ProgressBar {
        id: progressBar

        width: parent.width
        height: parent.height / 2

        anchors.top: labelProgress.bottom

        from: 0
        to: 100
        value: root.progress
    }
    Button {
        text: "Cancel"

        width: parent.width / 2
        height: parent.height / 4

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        onClicked: root.abortTriggered()
    }
}
