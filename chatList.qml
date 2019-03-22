import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QGuov.Controller.ChatListController 1.0

Page {
  background: Rectangle {
    color: "#f4f8f9"
  }

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
    id: chatListController
    globalStore: globalStoreModel
    stackView: stackViewController
  }

  ListView {
    id: listView
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
        // bottom blue line
        anchors.fill: parent
        z: -1
        color: 'white'
      }
      MouseArea {
        anchors.fill: parent
        onClicked: {
          globalStoreModel.currentChatId = id;
          console.log('clicked', id, 'id' )
          chatListController.goToChat();
        }
      }

      property int iconSize: 40
      width: parent.width
      height: 72
      RowLayout {
        anchors {
          left: parent.left
          leftMargin: 16
          right: parent.right
          rightMargin: 16
          top: parent.top
          bottom: parent.bottom
        }

        Image {
          source: icon
          Layout.alignment: Qt.AlignVCenter
          Layout.maximumHeight: iconSize
          Layout.maximumWidth: iconSize
        }
        spacing: 16
        ColumnLayout {
          spacing: 0
          Text {
            text: initials
            Layout.fillHeight: false
            font.pointSize: 16
            topPadding: 24 - font.pixelSize
            Rectangle {
              // debug initials top red
              anchors.fill: parent
              visible: false
              border.width: 1
              border.color: "red"
              opacity: 0.1
            }
          }

          RowLayout {
            Layout.fillHeight: true
            Text {
              text: "<i>last message:</i> <b>" + message + "</b>"
              font.pointSize: 12
              Rectangle {
                // debug lastMessage bottom red
                anchors.fill: parent
                visible: false
                opacity: 0.3
                border {
                  color: 'red'
                  width: 1
                }
              }
              bottomPadding: 8
            }
            Text {
              text: date
              Layout.fillWidth: true
              Layout.alignment: Qt.AlignRight
              horizontalAlignment: Text.AlignRight
              Rectangle {
                // debug date right red
                visible: false
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
