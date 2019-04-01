#ifndef MESSAGEELEMENT_H
#define MESSAGEELEMENT_H

#include <QString>
#include <QJsonObject>
#include <QDebug>
#include <QDateTime>

class MessageGQL
{
  public:
    MessageGQL(QJsonObject data, QString userId);

    QString getId() const;
    QString getMessage() const;
    QString getInitials() const;
    QString getCreatedAt() const;
    bool getIsMe() const;

  private:
    QString m_id;
    QString m_message;
    QString m_initials;
    QDateTime m_createdAt;
    bool m_isMe;
};

#endif // MESSAGEELEMENT_H
