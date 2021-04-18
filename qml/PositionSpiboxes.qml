import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    readonly property double xPercentage: spinBoxX.value // value of the x percentage spinbox
    readonly property double yPercentage: spinBoxY.value // value of the y percentage spinbox

    Column {
        width: parent.width
        height: parent.height

        Column {
            width: parent.width
            height: parent.height / 2

            spacing: 5

            Label {
                text: "x [%]"

                width: parent.width
                height: parent.height / 4

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                font.pointSize: 12
                minimumPointSize: 6
                fontSizeMode: Text.Fit
            }
            SpinBox {
                id: spinBoxX

                width: parent.width
                height: parent.height / 2

                from: 0
                to: 100
            }
        }
        Column {
            width: parent.width
            height: parent.height / 2

            spacing: 5

            Label {
                text: "y [%]"

                width: parent.width
                height: parent.height / 4

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                font.pointSize: 12
                minimumPointSize: 6
                fontSizeMode: Text.Fit
            }
            SpinBox {
                id: spinBoxY

                width: parent.width
                height: parent.height / 2

                from: 0
                to: 100
            }
        }
    }
}
