#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  m_chatsModel = new ChatsModel(this);
  m_messagesModel = new MessagesModel();
  m_currentChatId = "5c94c7b8d48d843070adfa96";
  m_websockets = new QWebSocket("https://dev.scis.xyz", QWebSocketProtocol::Version13, parent);
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
  qDebug() << "ready to subs";
  connect(m_websockets, &QWebSocket::connected, [=] () {
    qDebug() << "connected";
    m_websockets->sendTextMessage(R"({"type":"connection_init","payload":{"Authorization":"Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZDFDIjoiMTljYWE2MmEtNmIwMi0xMWU4LTgwZTYtZTAwNzFiY2ZlMWYwIiwiaWF0IjoxNTUzNTcyNDUxfQ.g9fdD1xGkx23HmKeeaLmbzgasdPtNyWcRf9yEx8ouo4"}})");
  });
  connect(m_websockets, &QWebSocket::disconnected, [this] () {
    qDebug() << "disconnected";
    qDebug() << m_websockets->errorString();
    qDebug() << m_websockets->error();
  });
  connect(m_websockets, &QWebSocket::pong, [] () {
    qDebug() << "pong";
  });
  connect(m_websockets, &QWebSocket::textMessageReceived, [] () {
    qDebug() << "new message!";
  });
  // connect(m_websockets, &QWebSocket::error, [] (QAbstractSocket::) {
  //
  // });

  m_websockets->open(QUrl("ws://dev.scis.xyz/api/graphql"));
}
