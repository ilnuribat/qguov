#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  m_chatsModel = new ChatsModel(this);
  m_messagesModel = new MessagesModel();
  m_websockets = new QWebSocket(httpClient.getHost(), QWebSocketProtocol::Version13, parent);
}

ChatsModel *GlobalStore::chatsModel() const {
  return m_chatsModel;
}

MessagesModel *GlobalStore::messagesModel() const {
  return messagesStore[m_currentChatId];
}

QString GlobalStore::currentChatId() const {
  return m_currentChatId;
}

void GlobalStore::setCurrentChatId(QString currentChatId) {
  m_currentChatId = currentChatId;
  if (!messagesStore.contains(m_currentChatId)) {
    messagesStore[currentChatId] = new MessagesModel();
  }
  emit currentChatIdChanged();
}

void GlobalStore::startSubscriptions() {
  qDebug() << "ready to subs, host is" << httpClient.getHost();
  connect(m_websockets, &QWebSocket::connected, [=] () {
    qDebug() << "connected";

    QString token = httpClient.getToken();
    QString subsQuery = "{\"type\":\"connection_init\",\"payload\":{\"Authorization\":\"Bearer " + token + "\" } }";
    qDebug() << subsQuery;
    m_websockets->sendTextMessage(subsQuery);
  });

  connect(m_websockets, &QWebSocket::disconnected, [this] () {
    qDebug() << "disconnected";
    qDebug() << "errorString: " << m_websockets->errorString();
    qDebug() << "lastError: " <<  m_websockets->error();
    if (m_websockets->error() == QAbstractSocket::RemoteHostClosedError) {
      qDebug() << "we should reconnect";
      m_websockets->open(request);
    }
  });
  connect(m_websockets, &QWebSocket::textMessageReceived, [this] (QString message) {
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
      m_websockets->sendTextMessage(QJsonDocument(subsObj).toJson());
    }
    if (jsonObj.value("type").toString() == "connection_error") {
      qDebug() << "error in websocket messages" << jsonObj.value("payload").toObject();
      m_websockets->close(QWebSocketProtocol::CloseCodeBadOperation, "wrong subscription query");
    }
  });
  connect(m_websockets, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), [=](QAbstractSocket::SocketError error) {
    qDebug() << "error signal" << error;
  });

  QString url = "ws://" + httpClient.getHost() + "/api/graphql";
  qDebug() << "url of ->open() is " << url;


  request.setUrl(QUrl(url));
  request.setRawHeader("Sec-WebSocket-Protocol", "graphql-ws");

  m_websockets->open(request);
}
