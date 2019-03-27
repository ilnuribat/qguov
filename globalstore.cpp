#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  m_chatsModel = new ChatsModel(this);
  m_websocket = new WebSocket();
  connect(m_websocket, &WebSocket::messageAdded, this, &GlobalStore::messageAdded);

}

void GlobalStore::messageAdded(QJsonObject data) {
  qDebug() << "handle in globalStore " << data;
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
  qDebug() << "Starting subs!";
  m_websocket->startSubscriptions();
}
