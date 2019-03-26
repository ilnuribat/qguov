import QtQuick 2.0

Item {
  Text {
    text: "checking realtime"
  }
  Component.onCompleted: {
      globalStoreModel.startSubscriptions();
  }
}
