#include "websocket.h"

WebSocket::WebSocket()
{
  m_token = httpClient.getToken();
  QString url = "ws://" + httpClient.getHost() + "/api/graphql";
  qDebug() << "url of ->open() is " << url;

  m_request.setUrl(QUrl(url));
  m_request.setRawHeader("Sec-WebSocket-Protocol", "graphql-ws");
  m_websocket = new QWebSocket(httpClient.getHost(), QWebSocketProtocol::Version13);
}

void WebSocket::messageAddedSubs() {
  QString messageAddedSubs = R"(
                          subscription {
                            messageAdded {
                              id
                              text
                              isDirect
                              createdAt
                              userId
                              isRead
                              from {
                                id
                                username
                              }
                              to {
                                __typename
                                ... on Task {
                                  id
                                  parentId
                                  objectId
                                  name
                                }
                                ... on Direct {
                                  id
                                }
                              }
                            }
                          })";
  QJsonObject payload
   {
     { "query", messageAddedSubs },
   };

   QJsonObject subsObj
   {
     {"id", "1"},
     {"type", "start"},
     {"payload", payload }
   };
   m_websocket->sendTextMessage(QJsonDocument(subsObj).toJson());
}

void WebSocket::startSubscriptions() {
  qDebug() << "ready to subs, host is" << httpClient.getHost();
  QObject::connect(m_websocket, &QWebSocket::connected, [=] () {
    qDebug() << "connected";

    QString token = httpClient.getToken();
    QString subsQuery = "{\"type\":\"connection_init\",\"payload\":{\"Authorization\":\"Bearer " + token + "\" } }";
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
  QObject::connect(m_websocket, &QWebSocket::textMessageReceived, [=] (QString message) {
    QJsonObject jsonObj = QJsonDocument::fromJson(message.toUtf8()).object();
    QString messageType = jsonObj.value("type").toString();

    qDebug() << "type: " << messageType;

    if (messageType == "connection_ack") {
      qDebug() << "we are ready to subscribe!";
      messageAddedSubs();
    }
    if (messageType == "connection_error") {
      qDebug() << "error in websocket messages" << jsonObj.value("payload").toObject();
      m_websocket->close(QWebSocketProtocol::CloseCodeBadOperation, "wrong subscription query");
    }
    if(messageType == "data") {
      if (jsonObj.value("id").toString() == "1") {
        emit messageAdded(jsonObj.value("payload").toObject().value("data").toObject().value("messageAdded").toObject());
      } else {
        qDebug() << "recieved mesage of unknown id" << jsonObj;
      }
    }
  });
  QObject::connect(m_websocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), [=](QAbstractSocket::SocketError error) {
    qDebug() << "error signal" << error;
  });




  m_websocket->open(m_request);

}
