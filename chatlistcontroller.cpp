#include "chatlistcontroller.h"

ChatListController::ChatListController(QObject *parent) : QObject(parent)
{
  // make http request
  qDebug() << "init of Chat list controller";
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
      QString initials = direct.value("user").toObject().value("initials").toString();
      QString icon = direct.value("user").toObject().value("icon").toString();
      QString text = direct.value("lastMessage").toObject().value("text").toString();
      QString createdAt = direct.value("lastMessage").toObject().value("createdAt").toString();
      QDateTime date = QDateTime::fromString(createdAt.left(19), "yyyy-MM-ddTHH:mm:ss");
      if (icon.startsWith("https")) {
        icon = "http" + icon.right(icon.length() - 5);
      }
      qDebug() << initials << icon << text << createdAt.left(19) << date;
      m_globalStore->chatsModel()->appendChat(new ChatListElement(initials, icon, text, date));
    }
    emit m_globalStore->chatsModelChanged();
  });
}

void ChatListController::setGlobalStore(QObject *globalStore) {
  m_globalStore = qobject_cast<GlobalStore*>(globalStore);
}
