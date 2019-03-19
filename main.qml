import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QGuov.Controller.Login 1.0
import QGuov.Controller.StackView 1.0
import '.'

ApplicationWindow {
  id: window
  visible: true
  width: 500
  height: 900
  title: qsTr("ГУОВ")

  StackViewController {
    id: stackViewController
    onGoToPageChanged: {
      console.log('page is:', page);
      switch (page) {
        case 'login':
          stackView.replace(Qt.resolvedUrl('./login.qml'));
          break;

        case 'chatList':
          stackView.replace(Qt.resolvedUrl('./chatList.qml'));
          break;
        default:
          console.error('no page on signal!');

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

  property real controlsWidth: width * 0.4

  Component.onCompleted: stackViewController.handleAuthToken();
}
