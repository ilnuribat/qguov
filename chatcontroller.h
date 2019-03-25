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
    Q_PROPERTY(QObject *globalStore WRITE setGlobalStore)
  public:
    explicit ChatController(QObject *parent = nullptr);

    void setGlobalStore(QObject *globalStore);

  signals:

  public slots:
  private:
    GlobalStore *m_globalStore;
    void getMessages();
};

#endif // CHATCONTROLLER_H
