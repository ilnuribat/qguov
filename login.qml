import QtQuick 2.0
import QtQuick.Controls 2.5
import QGuov.Controller.Login 1.0
import QtQuick.Controls.Material 2.3

Item {
  LoginController {
      id: loginController
      login: login.text
      password: password.text
  }

  Image {
    id: logo
    source: "https://scontent.frix2-1.fna.fbcdn.net/v/t1.0-9/14264059_984166355063121_4796291850236353168_n.png?_nc_cat=107&_nc_pt=1&_nc_ht=scontent.frix2-1.fna&oh=3b970760c8c3e41e2580a84c99d1d9ab&oe=5D2345C6"
    anchors {
      horizontalCenter: parent.horizontalCenter
      bottom: login.top
    }
    width: parent.width * 0.8
    height: width
  }

  TextField {
    id: login
    anchors {
      bottom: password.top
      horizontalCenter: parent.horizontalCenter
    }
    width: controlsWidth
    placeholderText: qsTr("Логин")
    text: loginController.login
  }
  TextField {
    id: password
    anchors {
      bottom: submit.top
      horizontalCenter: parent.horizontalCenter
    }
    width: controlsWidth
    placeholderText: qsTr("Пароль")
    text: loginController.password
  }
  Button {
    id: submit
    text: qsTr("Войти")
    highlighted: true
    Material.background: Material.Teal
    anchors {
      bottom: parent.bottom
      bottomMargin: 20
      horizontalCenter: parent.horizontalCenter
    }
    width: controlsWidth
    onClicked: loginController.submitLogin()
//    onClicked: stackView.push(Qt.resolvedUrl('./chat.qml'))
  }

}
