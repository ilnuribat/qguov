#include "stackviewcontroller.h"

StackViewController::StackViewController(QObject *parent) : QObject(parent) {
}

void StackViewController::handleAuthToken() {
  qDebug() << "handle auth token";
  settings = new QSettings();
  QString token = settings->value("token").toString();

  if (token.length() == 0) {
    emit this->goToPageChanged("login");

    return;
  }

  emit this->goToPageChanged("chatList");
}

void StackViewController::goChatsListPage() {
  emit this->goToPageChanged("chatList");
}

void StackViewController::goChatPage() {
  emit this->goToPageChanged("chat");
}
