#ifndef MESSAGESMODEL_H
#define MESSAGESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QModelIndex>
#include "messageelement.h"

class MessagesModel : public QAbstractListModel
{
    Q_OBJECT
  public:
    enum Roles {
      idRole = Qt::UserRole + 1,
      textRole,
      initialsRole,
    };

    MessagesModel();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

  private:
    QList<MessageElement*> m_messages;
};

#endif // MESSAGESMODEL_H
