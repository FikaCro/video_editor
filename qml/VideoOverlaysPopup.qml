import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import OverlayEffects 1.0

Popup {
    id: root

    signal overlaysApplyTriggered(variant overlays) // signal emitted if apply button is clicked, argument is the vector of overlays with 4 arguments needed to create one

    closePolicy: Popup.NoAutoClose // closed only on apply or close button

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    width: parent.width * 0.75
    height: parent.height * 0.75

    Row {
        width: parent.width

        anchors.top: parent.top
        anchors.bottom: rowButtons.top

        VideoOverlayItem { // number overlay visualization and property selection
            id: numberOverlay

            width: parent.width / 3.
            height: parent.height

            overlayType: OverlayEffects.Number
            timeMiliseconds: 300
        }

        VideoOverlayItem { // rectangle overlay visualization and property selection
            id: rectangleOverlay

            width: parent.width / 3.
            height: parent.height

            overlayType: OverlayEffects.Rectangle
            timeMiliseconds: 1000
        }

        VideoOverlayItem { // slider overlay visualization and property selection
            id: sliderOverlay

            width: parent.width / 3.
            height: parent.height

            overlayType: OverlayEffects.Slider
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
                // overlays as vector of each overlay containing the type, change time, position percantage x and y
                var overlays = [];
                if (numberOverlay.applied)
                {
                    overlays.push([numberOverlay.overlayType, numberOverlay.timeMiliseconds, numberOverlay.xPercentage, numberOverlay.yPercentage])
                }
                if (rectangleOverlay.applied)
                {
                    overlays.push([rectangleOverlay.overlayType, rectangleOverlay.timeMiliseconds,rectangleOverlay.xPercentage, rectangleOverlay.yPercentage])
                }
                if (sliderOverlay.applied)
                {
                    overlays.push([sliderOverlay.overlayType, sliderOverlay.timeMiliseconds, sliderOverlay.xPercentage, sliderOverlay.yPercentage])
                }
                root.close()

                if (overlays.length !== 0) // only if at leas one overlay is applied
                {
                    root.overlaysApplyTriggered(overlays)
                }
            }
        }

        Button {
            width: root.width / 3

            text: "Close"

            onClicked: root.close()
        }
    }
}
