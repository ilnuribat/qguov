#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  qDebug() << "global store constructor";
  m_chatsModel = new ChatsModel(this);
  m_messagesModel = new MessagesModel();
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
