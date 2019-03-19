#include "logincontroller.h"

LoginController::LoginController(QObject *parent) : QObject(parent) {
  settings = new QSettings();
}

QString LoginController::login() {
  return this->m_login;
}

void LoginController::setLogin(const QString login) {
  if (this->m_login == login) {
      return;
  }
  this->m_login = login;

  emit this->loginChanged(this->m_login);
}

QString LoginController::password() {
  return this->m_password;
}

void LoginController::setPassword(const QString password) {
  if (this->m_password == password) {
    return;
  }

  this->m_password = password;

  emit this->passwordChanged(this->m_password);
}

void LoginController::submitLogin() {
  HttpRequest *httpRequest = new HttpRequest();

  httpRequest->login(this->m_login, this->m_password);
}
