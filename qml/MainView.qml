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

        width: parent.width / 3.0
        height: parent.height / 3.0

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -width / 1.5

        Label {
            text: "Raw videos"

            width: parent.width * 0.8
            height: parent.height * 0.8

            anchors.centerIn: parent

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pointSize: 72
            fontSizeMode: Text.Fit
        }
        onClicked: showRaw()
    }

    Button {
        id: button_edited

        width: parent.width / 3.0
        height: parent.height / 3.0

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: width / 1.5

        Label {
            text: "Edited videos"

            width: parent.width * 0.8
            height: parent.height * 0.8

            anchors.centerIn: parent

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pointSize: 72
            fontSizeMode: Text.Fit
        }
        onClicked: showEdited()
    }
}
