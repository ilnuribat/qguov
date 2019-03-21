#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  m_chatsModel = new ChatsModel(this);
}

ChatsModel *GlobalStore::chatsModel() const {
  return m_chatsModel;
}
