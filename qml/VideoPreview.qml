import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
Item {
    id: root

    anchors.fill: parent

    signal backTriggered()

    RoundButton {
        id: buttonBack
        x: 20
        y: 20

        Material.background: Material.Grey
        Material.foreground: "black"
        text: "Back"

        onClicked: backTriggered()
    }
}
