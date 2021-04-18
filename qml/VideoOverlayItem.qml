import QtQuick 2.0
import QtQuick.Controls 2.12

import OverlayEffects 1.0

Item {
    id: root

    property variant overlayType // property defining overlay type as OverlayEffects enum
    property int timeMiliseconds // property defining the change time in miliseconds

    readonly property int xPercentage: positionSpinBoxes.xPercentage // property defining the desired overlay x position as percentage of frame width
    readonly property int yPercentage: positionSpinBoxes.yPercentage // property defining the desired overlay y position as percentage of frame height
    readonly property bool applied: applyCheckBox.checked // property defining if the overlay is selected

    PositionSpiboxes { // overlay position spinboxes
        id: positionSpinBoxes

        width: parent.width
        height: parent.height * 0.25

        enabled: applyCheckBox.checked
    }

    Rectangle {
        width: parent.width

        anchors.top: positionSpinBoxes.bottom
        anchors.bottom: applyCheckBox.top

        color: "transparent"

        border.color: "white"
        border.width: 1

        Rectangle {
            id: overlayRectangle

            anchors.fill: parent
            anchors.margins: 5

            color: "transparent"

            Loader { // loader component based on the desired overlay effect
                sourceComponent: {
                    if (overlayType === OverlayEffects.Number)
                    {
                        return numberOverlay;
                    }
                    else if (overlayType === OverlayEffects.Rectangle)
                    {
                        return rectangleOverlay;
                    }
                    else if (overlayType === OverlayEffects.Slider)
                    {
                        return sliderOverlay;
                    }
                    return emptyOverlay;
                }
            }
        }
    }

    CheckBox {
        id: applyCheckBox

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        text: "Apply"
    }

    Component {
        id: emptyOverlay

        Label {
            text: "Overlay not supported"
        }
    }

    Component {
        id: numberOverlay // random changing number value with constant position overlay

        Item {
            Label {
                id: number

                text: "0"

                x: positionSpinBoxes.xPercentage / 100.0 * (overlayRectangle.width - width) // position defiend as percentage of width
                y: positionSpinBoxes.yPercentage / 100.0 * (overlayRectangle.height - height) // position defined as percentage of height
            }
            Timer {
                interval: root.timeMiliseconds
                running: true
                repeat: true

                onTriggered: {
                    number.text = Math.floor(Math.random() * 100).toString(); // change number value with the desired time in miliseconds
                }
            }
        }
    }

    Component {
        id: rectangleOverlay // random changing position and gradient rectangle overlay

        Rectangle {
            id: rectangleShape

            width: overlayRectangle.width * 0.1 // rectangle size as 10 % of frame width/height
            height: overlayRectangle.height * 0.1

            property real colorStart: 0 // property for gradient start hue value
            property real colorEnd: 1 // property for gradient end hue value

            gradient: Gradient { // two color gradient
                GradientStop {
                    position: 0.0
                    color: Qt.hsla(rectangleShape.colorStart, 1, 0.5, 1)
                }
                GradientStop {
                    position: 1.0
                    color: Qt.hsla(rectangleShape.colorEnd, 1, 0.5, 1)
                }
            }

            Timer {
                interval: root.timeMiliseconds
                running: true
                repeat: true

                onTriggered: {
                    // change rectangle position over the time but keeping it inside the frame dimensions
                    rectangleShape.x = Math.floor(Math.random() * 100) / 100 * (overlayRectangle.width - rectangleShape.width);
                    rectangleShape.y = Math.floor(Math.random() * 100) / 100 * (overlayRectangle.height - rectangleShape.height);
                    // change rectangle gradient color (its hue value!) over the time
                    rectangleShape.colorStart = Math.floor(Math.random() * 100) / 100;
                    rectangleShape.colorEnd = Math.floor(Math.random() * 100) / 100;
                }
            }
        }
    }

    Component {
        id: sliderOverlay // slider sliding from min to mix in a desired time at the desired position

        Slider {
            id: slider

            enabled: false

            width: overlayRectangle.width / 3

            x: positionSpinBoxes.xPercentage / 100.0 * (overlayRectangle.width - width)
            y: positionSpinBoxes.yPercentage / 100.0 * (overlayRectangle.height - height)

            from: 0
            to: 1

            Timer {
                interval: 1
                running: true
                repeat: true

                property real increment: 1

                onTriggered: {
                    slider.value = slider.value + increment * (slider.to - slider.from) / (root.timeMiliseconds / 2.0);

                    if (slider.value == slider.to)
                    {
                        increment = -1;
                    }
                    if (slider.value == slider.from)
                    {
                        increment = 1;
                    }
                }
            }
        }
    }
}
