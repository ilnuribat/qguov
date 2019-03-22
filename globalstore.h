#ifndef GLOBALSTORE_H
#define GLOBALSTORE_H

#include <QObject>
#include <QDebug>
#include "chatsmodel.h"

class GlobalStore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChatsModel *chatsModel READ chatsModel NOTIFY chatsModelChanged)
    Q_PROPERTY(QString currentChatId READ currentChatId WRITE setCurrentChatId NOTIFY currentChatIdChanged)
  public:
    explicit GlobalStore(QObject *parent = nullptr);

    ChatsModel *chatsModel() const;
    QString currentChatId() const;
    void setCurrentChatId(QString currentChatId);

  signals:
    void chatsModelChanged();
    void currentChatIdChanged();

  public slots:
  private:
    ChatsModel *m_chatsModel;
    QString m_currentChatId;
};

#endif // GLOBALSTORE_H
