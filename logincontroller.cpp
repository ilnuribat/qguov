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

  emit this->loginChanged();
}

QString LoginController::password() {
  return this->m_password;
}

void LoginController::setPassword(const QString password) {
  if (this->m_password == password) {
    return;
  }

  this->m_password = password;

  emit this->passwordChanged();
}

QString LoginController::resultMessage() const {
  return m_resultMessage;
}

void LoginController::setStackView(QObject *stackView) {
  if (stackView) {
    qDebug() << "set stackview, not empty";
  }

  m_stackView = qobject_cast<StackViewController*>(stackView);
}

void LoginController::loginResponse(QJsonObject &object) {
  if (object.contains("errors")) {
    qDebug() << "error!" << object.value("errors").toArray().at(0).toObject();
    m_resultMessage = "Неверные логин или пароль";
    emit this->resultMessageChanged();
  }

  QString token = object.value("data").toObject().value("login").toObject().value("token").toString();

  qDebug() << "token ready" << token;

  settings->setValue("token", token);

  m_stackView->goChatsListPage();
}

void LoginController::submitLogin() {
  HttpClient *httpRequest = new HttpClient();

  connect(httpRequest, &HttpClient::responseReady, this, &LoginController::loginResponse);

  httpRequest->request(R"(
                        mutation($email: String!, $password: String!) {
                          login(user: {
                            email: $email
                            password: $password
                          }) {
                            id
                            token
                          }
                        })",
    QJsonObject {
      { "email", this->login() },
      { "password", this->password() },
  });
}
