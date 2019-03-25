#include "chatcontroller.h"

ChatController::ChatController(QObject *parent) : QObject(parent)
{

}

void ChatController::setGlobalStore(QObject *globalStore) {
  m_globalStore = qobject_cast<GlobalStore*>(globalStore);
  this->getMessages();
}

void ChatController::getMessages() {
  qDebug() << "get messages";
  HttpClient *httpClient = new HttpClient();
  QString id = m_globalStore->currentChatId();

  m_globalStore->messagesModel()->clear();

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
