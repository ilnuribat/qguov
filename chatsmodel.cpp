#include "chatsmodel.h"

ChatsModel::ChatsModel(QObject *parent): QAbstractListModel (parent)
{
}

ChatListElement *ChatsModel::getChatElementById(QString id) const {
  for (int i = 0; i < m_list.size(); i ++) {
    if (m_list.at(i)->id() == id) {
      return m_list.at(i);
    }
  }
  qDebug() << "no such chat";
  return new ChatListElement();
}

void ChatsModel::appendChat(ChatListElement *chat) {
  beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
  m_list.append(chat);
  endInsertRows();
}

void ChatsModel::updateLastMessage(QJsonObject data, QString userId) {
  QString chatId = data.value("to").toObject().value("id").toString();

  for (int i = 0; i < m_list.size(); i ++) {
    ChatListElement *chat = m_list.at(i);

    if (chat->id() == chatId) {
      // update chat info
      MessageGQL *lastMessage = new MessageGQL(data, userId);
      chat->setLastMessage(lastMessage);

      QModelIndex currentRow = ChatsModel::createIndex(i, 0);
      dataChanged(currentRow, currentRow);
      if (i == 0) {
        break;
      }
      beginMoveRows(QModelIndex(), i, i, QModelIndex(), 0);
      for (int j = i; j > 0; j --) {
        m_list[j] = m_list[j - 1];
      }
      m_list[0] = chat;
      endMoveRows();
      break;
    }
  }
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
    case idRole: return m_list.at(index.row())->id();
    case messageRole: return m_list.at(index.row())->lastMessage()->getMessage();
    case dateRole: return m_list.at(index.row())->lastMessage()->getCreatedAt();

    default: return QVariant();
  }
}

QHash <int, QByteArray> ChatsModel::roleNames() const {
  QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[initialsRole] = "initials";
  roles[iconRole] = "icon";
  roles[messageRole] = "message";
  roles[dateRole] = "date";
  roles[idRole] = "id";

  return roles;
}
