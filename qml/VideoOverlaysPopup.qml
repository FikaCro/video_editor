import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Popup {
    id: root

    signal overlaysApplyTriggered(variant overlays)

    closePolicy: Popup.NoAutoClose

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    width: parent.width * 0.75
    height: parent.height * 0.75

    Row {
        width: parent.width

        anchors.top: parent.top
        anchors.bottom: rowButtons.top

        VideoOverlayItem {
            id: numberOverlay

            width: parent.width / 3.
            height: parent.height

            overlayType: "numberOverlay"
            timeMiliseconds: 300
        }

        VideoOverlayItem {
            id: rectangleOverlay

            width: parent.width / 3.
            height: parent.height

            overlayType: "rectangleOverlay"
            timeMiliseconds: 1000
        }

        VideoOverlayItem {
            id: sliderOverlay

            width: parent.width / 3.
            height: parent.height

            overlayType: "sliderOverlay"
            timeMiliseconds: 500
        }
    }


    Row {
        id: rowButtons

        width:  childrenRect.width
        height: parent.height / 10

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        spacing: width / 10

        Button {
            width: root.width / 3

            text: "Apply"

            onClicked:
            {
                var overlays = [];
                if (numberOverlay.applied)
                {
                    console.log(Qt.point(numberOverlay.xPos, numberOverlay.yPos))
                    overlays.push([numberOverlay.overlayType, numberOverlay.timeMiliseconds, Qt.point(numberOverlay.xPos, numberOverlay.yPos)])
                }
                if (rectangleOverlay.applied)
                {
                    overlays.push([rectangleOverlay.overlayType, rectangleOverlay.timeMiliseconds, Qt.point(rectangleOverlay.xPos, rectangleOverlay.yPos)])
                }
                if (sliderOverlay.applied)
                {
                    overlays.push([sliderOverlay.overlayType, sliderOverlay.timeMiliseconds, Qt.point(sliderOverlay.xPos, sliderOverlay.yPos)])
                }
                root.overlaysApplyTriggered(overlays)
                root.close()
            }
        }

        Button {
            width: root.width / 3

            text: "Close"

            onClicked: root.close()
        }
    }
}
