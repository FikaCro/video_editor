import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: root

    signal showRaw()
    signal showEdited()

    anchors.fill: parent

    Button {
        id: button_raw
        Label {
            text: "Raw videos"

            anchors.centerIn: parent
            width: parent.width * 0.8
            height: parent.height * 0.8

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 72
            fontSizeMode: Text.Fit
        }

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -width / 1.5

        width: parent.width / 3.0
        height: parent.height / 3.0

        onClicked: showRaw()
    }

    Button {
        id: button_edited
        Label {
            text: "Edited videos"

            anchors.centerIn: parent
            width: parent.width * 0.8
            height: parent.height * 0.8

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 72
            fontSizeMode: Text.Fit
        }

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: width / 1.5

        width: parent.width / 3.0
        height: parent.height / 3.0

        onClicked: showEdited()
    }
}
