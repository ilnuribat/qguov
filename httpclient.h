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
    QString getHost() const;
    QString getToken() const;

  signals:
    void responseReady(QJsonObject &object);
  public slots:
    void handleResponse(QNetworkReply *reply);

  private:
    QString HOST = "localhost:8500"; // "dev.scis.xyz";
    QString URL = "http://" + HOST + "/api";
    QSettings *settings;
};

#endif // HTTPREQUEST_H
