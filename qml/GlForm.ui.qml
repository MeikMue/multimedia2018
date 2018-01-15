import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import GlComponents 1.0

Item {
    property Button rotateRightButton: rotateRightButton
    property alias mouseArea: mouseArea
    MyGlItem {
        id: myGlItem
        anchors.fill: parent


        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
            onClicked: myGlItem.mousePressed(mouseX,mouseY)

        }

        RowLayout {
            id: rowLayout
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter



            Button {
                id: rotateLeftButton
                text: qsTr("Rotate Left")
            }

            Button {
                id: rotateRightButton
                text: qsTr("Rotate Right")
                onClicked: myGlItem.toggleMove()
            }
        }


    }
}
