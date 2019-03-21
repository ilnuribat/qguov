#include "chatsmodel.h"

ChatsModel::ChatsModel(QObject *parent): QAbstractListModel (parent)
{
}

void ChatsModel::appendChat(ChatListElement *chat) {
  beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
  m_list.append(chat);
  endInsertRows();
}

int ChatsModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)

  return m_list.size();
}

QVariant ChatsModel::data(const QModelIndex &index, int role) const {
  if(!index.isValid()) {
    return QVariant();
  }

  switch (role) {
    case initialsRole: return m_list.at(index.row())->initials();
    case iconRole: return m_list.at(index.row())->icon();
    case messageRole: return m_list.at(index.row())->message();
    case dateRole: return m_list.at(index.row())->date();

    default: return QVariant();
  }
}

QHash <int, QByteArray> ChatsModel::roleNames() const {
  QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[initialsRole] = "initials";
  roles[iconRole] = "icon";
  roles[messageRole] = "message";
  roles[dateRole] = "date";

  return roles;
}
