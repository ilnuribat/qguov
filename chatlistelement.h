#ifndef CHATLISTELEMENT_H
#define CHATLISTELEMENT_H

#include <QString>
#include <QDateTime>
#include <QDebug>

class ChatListElement
{
public:
  ChatListElement();
  ChatListElement(QString initials, QString icon, QString message, QDateTime date);

  QString initials() const;
  QString icon() const;
  QString message() const;
  QString date() const;

  void setInitials(QString initials);
  void setIcon(QString icon);
  void setMessage(QString message);
  void setDate(QDateTime date);

private:
  QString m_initials;
  QString m_icon;
  QString m_message;
  QDateTime m_date;

};

#endif // CHATLISTELEMENT_H
