#include "stackviewcontroller.h"

StackViewController::StackViewController(QObject *parent) : QObject(parent) {
  qDebug() << "stack View initialized!";
  settings = new QSettings();
  QString token = settings->value("token").toString();

  if (token.length() == 0) {
    qDebug() << "no token found";

    return;
  }

  qDebug() << token;
}
