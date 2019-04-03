#include "directgql.h"

DirectGQL::DirectGQL(QObject *parent): QObject(parent) {}

DirectGQL::DirectGQL(QJsonObject data) {
   m_id = data.value("id").toString();
   m_initials = data.value("user").toObject().value("initials").toString();
   m_icon = data.value("user").toObject().value("icon").toString();

   if (data.contains("lastMessage") && !data.value("lastMessage").toObject().isEmpty()) {
     m_lastMessage = new MessageGQL(data.value("lastMessage").toObject(), "");
   }

   if (m_icon.startsWith("https")) {
     m_icon = "http" + m_icon.right(m_icon.length() - 5);
   } else {
     m_icon = "http://dev.scis.xyz/api/" + m_icon;
   }
}

MessageGQL *DirectGQL::lastMessage() const {
  if (m_lastMessage) {
    return m_lastMessage;
  }

  return new MessageGQL(QJsonObject{}, "");
}

QString DirectGQL::chatName() const {
  return m_initials;
}

QString DirectGQL::initials() const {
  return m_initials;
}

QString DirectGQL::icon() const {
  return m_icon;
}

QString DirectGQL::id() const {
  return m_id;
}

void DirectGQL::setInitials(QString initials) {
  m_initials = initials;
}

void DirectGQL::setIcon(QString icon) {
  m_icon = icon;
}

void DirectGQL::setId(QString id) {
  m_id = id;
}

void DirectGQL::setLastMessage(MessageGQL *lastMessage) {
  m_lastMessage = lastMessage;
}

