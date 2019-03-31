import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QGuov.Controller.ChatController 1.0

Page {
  property alias listView: listView

  background: Rectangle {
    color: "#f4f8f9"
  }


  ChatController {
    id: chatController
    globalStore: globalStoreModel
    onMessagesLoaded: listView.positionViewAtEnd();
    onMessagesModelChanged: {
      listView.positionViewAtEnd();
    }
    onMessageSent: textField.clear();
    Component.onCompleted: listView.positionViewAtEnd();
  }


  Item {
    id: header
    height: 60
    width: parent.width
    anchors.top: parent.top
    Text {
      anchors {
        verticalCenter: parent.verticalCenter
        horizontalCenter: parent.horizontalCenter
      }
      text: globalStoreModel.currentChat.chatName
    }
  }

  ListView {
    id: listView
    anchors {
      top: header.bottom
      bottom: sendMessageControls.top
    }
    width: parent.width
    // model: ListModel {
    //     ListElement {
    //         initials: 'user1'
    //         message: 'message'
    //         isMe: true
    //     }
    //     ListElement {
    //         initials: 'user2'
    //         message: 'message2'
    //         isMe: false
    //     }
    //     ListElement {
    //         initials: 'user1'
    //         message: 'message-------------------------\nnew line\nnew one'
    //         isMe: true
    //     }
    // }
    model: globalStoreModel.messagesModel
    spacing: 10

    delegate: RowLayout {
      width: parent.width
      layoutDirection: isMe ? Qt.RightToLeft : Qt.LeftToRight
      Pane {
        id: paneMessage
          background: Rectangle {
          color: 'lightgray'
          radius: 10
        }

        ColumnLayout {
          id: rowLayout
          Text {
            id: messageText
            text: message
            wrapMode: Text.WordWrap
            horizontalAlignment: isMe ? Text.AlignRight : Text.AlignLeft
          }
          Text {
            text: (new Date()).toString()
            horizontalAlignment: isMe ? Text.AlignRight : Text.AlignLeft
          }
        }
      }
    }
  }

  RowLayout {
    id: sendMessageControls
    anchors.bottom: parent.bottom
    Layout.maximumHeight: 40
    width: parent.width
    TextField {
      id: textField
      Layout.fillHeight: false
      Layout.fillWidth: true
      placeholderText: qsTr('Введите сообщение...')
    }
    Button {
      Layout.fillHeight: false
      Layout.fillWidth: false
      display: AbstractButton.IconOnly
      icon.source: 'baseline_send_black_18dp.png'
      onClicked: {
        console.log('sending message');
        chatController.sendMessage(textField.text);
      }
    }
  }

}
