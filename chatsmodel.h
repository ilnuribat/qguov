#ifndef CHATSMODEL_H
#define CHATSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDateTime>
#include <QModelIndex>
#include "directgql.h"
#include "httpclient.h"

class ChatsModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum Roles {
    initialsRole = Qt::UserRole + 1,
    iconRole,
    messageRole,
    dateRole,
    idRole
  };
  ChatsModel(QObject *parent = nullptr);

  void appendChat(DirectGQL *chat);
  void updateLastMessage(QJsonObject data, QString userId);
  DirectGQL *getChatElementById(QString id) const;

  virtual int rowCount(const QModelIndex &parent) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QHash<int, QByteArray> roleNames() const;

  // Q_INVOKABLE void add();

private:
  QList<DirectGQL *> m_list;
};

#endif // CHATSMODEL_H
