#include "messagegql.h"

MessageGQL::MessageGQL(QJsonObject data, QString userId) {
  m_id = data.value("id").toString();
  m_message = data.value("text").toString();
  m_initials = data.value("from").toObject().value("initials").toString();
  m_isMe = userId == data.value("from").toObject().value("id").toString();
  m_createdAt = QDateTime::fromString(data.value("createdAt").toString(), Qt::ISODate); //2019-03-29T11:15:07+00:00
}

QString MessageGQL::getId() const {
  return m_id;
}

QString MessageGQL::getMessage() const {
  return m_message;
}

QString MessageGQL::getInitials() const {
  return m_initials;
}

bool MessageGQL::getIsMe() const {
  return m_isMe;
}

QString MessageGQL::getCreatedAt() const {
  if (!m_createdAt.isValid()) {
    return "";
  }

  QDate now = QDateTime::currentDateTime().date();

  if (now.year() != m_createdAt.date().year()) {
    return m_createdAt.toString("yyyy-MMMM-dd");
  }
  if (now.month() != m_createdAt.date().month()) {
    return m_createdAt.toString("dd MMMM");
  }
  if (now.weekNumber() != m_createdAt.date().weekNumber()) {
    return m_createdAt.toString("dd MMMM");
  }
  if (now.day() != m_createdAt.date().day()) {
    return m_createdAt.toString("ddd");
  }
  return m_createdAt.toString("hh:mm");
}
