#include "globalstore.h"

GlobalStore::GlobalStore(QObject *parent) : QObject(parent)
{
}

void GlobalStore::initGlobalStore() {
  m_chatsModel = new ChatsModel(this);
  m_websocket = new WebSocket();
  connect(m_websocket, &WebSocket::messageAdded, this, &GlobalStore::messageAdded);
  QSettings *m_settings = new QSettings();

  if (m_settings->contains("userId")) {
    m_userId = m_settings->value("userId").toString();
    emit globalStoreIsReady();

    return;
  }

  // no userId
  HttpClient *httpClient = new HttpClient();
  connect(httpClient, &HttpClient::responseReady, [=](QJsonObject data) {
    m_userId = data.value("data").toObject().value("user").toObject().value("id").toString();
    m_settings->setValue("userId", m_userId);
    emit globalStoreIsReady();
  });
  httpClient->request("{ user { id } }");
}

void GlobalStore::messageAdded(QJsonObject data) {
  QString chatId = data.value("to").toObject().value("id").toString();

  if (!messagesStore.contains(chatId)) {
    messagesStore[chatId] = new MessagesModel();
  }
  messagesStore[chatId]->append(new MessageGQL(data, m_userId));
  emit messagesModelChanged();

  m_chatsModel->updateLastMessage(data, m_userId);
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

QString GlobalStore::getUserId() const {
  return m_userId;
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
