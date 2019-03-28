#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
  m_chatsModel = new ChatsModel(this);
  m_websocket = new WebSocket();
  connect(m_websocket, &WebSocket::messageAdded, this, &GlobalStore::messageAdded);
}

void GlobalStore::messageAdded(QJsonObject data) {
  QString chatId = data.value("to").toObject().value("id").toString();

  if (!messagesStore.contains(chatId)) {
    messagesStore[chatId] = new MessagesModel();
  }
  messagesStore[chatId]->append(new MessageElement(data));
  emit messagesModelChanged();

  m_chatsModel->updateLastMessage(data);
}

ChatsModel *GlobalStore::chatsModel() const {
  return m_chatsModel;
}

ChatListElement *GlobalStore::currentChat() const {
  return m_chatsModel->getChatElementById(m_currentChatId);
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
  emit currentChatChanged();
}

void GlobalStore::startSubscriptions() {
  qDebug() << "Starting subs!";
  m_websocket->startSubscriptions();
}
