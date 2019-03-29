#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include "globalstore.h"
#include "httpclient.h"

class ChatController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *globalStore READ globalStore WRITE setGlobalStore)
  public:
    explicit ChatController(QObject *parent = nullptr);

    void setGlobalStore(QObject *globalStore);
    GlobalStore *globalStore() const;
    Q_INVOKABLE void sendMessage(QString message);

  signals:
    void messagesLoaded();
    void messagesModelChanged();
    void messageSent();

  public slots:
    void messagesModelUpdated();
  private:
    GlobalStore *m_globalStore;
    void getMessages();
};

#endif // CHATCONTROLLER_H
