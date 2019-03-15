import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

ApplicationWindow {
  id: window
  visible: true
  width: 480
  height: 800
  title: qsTr("ГУОВ")

  Material.theme: Material.Light
  Material.accent: Material.Dark

  property real controlsWidth: width * 0.4

  Image {
    id: logo
    source: "https://scontent.frix2-1.fna.fbcdn.net/v/t1.0-9/14264059_984166355063121_4796291850236353168_n.png?_nc_cat=107&_nc_pt=1&_nc_ht=scontent.frix2-1.fna&oh=3b970760c8c3e41e2580a84c99d1d9ab&oe=5D2345C6"
    anchors {
      horizontalCenter: parent.horizontalCenter
      top: parent.top
      topMargin: 100
    }
    width: parent.width * 0.8
    height: width
  }

  TextField {
    id: login
    anchors {
      top: logo.bottom
      topMargin: 50
      horizontalCenter: parent.horizontalCenter
    }
    width: controlsWidth
    placeholderText: qsTr("Логин")
  }
  TextField {
    id: password
    anchors {
      top: login.bottom
      horizontalCenter: parent.horizontalCenter
    }
    width: controlsWidth
    placeholderText: qsTr("Пароль")
  }
  Button {
    id: submit
    text: qsTr("Войти")
    highlighted: true
    Material.background: Material.Teal
    anchors {
      top: password.bottom
      topMargin: 20
      horizontalCenter: parent.horizontalCenter
    }
    width: controlsWidth
  }
}
