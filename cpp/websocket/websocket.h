#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QSettings>
#include <QNetworkRequest>
#include <QDebug>
#include <QWebSocket>
#include <QWebSocketProtocol>
#include <QObject>
#include "httpclient.h"

class WebSocket
{
  public:
    WebSocket();
    void startSubscriptions();
  private:
    QSettings *m_settings;
    QString m_token;
    QNetworkRequest m_request;
    HttpClient httpClient;
    QWebSocket *m_websocket;
};

#endif // WEBSOCKET_H
