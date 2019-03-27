import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QGuov.Controller.StackView 1.0
import QGuov.Model.GlobalStore 1.0
import '.'

ApplicationWindow {
  id: window
  visible: true
  width: 500
  height: 500
  title: qsTr("ГУОВ Стимул")

  property bool isGlobalStoreReady: false
  property bool isStackViewReady: false

  GlobalStore {
    id: globalStoreModel
    Component.onCompleted: {
      isGlobalStoreReady = true;
      if (isStackViewReady && isGlobalStoreReady) {
        stackViewController.handleAuthToken()
      }
    }
  }

  StackViewController {
    id: stackViewController
    objectName: "stackView"
    onGoToPageChanged: {
      switch (page) {
        case 'login':
          stackView.replace(Qt.resolvedUrl('./login.qml'));
          break;

        case 'chatList':
          stackView.replace(Qt.resolvedUrl('./chatList.qml'));
          break;
        case 'chat':
          stackView.push(Qt.resolvedUrl('./Chat.qml'));
          break;
        case 'Realtime':
          stackView.replace(Qt.resolvedUrl('./Realtime.qml'))
          break;
        default:
          console.error('no page on signal!');
      }
    }

    Component.onCompleted: {
      isStackViewReady = true;
      if (isStackViewReady && isGlobalStoreReady) {
        stackViewController.handleAuthToken();
      }
    }
  }

  StackView {
    id: stackView
    anchors.fill: parent
    focus: true
    initialItem: Qt.resolvedUrl('./initPage.qml')

    Keys.onReleased: {
      if (event.key === Qt.Key_Back || event.key === Qt.Key_Escape) {
        stackView.pop();
        event.accepted = true;
      }
    }
  }

  Material.theme: Material.Light
  Material.accent: Material.Dark
}
