#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  qDebug() << "global store constructor";
  m_chatsModel = new ChatsModel(this);
}

ChatsModel *GlobalStore::chatsModel() const {
  return m_chatsModel;
}
