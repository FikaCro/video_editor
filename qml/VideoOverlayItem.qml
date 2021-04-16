import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: root

    property string overlayType
    property int timeMiliseconds

    readonly property int xPos: positionSpinBoxes.xPos
    readonly property int yPos: positionSpinBoxes.yPos
    readonly property bool applied: applyCheckBox.checked

    width: parent.width
    height: parent.height

    PositionSpiboxes {
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

            Loader {
                sourceComponent: {
                    if (overlayType == "numberOverlay")
                    {
                        return numberOverlay;
                    }
                    else if (overlayType == "rectangleOverlay")
                    {
                        return rectangleOverlay;
                    }
                    else if (overlayType == "sliderOverlay")
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
        id: numberOverlay

        Item {
            Label {
                id: number

                text: "0"

                x: positionSpinBoxes.xPos * (overlayRectangle.width - width)
                y: positionSpinBoxes.yPos * (overlayRectangle.height - height)
            }
            Timer {
                interval: root.timeMiliseconds
                running: true
                repeat: true

                onTriggered: {
                    number.text = Math.floor(Math.random() * 100).toString();
                }
            }
        }
    }

    Component {
        id: rectangleOverlay

        Rectangle {
            id: rectangleShape

            width: overlayRectangle.width * 0.1
            height: overlayRectangle.height * 0.1

            property real colorStart: 0
            property real colorEnd: 1

            gradient: Gradient {
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
                    rectangleShape.x = Math.floor(Math.random() * 100) / 100 * (overlayRectangle.width - rectangleShape.width);
                    rectangleShape.y = Math.floor(Math.random() * 100) / 100 * (overlayRectangle.height - rectangleShape.height);
                    rectangleShape.colorStart = Math.floor(Math.random() * 100) / 100;
                    rectangleShape.colorEnd = Math.floor(Math.random() * 100) / 100;
                }
            }
        }
    }

    Component {
        id: sliderOverlay

        Slider {
            id: slider

            enabled: false

            width: overlayRectangle.width / 3

            x: positionSpinBoxes.xPos * (overlayRectangle.width - width)
            y: positionSpinBoxes.yPos * (overlayRectangle.height - height)

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
