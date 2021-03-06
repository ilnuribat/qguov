#include "messagesmodel.h"

MessagesModel::MessagesModel()
{
  m_isEmpty = true;
}

bool MessagesModel::isEmpty() const {
  return m_isEmpty;
}

void MessagesModel::startFillingMessages() {
  m_isEmpty = false;
  clear();
}

int MessagesModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_messages.size();
}

void MessagesModel::append(MessageGQL *message) {
  beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
  m_messages.push_back(message);
  endInsertRows();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }

  switch (role) {
    case idRole: return m_messages.at(index.row())->getId();
    case messageRole: return m_messages.at(index.row())->getMessage();
    case initialsRole: return m_messages.at(index.row())->getInitials();
    case isMeRole: return m_messages.at(index.row())->getIsMe();
    case createdAtRole: return m_messages.at(index.row())->getCreatedAt();
    default: return QVariant();
  };
}

QHash<int, QByteArray> MessagesModel::roleNames() const {
  QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[idRole] = "id";
  roles[messageRole] = "message";
  roles[initialsRole] = "initials";
  roles[isMeRole] = "isMe";
  roles[createdAtRole] = "createdAt";

  return roles;
}

void MessagesModel::clear() {
  m_messages.clear();
  removeRows(0, m_messages.size(), QModelIndex());
}
