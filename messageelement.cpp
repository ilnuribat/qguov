#include "messageelement.h"

MessageElement::MessageElement(QString id, QString message, QString initials, bool isMe)
  : m_id(id), m_message(message), m_initials(initials), m_isMe(isMe)
{
}

MessageElement::MessageElement(QJsonObject data, QString userId) {
  m_id = data.value("id").toString();
  m_message = data.value("text").toString();
  m_initials = data.value("from").toObject().value("initials").toString();
  m_isMe = userId == data.value("from").toObject().value("id").toString();
}

QString MessageElement::getId() const {
  return m_id;
}

QString MessageElement::getMessage() const {
  return m_message;
}

QString MessageElement::getInitials() const {
  return m_initials;
}

bool MessageElement::getIsMe() const {
  return m_isMe;
}
