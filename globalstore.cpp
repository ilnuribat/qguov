#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  qDebug() << "global store constructor";
  m_chatsModel = new ChatsModel(this);
}

ChatsModel *GlobalStore::chatsModel() const {
  return m_chatsModel;
}

QString GlobalStore::currentChatId() const {
  return m_currentChatId;
}

void GlobalStore::setCurrentChatId(QString currentChatId) {
  m_currentChatId = currentChatId;
  emit currentChatIdChanged();
  qDebug() << "currentChat changed";
}
