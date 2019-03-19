import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

Page {
  anchors.fill: parent
  header: Item {
    anchors.top: parent.top
    height: 50
    Rectangle {
      anchors {
        bottom: parent.bottom
      }
      width: parent.width
      color: 'red'
      height: 1
    }

    Text {
      anchors {
        left: parent.left
        verticalCenter: parent.verticalCenter
      }
      text: 'Chat page'
    }
  }
}
