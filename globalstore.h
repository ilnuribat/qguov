#ifndef GLOBALSTORE_H
#define GLOBALSTORE_H

#include <QObject>
#include <QDebug>
#include "chatsmodel.h"
#include "messagesmodel.h"

class GlobalStore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChatsModel *chatsModel READ chatsModel NOTIFY chatsModelChanged)
    Q_PROPERTY(QString currentChatId READ currentChatId WRITE setCurrentChatId NOTIFY currentChatIdChanged)
    Q_PROPERTY(MessagesModel *messagesModel READ messagesModel NOTIFY messagesModelChanged)
  public:
    explicit GlobalStore(QObject *parent = nullptr);

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
    ChatsModel *m_chatsModel;
    QString m_currentChatId;
    MessagesModel *m_messagesModel;
};

#endif // GLOBALSTORE_H
