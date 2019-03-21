import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QGuov.Controller.ChatListController 1.0

Item {
  Item {
    id: header
    anchors.top: parent.top
    height: 50
    Text {
      anchors {
        left: parent.left
        verticalCenter: parent.verticalCenter
      }
      text: 'Chat page'
    }
  }

  ChatListController {
    globalStore: globalStoreModel
  }

  ListView {
    anchors {
      top: header.bottom
      left: parent.left
      right: parent.right
      bottom: parent.bottom
    }
    model: globalStoreModel.chatsModel
    spacing: 10
    delegate: Item {
      Rectangle {
        anchors {
          left: parent.left
          right: parent.right
          bottom: parent.bottom
        }
        height: 1
        color: 'blue'
      }

      property int iconSize: 80
      width: parent.width
      height: iconSize
      RowLayout {
        anchors {
          left: parent.left
          leftMargin: 15
          right: parent.right
          rightMargin: 15
        }
        height: parent.height

        Image {
          source: icon
          height: parent.height
          Layout.maximumHeight: iconSize
          Layout.maximumWidth: iconSize
        }
        ColumnLayout {
          Text {
            text: initials
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true
            topPadding: 8
            Rectangle {
              // debug
              anchors {
                left: parent.left
                right: parent.right
                top: parent.top
              }
              height: 1
              color: 'red'
            }
          }

          RowLayout {
            Text {
              text: "<i>last message:</i> <b>" + message + "</b>"
              Rectangle {
                anchors {
                  left: parent.left
                  right: parent.right
                  bottom: parent.bottom
                }
                height: 1
                color: 'red'
              }
              bottomPadding: 8
            }
            Text {
              text: date
              Layout.fillWidth: true
              Layout.alignment: Qt.AlignRight
              horizontalAlignment: Text.AlignRight
              Rectangle {
                // debug
                anchors {
                  top: parent.top
                  bottom: parent.bottom
                  right: parent.right
                }
                width: 1
                color: 'red'
              }
            }
          }
        }
      }
    }
  }
}
