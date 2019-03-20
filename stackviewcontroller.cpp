#include "stackviewcontroller.h"

StackViewController::StackViewController(QObject *parent) : QObject(parent) {
  qDebug() << "stack View initialized!";
}

void StackViewController::handleAuthToken() {
  settings = new QSettings();
  QString token = settings->value("token").toString();

  if (token.length() != 0) {
    qDebug() << "no token found";

    // show login page
    emit this->goToPageChanged("login");
    emit this->onCurrentPageChanged();

    return;
  }

  qDebug() << "token is ready" << token;

  emit this->goToPageChanged("chatList");
  emit this->onCurrentPageChanged();
  // show chat page
}

QString StackViewController::currentPage() const {
  return m_lastGoToPage;
}
