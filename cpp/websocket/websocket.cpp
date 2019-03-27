#include "websocket.h"

WebSocket::WebSocket()
{
  m_settings = new QSettings();
  m_token = m_settings->value("token").toString();
  m_request.setRawHeader("", "");
  m_websocket = new QWebSocket(httpClient.getHost(), QWebSocketProtocol::Version13);
}

void WebSocket::startSubscriptions() {
  qDebug() << "ready to subs, host is" << httpClient.getHost();
  QObject::connect(m_websocket, &QWebSocket::connected, [=] () {
    qDebug() << "connected";

    QString token = httpClient.getToken();
    QString subsQuery = "{\"type\":\"connection_init\",\"payload\":{\"Authorization\":\"Bearer " + token + "\" } }";
    qDebug() << subsQuery;
    m_websocket->sendTextMessage(subsQuery);
  });

  QObject::connect(m_websocket, &QWebSocket::disconnected, [this] () {
    qDebug() << "disconnected";
    qDebug() << "errorString: " << m_websocket->errorString();
    qDebug() << "lastError: " <<  m_websocket->error();
    if (m_websocket->error() == QAbstractSocket::RemoteHostClosedError) {
      qDebug() << "we should reconnect";
      m_websocket->open(m_request);
    }
  });
  QObject::connect(m_websocket, &QWebSocket::textMessageReceived, [this] (QString message) {
    qDebug() << "new message!" << message;
    QJsonObject jsonObj = QJsonDocument::fromJson(message.toUtf8()).object();

    if (jsonObj.value("type").toString() == "connection_ack") {
      qDebug() << "we are ready to subscribe!";
      QJsonObject payload
      {
        { "query", "subscription { messageAdded { id text } }" },
      };

      QJsonObject subsObj
      {
        {"id", "1"},
        {"type", "start"},
        {"payload", payload }
      };
      QString messageAddedSubs = R"({"id":"1","type":"start","payload":{"variables":{},"extensions":{},"operationName":null,"query":"subscription {\n  messageAdded {\n    id\n    text\n    isDirect\n    createdAt\n    userId\n    isRead\n    from {\n      id\n      username\n      __typename\n    }\n    to {\n      __typename\n      ... on Task {\n        id\n        parentId\n        objectId\n        name\n        __typename\n      }\n      ... on Direct {\n        id\n        __typename\n      }\n    }\n    __typename\n  }\n}\n"}})";
      qDebug() << QJsonDocument(subsObj).toJson();
      m_websocket->sendTextMessage(QJsonDocument(subsObj).toJson());
    }
    if (jsonObj.value("type").toString() == "connection_error") {
      qDebug() << "error in websocket messages" << jsonObj.value("payload").toObject();
      m_websocket->close(QWebSocketProtocol::CloseCodeBadOperation, "wrong subscription query");
    }
  });
  QObject::connect(m_websocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), [=](QAbstractSocket::SocketError error) {
    qDebug() << "error signal" << error;
  });

  QString url = "ws://" + httpClient.getHost() + "/api/graphql";
  qDebug() << "url of ->open() is " << url;


  m_request.setUrl(QUrl(url));
  m_request.setRawHeader("Sec-WebSocket-Protocol", "graphql-ws");

  m_websocket->open(m_request);

}
