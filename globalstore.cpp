#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  m_chatsModel = new ChatsModel(this);
  m_messagesModel = new MessagesModel();
  m_currentChatId = "5c94c7b8d48d843070adfa96";
  m_websockets = new QWebSocket(httpClient.getHost(), QWebSocketProtocol::Version13, parent);
}

ChatsModel *GlobalStore::chatsModel() const {
  return m_chatsModel;
}

MessagesModel *GlobalStore::messagesModel() const {
  return m_messagesModel;
}

QString GlobalStore::currentChatId() const {
  return m_currentChatId;
}

void GlobalStore::setCurrentChatId(QString currentChatId) {
  m_currentChatId = currentChatId;
  emit currentChatIdChanged();
  qDebug() << "currentChat changed";
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
  connect(m_websockets, &QWebSocket::textMessageReceived, [] (QString message) {
    qDebug() << "new message!" << message;
    QJsonObject jsonObj = QJsonDocument::fromJson(message.toUtf8()).object();

    if (jsonObj.value("type").toString() == "connection_ack") {
      qDebug() << "we are ready to subscribe!";
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
