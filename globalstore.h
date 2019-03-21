#ifndef GLOBALSTORE_H
#define GLOBALSTORE_H

#include <QObject>
#include "chatsmodel.h"

class GlobalStore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChatsModel *chatsModel READ chatsModel NOTIFY chatsModelChanged)
  public:
    explicit GlobalStore(QObject *parent = nullptr);

    ChatsModel *chatsModel() const;

  signals:
    void chatsModelChanged();

  public slots:
  private:
    ChatsModel *m_chatsModel;
};

#endif // GLOBALSTORE_H
