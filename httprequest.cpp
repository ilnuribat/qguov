#include "httprequest.h"

HttpRequest::HttpRequest()
{
  this->login("ibatullin.it", "123");
  settings = new QSettings();
}

void HttpRequest::login(QString login, QString password) {
  Q_UNUSED(login);
  Q_UNUSED(password);
  pManager = new QNetworkAccessManager(this);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  connect(pManager, &QNetworkAccessManager::finished, [=] (QNetworkReply *reply) {
    qDebug () << "request is ready";
    if (reply->error()) {
      qDebug() << "error!";
    }

    QString response = QString(reply->readAll());

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
    qDebug() << jsonDoc.toJson(QJsonDocument::Compact);
    QJsonObject jsObject = jsonDoc.object();

    if (jsObject.contains("errors")) {
      qDebug() << "error!" << jsObject.value("errors").toString();
    }

    QString token = jsObject.value("data").toObject().value("login").toObject().value("token").toString();

    settings->setValue("token", token);

  });

  request.setUrl(QUrl(URL));

  QString gql = R"(
    mutation($login: String!, $password: String!) {
      login(user: {
        email: $login
        password: $password
      }) {
        id
        token
      }
    })";

  QJsonDocument *jsonDoc = new QJsonDocument();

  QJsonObject vars {
    { "login", login },
    { "password", password },
  };

  QJsonObject jsonObject
  {
    { "query", gql },
    { "variables", vars },
  };

  jsonDoc->setObject(jsonObject);

  QString requestBody(jsonDoc->toJson(QJsonDocument::Compact));

  pManager->post(request, requestBody.toUtf8());
}
