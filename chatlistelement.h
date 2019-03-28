#ifndef CHATLISTELEMENT_H
#define CHATLISTELEMENT_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QDebug>

class ChatListElement: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString chatName READ chatName NOTIFY chatNameChanged)
public:
  explicit ChatListElement(QObject *parent = nullptr);
  ChatListElement(QString id, QString initials, QString icon, QString message, QDateTime date);
  ChatListElement(QJsonObject data);

  QString id() const;
  QString initials() const;
  QString icon() const;
  QString message() const;
  QString date() const;
  QString chatName() const;

  void setInitials(QString initials);
  void setIcon(QString icon);
  void setMessage(QString message);
  void setDate(QDateTime date);
  void setId(QString id);
signals:
  void chatNameChanged();

private:
  QString m_initials;
  QString m_icon;
  QString m_message;
  QDateTime m_date;
  QString m_id;

};

#endif // CHATLISTELEMENT_H
