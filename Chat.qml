import QtQuick 2.0
import QGuov.Controller.ChatController 1.0

Item {
  ChatController {
    globalStore: globalStoreModel
  }

  Component.onCompleted: console.log('chat is openned');
}
