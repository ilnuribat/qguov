import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.12
import QGuov.Controller.Login 1.0

Item {
  LoginController {
    id: loginController
    login: login.text
    password: password.text
    stackView: stackViewController
    Component.onCompleted: console.log('login controller completed');
  }
  Item {
    anchors {
      top: parent.top
      bottom: columnLayout.top
      left: parent.left
      right: parent.right
    }
    Image {
      id: logo
      anchors {
        horizontalCenter: parent.horizontalCenter
        verticalCenter: parent.verticalCenter
      }

      source: "https://scontent.frix2-1.fna.fbcdn.net/v/t1.0-9/14264059_984166355063121_4796291850236353168_n.png?_nc_cat=107&_nc_pt=1&_nc_ht=scontent.frix2-1.fna&oh=3b970760c8c3e41e2580a84c99d1d9ab&oe=5D2345C6"
      width: 250
      height: width
    }
  }


  ColumnLayout {
    id: columnLayout
    anchors {
      bottom: parent.bottom
      bottomMargin: 20
      horizontalCenter: parent.horizontalCenter
    }
    width: parent.width * 0.8

    TextField {
      id: login
      Layout.alignment: Qt.AlignCenter
      Layout.fillHeight: false
      placeholderText: qsTr("Логин")
      text: loginController.login
    }
    TextField {
      id: password
      placeholderText: qsTr("Пароль")
      Layout.alignment: Qt.AlignCenter
      Layout.fillHeight: false
      text: loginController.password
    }
    Button {
      text: qsTr("Войти")
      highlighted: true
      Layout.alignment: Qt.AlignCenter
      Layout.fillHeight: false
      Material.background: Material.Teal
      onClicked: loginController.submitLogin()
    }
    Text {
      id: resultMessage
      text: loginController.resultMessage
      Layout.alignment: Qt.AlignCenter
      Layout.fillHeight: false
    }
  }
}
