#ifndef CHATLISTELEMENT_H
#define CHATLISTELEMENT_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QDebug>
#include "messagegql.h"

class DirectGQL: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString chatName READ chatName NOTIFY chatNameChanged)
    Q_PROPERTY(MessageGQL *lastMessage READ lastMessage NOTIFY lastMessageChanged)
public:
  explicit DirectGQL(QObject *parent = nullptr);

  DirectGQL(QJsonObject data);

  QString id() const;
  QString initials() const;
  QString icon() const;
  QString chatName() const;
  MessageGQL *lastMessage() const;

  void setInitials(QString initials);
  void setIcon(QString icon);
  void setId(QString id);
  void setLastMessage(MessageGQL *lastMessage);

signals:
  void chatNameChanged();
  void lastMessageChanged();

private:
  QString m_initials;
  QString m_icon;
  QString m_id;
  MessageGQL *m_lastMessage;
};

#endif // CHATLISTELEMENT_H
