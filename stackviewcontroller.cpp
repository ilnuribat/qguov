#include "stackviewcontroller.h"

StackViewController::StackViewController(QObject *parent) : QObject(parent) {
  qDebug() << "stack View initialized!";
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

  qDebug() << "token is ready" << token;
  emit this->goToPageChanged("chat");
  // show chat page
}
