#include "chatsmodel.h"

ChatsModel::ChatsModel(QObject *parent): QAbstractListModel (parent)
{
  qDebug() << "init of chatsModel";
  m_list.append(new ChatListElement("Maxim", "http://dev.scis.xyz/images/download", "good!", QDateTime::fromString("2019-03-20", "yyyy-MM-dd")));
  m_list.append(new ChatListElement("Kirill", "http://dev.scis.xyz/images/Ибатуллин Ильнур Тимерьярович", "ok", QDateTime::fromString("2019-03-19", "yyyy-MM-dd")));

  HttpClient *httpClient = new HttpClient();
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
