#include "stackviewcontroller.h"

StackViewController::StackViewController(QObject *parent) : QObject(parent) {
}

void StackViewController::handleAuthToken() {
  settings = new QSettings();
  QString token = settings->value("token").toString();

  if (token.length() == 0) {
    qDebug() << "no token found";
    // show login page
    emit this->goToPageChanged("login");

    return;
  }

  emit this->goToPageChanged("chatList");
}

void StackViewController::goChatsListPage() {
  emit this->goToPageChanged("chatList");
}
