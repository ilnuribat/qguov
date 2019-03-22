#include "chatlistelement.h"

ChatListElement::ChatListElement() {}

ChatListElement::ChatListElement(QString id, QString initials, QString icon, QString message, QDateTime date) {
  m_initials = initials;
  m_icon = icon;
  m_message = message;
  m_id = id;

  if (!date.isValid()) {
    throw "invalid date";
  }
  m_date = date;
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
    throw "date is invalid";
  }
  m_date = date;
}

void ChatListElement::setId(QString id) {
  m_id = id;
}
