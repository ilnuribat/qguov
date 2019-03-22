#include "messageelement.h"

MessageElement::MessageElement(QString id, QString text, QString initials) {
  m_id = id;
  m_text = text;
  m_initials = initials;
}

QString MessageElement::getId() const {
  return m_id;
}

QString MessageElement::getText() const {
  return m_text;
}

QString MessageElement::getInitials() const {
  return m_initials;
}

