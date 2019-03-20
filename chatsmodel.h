#ifndef CHATSMODEL_H
#define CHATSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDateTime>
#include "chatlistelement.h"
#include "httpclient.h"

class ChatsModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum Roles {
    initialsRole = Qt::UserRole + 1,
    iconRole,
    messageRole,
    dateRole
  };
  ChatsModel(QObject *parent = nullptr);

  virtual int rowCount(const QModelIndex &parent) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QHash<int, QByteArray> roleNames() const;

  // Q_INVOKABLE void add();

private:
  QList<ChatListElement *> m_list;
};

#endif // CHATSMODEL_H
