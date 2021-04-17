import QtQuick 2.0
import QtQuick.Controls 2.12

// Self destructing on calling close()
Popup {
    id: root

    property real progress: 0

    signal abortTriggered()

    closePolicy: Popup.NoAutoClose

    ProgressBar {
        id: progressBar

        width: parent.width
        height: parent.height / 2

        anchors.top: parent.top

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

    onClosed: destroy(10000);
}
