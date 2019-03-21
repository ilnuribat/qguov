#include "httpclient.h"

HttpClient::HttpClient()
{
  this->login("ibatullin.it", "123");

  settings = new QSettings();
}

void HttpClient::handleResponse(QNetworkReply *reply) {
  if (reply->error()) {
    qDebug() << "error in request!" << QString(reply->readAll());

    return;
  }

  QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();

  emit this->responseReady(jsonObject);
}

void HttpClient::request(QString query) {
  QJsonObject emptyObj {};

  this->request(query, emptyObj);
}

void HttpClient::request(QString query, QJsonObject variables) {
  QNetworkAccessManager *pManager = new QNetworkAccessManager(this);

  connect(pManager, &QNetworkAccessManager::finished, this, &HttpClient::handleResponse);

  QNetworkRequest m_request;

  m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  m_request.setUrl(QUrl(URL));

  QString token = settings->value("token").toString();

  if (token.length() > 0) {
    m_request.setRawHeader("Authorization", QString("Bearer " + token).toUtf8());
  }

  QJsonObject gql
  {
    { "query", query },
    { "variables", variables },
  };

  QString requestBody(QJsonDocument(gql).toJson(QJsonDocument::Compact));

  pManager->post(m_request, requestBody.toUtf8());
}

void HttpClient::login(QString login, QString password) {
  QNetworkAccessManager *pManager = new QNetworkAccessManager(this);
  QNetworkRequest m_request;

  m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  connect(pManager, &QNetworkAccessManager::finished, [=] (QNetworkReply *reply) {
    if (reply->error()) {
      qDebug() << "error!";
    }

    QString response = QString(reply->readAll());

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject jsObject = jsonDoc.object();

    if (jsObject.contains("errors")) {
      qDebug() << "error!" << jsObject.value("errors").toString();
    }

    QString token = jsObject.value("data").toObject().value("login").toObject().value("token").toString();

    settings->setValue("token", token);
  });

  m_request.setUrl(QUrl(URL));

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

  pManager->post(m_request, requestBody.toUtf8());
}
