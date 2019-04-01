#ifndef MESSAGESMODEL_H
#define MESSAGESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QModelIndex>
#include <QDebug>
#include "messagegql.h"

class MessagesModel : public QAbstractListModel
{
    Q_OBJECT
  public:
    enum Roles {
      idRole = Qt::UserRole + 1,
      messageRole,
      isMeRole,
      initialsRole,
      createdAtRole,
    };

    MessagesModel();

    void append(MessageGQL *message);
    void clear();
    bool isEmpty() const;
    void startFillingMessages(); // флажок isEmpty переключаем на false, даже если сообщений нет

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

  private:
    QList<MessageGQL*> m_messages;
    bool m_isEmpty;
};

#endif // MESSAGESMODEL_H
