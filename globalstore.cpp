#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  m_chatsModel = new ChatsModel(this);
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
}
