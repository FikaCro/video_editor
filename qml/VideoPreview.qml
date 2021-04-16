import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtMultimedia 5.12

import VideoModel 1.0

Item {
    id: root

    anchors.fill: parent

    signal backTriggered()
    signal loadVideoTriggered()

    property variant model: model

    focus: true

    PathView {
        id: pathView

        focus: true

        anchors.fill: parent
        anchors.topMargin: buttonBack.y + buttonBack.height / 2

        pathItemCount: 9
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlightRangeMode: PathView.StrictlyEnforceRange

        model: root.model
        delegate: Rectangle {
            id: item
            height: parent.height * 0.5
            width: parent.width * 0.25

            color: "transparent"

            z: PathView.iconOrder
            scale: PathView.iconScale

            focus: true

            Rectangle {
                width: parent.width
                height: parent.height * 0.7

                color: "darkgrey"

                anchors.top: parent.top

                Label {
                    text: basename(path)

                    anchors.centerIn: parent
                    width: parent.width * 0.8
                    height: parent.height * 0.8

                    wrapMode: "Wrap"

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 72
                    fontSizeMode: Text.Fit

                    function basename(str)
                    {
                        return (str.slice(str.lastIndexOf("/")+1))
                    }
                }
                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        video.source = path
                        video.visible = true
                        video.play()
                        video.z = 999
                    }
                }
            }

            Button {
                id: button_edit

                visible: model.editable

                Label {
                    text: "Edit"

                    anchors.centerIn: parent
                    width: parent.width * 0.8
                    height: parent.height * 0.8

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 72
                    fontSizeMode: Text.Fit
                }

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom

                width: parent.width / 3.0
                height: parent.height * 0.2

                onClicked: showEdited()
            }
        }

        path: Path {
            startX: 0
            startY: parent.height / 2
            PathAttribute {
                name: "iconScale"
                value: 0.3
            }
            PathAttribute {
                name: "iconOrder"
                value: 0
            }

            PathLine {
                x: parent.width / 2
                y: parent.height / 2
            }
            PathAttribute {
                name: "iconScale"
                value: 1.2
            }
            PathAttribute {
                name: "iconOrder"
                value: 10
            }

            PathLine {
                x: parent.width
                y: parent.height / 2
            }
        }
    }

    RoundButton {
        id: buttonBack
        x: 20
        y: 20

        text: "Back"

        onClicked: backTriggered()
    }

    RoundButton {
        id: buttonLoadVideo
        x: parent.width - 20 - width
        y: 20

        visible: model.editable

        text: "Load video"

        onClicked: loadVideoTriggered()
    }

    Video {
        id: video
        visible: false

        muted: true

        anchors.fill: parent

        focus: true

        MouseArea {
            anchors.fill: parent

            onDoubleClicked: {
                video.stop()
                video.source = ""
                video.visible = false
            }
        }
    }
}
