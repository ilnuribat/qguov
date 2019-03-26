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
    QString subsQuery = R"({"type":"connection_init","payload":{"Authorization":"Bearer ")" + token + "\" } }";
    // qDebug() << subsQuery;
    // m_websockets->sendTextMessage(subsQuery);
  });

  connect(m_websockets, &QWebSocket::disconnected, [this] () {
    qDebug() << "disconnected";
    qDebug() << "errorString: " << m_websockets->errorString();
    qDebug() << "lastError: " <<  m_websockets->error();
  });
  connect(m_websockets, &QWebSocket::pong, [] () {
    qDebug() << "pong";
  });
  connect(m_websockets, &QWebSocket::textMessageReceived, [] () {
    qDebug() << "new message!";
  });
  connect(m_websockets, &QWebSocket::textFrameReceived, [] (QString frame) {
    qDebug() << "text frame: " << frame;
  });
  connect(m_websockets, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), [=](QAbstractSocket::SocketError error) {
    qDebug() << "error signal" << error;
  });

  QString url = "ws://" + httpClient.getHost() + "/graphql";
  qDebug() << "url of ->open() is " << url;

  m_websockets->open(QUrl(url));
}
