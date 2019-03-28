#include "messageelement.h"

MessageElement::MessageElement(QString id, QString message, QString initials)
  : m_id(id), m_message(message), m_initials(initials)
{
}

MessageElement::MessageElement(QJsonObject data) {
  m_id = data.value("id").toString();
  m_message = data.value("text").toString();
  m_initials = data.value("from").toObject().value("initials").toString();
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

