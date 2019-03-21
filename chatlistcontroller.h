#ifndef CHATLISTCONTROLLER_H
#define CHATLISTCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "httpclient.h"
#include "globalstore.h"

class ChatListController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *globalStore WRITE setGlobalStore)

  public:
    explicit ChatListController(QObject *parent = nullptr);

    void setGlobalStore(QObject *globalStore);

  signals:

  public slots:
  private:
    GlobalStore *m_globalStore;
};

#endif // CHATLISTCONTROLLER_H
