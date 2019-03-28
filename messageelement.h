#ifndef MESSAGEELEMENT_H
#define MESSAGEELEMENT_H

#include <QString>
#include <QJsonObject>
#include <QDebug>

class MessageElement
{
  public:
    MessageElement(QString id, QString message, QString initials);
    MessageElement(QJsonObject data);

    QString getId() const;
    QString getMessage() const;
    QString getInitials() const;

  private:
    QString m_id;
    QString m_message;
    QString m_initials;
};

#endif // MESSAGEELEMENT_H
