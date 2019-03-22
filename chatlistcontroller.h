#ifndef CHATLISTCONTROLLER_H
#define CHATLISTCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "httpclient.h"
#include "globalstore.h"
#include "stackviewcontroller.h"

class ChatListController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *globalStore WRITE setGlobalStore)
    Q_PROPERTY(QObject *stackView WRITE setStackView)

  public:
    explicit ChatListController(QObject *parent = nullptr);

    void setGlobalStore(QObject *globalStore);
    void setStackView(QObject *stackView);

    Q_INVOKABLE void goToChat();

  signals:

  public slots:
  private:
    GlobalStore *m_globalStore;
    StackViewController *m_stackView;
};

#endif // CHATLISTCONTROLLER_H
