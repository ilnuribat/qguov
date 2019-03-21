#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QDebug>

class HttpClient: public QObject
{
  Q_OBJECT
  public:
    HttpClient();

    void login(QString login, QString passwod);
    void request(QString query, QJsonObject variables);
    void request(QString query);

  signals:
    void responseReady(QJsonObject &object);
  public slots:
    void handleResponse(QNetworkReply *reply);

  private:
    QString URL = "http://dev.scis.xyz/api";
    QSettings *settings;
};

#endif // HTTPREQUEST_H
