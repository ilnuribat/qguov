#ifndef GLOBALSTORE_H
#define GLOBALSTORE_H

#include <QObject>
#include <QDebug>
#include <QtWebSockets/QWebSocket>
#include <QNetworkRequest>
#include "chatsmodel.h"
#include "messagesmodel.h"
#include "cpp/websocket/websocket.h"

class GlobalStore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChatsModel *chatsModel READ chatsModel NOTIFY chatsModelChanged)
    Q_PROPERTY(QString currentChatId READ currentChatId WRITE setCurrentChatId NOTIFY currentChatIdChanged)
    Q_PROPERTY(MessagesModel *messagesModel READ messagesModel NOTIFY messagesModelChanged)
  public:
    explicit GlobalStore(QObject *parent = nullptr);

    Q_INVOKABLE void startSubscriptions();
    ChatsModel *chatsModel() const;
    QString currentChatId() const;
    void setCurrentChatId(QString currentChatId);
    MessagesModel *messagesModel() const;

  signals:
    void chatsModelChanged();
    void currentChatIdChanged();
    void messagesModelChanged();

  public slots:
  private:
    // models
    ChatsModel *m_chatsModel;
    QHash<QString, MessagesModel*> messagesStore;

    QString m_currentChatId;
    QWebSocket *m_websockets;
    HttpClient httpClient;
    QNetworkRequest request;
    WebSocket *m_websocket;
};

#endif // GLOBALSTORE_H
