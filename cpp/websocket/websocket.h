#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QNetworkRequest>
#include <QDebug>
#include <QWebSocket>
#include <QWebSocketProtocol>
#include <QObject>
#include "httpclient.h"

class WebSocket: public QObject
{
  Q_OBJECT
  public:
    WebSocket();
    void startSubscriptions();
    void messageAddedSubs();

  signals:
    void messageAdded(QJsonObject data);

  private:
    void authenticate();
    QString m_token;
    QNetworkRequest m_request;
    HttpClient httpClient;
    QWebSocket *m_websocket;
};

#endif // WEBSOCKET_H
