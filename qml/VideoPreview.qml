import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import VideoModel 1.0

Item {
    id: root

    anchors.fill: parent

    signal backTriggered()
    signal loadVideoTriggered()

    property variant model: model

    PathView {
        id: pathView

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

            border.width: 5
            border.color: "white"
            color: "darkgrey"

            z: PathView.iconOrder
            scale: PathView.iconScale
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
}
