#include "chatlistcontroller.h"

ChatListController::ChatListController(QObject *parent) : QObject(parent)
{
  HttpClient *httpClient = new HttpClient();

  QString query =
    R"(
      {
        user {
          directs {
            id
            user {
              initials
              icon
            }
            lastMessage {
              text
              createdAt
            }
          }
        }
      }
    )";

  httpClient->request(query);

  connect(httpClient, &HttpClient::responseReady, [=] (QJsonObject data) {
    QJsonArray directs = data.value("data").toObject().value("user").toObject().value("directs").toArray();

    for (int i = 0; i < directs.size(); ++i) {
      QJsonObject direct = directs.at(i).toObject();
      m_globalStore->chatsModel()->appendChat(new DirectGQL(direct));
    }
    emit m_globalStore->chatsModelChanged();
  });
}

void ChatListController::goToChat() {
  m_stackView->goChatPage();
}

void ChatListController::setGlobalStore(QObject *globalStore) {
  m_globalStore = qobject_cast<GlobalStore*>(globalStore);
}

void ChatListController::setStackView(QObject *stackView) {
  m_stackView = qobject_cast<StackViewController*>(stackView);
}
