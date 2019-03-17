#include "httprequest.h"

HttpRequest::HttpRequest()
{
  this->login("ibatullin.it", "123");
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

    qDebug() << response;
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

  qDebug() << requestBody;
  pManager->post(request, requestBody.toUtf8());
}
