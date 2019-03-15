#include "httprequest.h"

HttpRequest::HttpRequest()
{
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
    mutation {
      login(user: {
        email: "ibatullin.it"
        password: "123"
      }) {
        id
        token
      }
    })";

  QJsonDocument *jsonDoc = new QJsonDocument();

  QJsonObject jsonObject
  {
    {"query", gql}
  };

  jsonDoc->setObject(jsonObject);

  QString requestBody(jsonDoc->toJson(QJsonDocument::Compact));

  qDebug() << requestBody;
  pManager->post(request, requestBody.toUtf8());
}

void HttpRequest::login(QString login, QString password) {
  Q_UNUSED(login);
  Q_UNUSED(password);
}
