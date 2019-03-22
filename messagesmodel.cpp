#include "messagesmodel.h"

MessagesModel::MessagesModel()
{
}

int MessagesModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_messages.size();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }

  switch (role) {
    case idRole: return m_messages.at(index.row())->getId();
    case textRole: return m_messages.at(index.row())->getText();
    case initialsRole: return m_messages.at(index.row())->getInitials();
    default: return QVariant();
  };
}

QHash<int, QByteArray> MessagesModel::roleNames() const {
  QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[idRole] = "id";
  roles[textRole] = "text";
  roles[initialsRole] = "initials";

  return roles;
}
