#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

class HttpRequest: public QObject
{
  public:
    HttpRequest();

    void login(QString login, QString passwod);

  private:
    QString URL = "http://dev.scis.xyz/api";
    QNetworkAccessManager *pManager;
    QNetworkRequest request;
    QSettings *settings;
};

#endif // HTTPREQUEST_H
