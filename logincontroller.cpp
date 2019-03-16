#include "logincontroller.h"

LoginController::LoginController(QObject *parent) : QObject(parent)
{

}

QString LoginController::login() {
  return this->m_login;
}

void LoginController::setLogin(const QString login) {
  if (this->m_login == login) {
      return;
  }
  this->m_login = login;

  qDebug() << "login changed: " << login;
  emit this->loginChanged(this->m_login);
}

QString LoginController::password() {
  return this->m_password;
}

void LoginController::setPassword(const QString password) {
  if (this->m_password == password) {
    return;
  }

  qDebug() << "password changed " << this->m_password;
  this->m_password = password;

  emit this->passwordChanged(this->m_password);
}
