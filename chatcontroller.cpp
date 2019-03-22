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
                text
              }
            }
          }
        }
      }
      )";
  QJsonObject variables {
    { "id", id }
  };

  connect(httpClient, &HttpClient::responseReady, [] (QJsonObject data) {
    qDebug() << data;
  });

  httpClient->request(query, variables);
}
