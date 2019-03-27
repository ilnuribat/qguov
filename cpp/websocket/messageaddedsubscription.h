#ifndef MESSAGEADDEDSUBSCRIPTION_H
#define MESSAGEADDEDSUBSCRIPTION_H

#include <QObject>
#include <QDebug>
#include "globalstore.h"

class MessageAddedSubscription
{
  public:
    MessageAddedSubscription(GlobalStore *globalStore);

    QString getQuery() const;
  private:
    GlobalStore *m_globalStore;
    QString query;
};

#endif // MESSAGEADDEDSUBSCRIPTION_H
