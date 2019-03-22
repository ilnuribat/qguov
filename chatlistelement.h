#ifndef CHATLISTELEMENT_H
#define CHATLISTELEMENT_H

#include <QString>
#include <QDateTime>
#include <QDebug>

class ChatListElement
{
public:
  ChatListElement();
  ChatListElement(QString id, QString initials, QString icon, QString message, QDateTime date);

  QString id() const;
  QString initials() const;
  QString icon() const;
  QString message() const;
  QString date() const;

  void setInitials(QString initials);
  void setIcon(QString icon);
  void setMessage(QString message);
  void setDate(QDateTime date);
  void setId(QString id);

private:
  QString m_initials;
  QString m_icon;
  QString m_message;
  QDateTime m_date;
  QString m_id;

};

#endif // CHATLISTELEMENT_H
