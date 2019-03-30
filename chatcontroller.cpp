#include "chatcontroller.h"

ChatController::ChatController(QObject *parent) : QObject(parent)
{ 
}

void ChatController::sendMessage(QString message) {
  HttpClient *httpClient = new HttpClient();
  QString query =
      R"(
        mutation($id: ID!, $text: String!) {
          createMessage(message: {
            groupId: $id,
            text: $text
          }) {
            id
          }
        }
      )";
  QJsonObject variables
  {
    {"id", m_globalStore->currentChatId()},
    {"text", message},
  };

  connect(httpClient, &HttpClient::responseReady, [this] (QJsonObject data) {
    qDebug() << data;
    if (data.contains("errors")) {
      qDebug() << "error on sending message" << data;
      return;
    }

    emit messageSent();
  });

  httpClient->request(query, variables);
}

GlobalStore *ChatController::globalStore() const {
  return m_globalStore;
}

void ChatController::setGlobalStore(QObject *globalStore) {
  m_globalStore = qobject_cast<GlobalStore*>(globalStore);
  this->getMessages();
  connect(m_globalStore, &GlobalStore::messagesModelChanged, this, &ChatController::messagesModelUpdated);
}

void ChatController::messagesModelUpdated() {
  emit this->messagesModelChanged();
}

void ChatController::getMessages() {
  HttpClient *httpClient = new HttpClient();
  QString id = m_globalStore->currentChatId();

  if (!m_globalStore->messagesModel()->isEmpty()) {
    return;
  }

  QString query =
      R"(
      query($id: ID!) {
        direct(id: $id) {
          id
          name
          user {
            initials
          }
          messages {
            edges {
              node {
                id
                text
                createdAt
                from {
                  initials
                }
              }
            }
          }
        }
      }
      )";
  QJsonObject variables {
    { "id", id }
  };

  connect(httpClient, &HttpClient::responseReady, [this] (QJsonObject data) {
    m_globalStore->messagesModel()->startFillingMessages();

    QJsonArray messagesJson = data.value("data").toObject().value("direct").toObject().value("messages").toObject().value("edges").toArray();

    for (int i = 0; i< messagesJson.size(); i ++) {
      QJsonObject currentMessage = messagesJson.at(i).toObject().value("node").toObject();
      QString initials = currentMessage.value("from").toObject().value("initials").toString();
      QString id = currentMessage.value("id").toString();
      QString text = currentMessage.value("text").toString();

      m_globalStore->messagesModel()->append(new MessageElement(id, text, initials));
    }

    emit m_globalStore->messagesModelChanged();

    emit messagesLoaded();
  });

  httpClient->request(query, variables);
}
