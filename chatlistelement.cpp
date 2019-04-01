#include "chatlistelement.h"

ChatListElement::ChatListElement(QObject *parent): QObject(parent) {}

ChatListElement::ChatListElement(QJsonObject data) {
   m_id = data.value("id").toString();
   m_initials = data.value("user").toObject().value("initials").toString();
   m_icon = data.value("user").toObject().value("icon").toString();

   if (data.contains("lastMessage") && !data.value("lastMessage").toObject().isEmpty()) {
     m_lastMessage = new MessageGQL(data.value("lastMessage").toObject(), "");
   }
   m_message = data.value("lastMessage").toObject().value("text").toString();
   QString createdAt = data.value("lastMessage").toObject().value("createdAt").toString();
   QDateTime date = QDateTime::fromString(createdAt.left(19), "yyyy-MM-ddTHH:mm:ss");

   if (m_icon.startsWith("https")) {
     m_icon = "http" + m_icon.right(m_icon.length() - 5);
   } else {
     m_icon = "http://dev.scis.xyz/api/" + m_icon;
   }
}

MessageGQL *ChatListElement::lastMessage() const {
  if (m_lastMessage) {
    return m_lastMessage;
  }

  return new MessageGQL(QJsonObject{}, "");
}

QString ChatListElement::chatName() const {
  return m_initials;
}

QString ChatListElement::initials() const {
  return m_initials;
}

QString ChatListElement::icon() const {
  return m_icon;
}

QString ChatListElement::message() const {
  return m_message;
}

QString ChatListElement::date() const {
  return m_date.toString("yyyy-MM-ddTHH:MM:ss");
}

QString ChatListElement::id() const {
  return m_id;
}

void ChatListElement::setInitials(QString initials) {
  m_initials = initials;
}

void ChatListElement::setIcon(QString icon) {
  m_icon = icon;
}

void ChatListElement::setMessage(QString message) {
  m_message = message;
}

void ChatListElement::setDate(QDateTime date) {
  if (!date.isValid()) {
    qDebug() << "invalid date";
  }
  m_date = date;
}

void ChatListElement::setId(QString id) {
  m_id = id;
}
