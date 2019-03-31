#ifndef MESSAGEELEMENT_H
#define MESSAGEELEMENT_H

#include <QString>
#include <QJsonObject>
#include <QDebug>

class MessageElement
{
  public:
    MessageElement(QString id, QString message, QString initials, bool isMe);
    MessageElement(QJsonObject data, QString userId);

    QString getId() const;
    QString getMessage() const;
    QString getInitials() const;
    bool getIsMe() const;

  private:
    QString m_id;
    QString m_message;
    QString m_initials;
    bool m_isMe;
};

#endif // MESSAGEELEMENT_H
