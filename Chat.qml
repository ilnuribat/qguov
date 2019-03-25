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
    globalStore: globalStoreModel
    onMessagesLoaded: listView.positionViewAtEnd();
  }

  Item {
    id: header
    height: 30
    width: parent.width
    anchors.top: parent.top
    Text {
      anchors {
        verticalCenter: parent.verticalCenter
        horizontalCenter: parent.horizontalCenter
      }
      text: 'chat name'
    }
  }

  ListModel {
    ListElement {
      message: "hi!"
      userName: "Ilnur"
    }
    ListElement {
      userName: "Kirill"
      message: 'это текст-"рыба", часто используемый в печати и вэб-дизайне. Lorem Ipsum является стандартной "рыбой" для текстов на латинице с начала XVI века. В то время некий безымянный печатник создал большую коллекцию размеров и форм шрифтов, используя Lorem Ipsum для распечатки образцов. Lorem Ipsum не только успешно пережил без заметных изменений пять веков, но и перешагнул в электронный дизайн.'
    }
  }


  ListView {
    id: listView
    anchors {
      top: header.bottom
      bottom: parent.bottom
    }
    width: parent.width
    model: globalStoreModel.messagesModel
    spacing: 10

    delegate: Item {
      Rectangle {
        anchors.fill: parent
        color: 'white'
      }

      width: parent.width
      height: rowLayout.height
      RowLayout {
        id: rowLayout
        width: parent.width
        height: messageText.contentHeight
        Text {
          Layout.fillWidth: false
          Layout.alignment: Qt.AlignTop
          text: "<b>" + initials + ":</b>"
        }
        Text {
          id: messageText
          text: message
          Layout.fillWidth: true
          wrapMode: Text.WordWrap
        }
      }
    }

  }

  Component.onCompleted: {
    listView.positionViewAtEnd();
    console.log('chat is openned');
  }
}
