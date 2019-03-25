#include "messageelement.h"

MessageElement::MessageElement(QString id, QString message, QString initials) {
  m_id = id;
  m_message = message;
  m_initials = initials;
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

