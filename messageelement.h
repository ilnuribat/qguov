#ifndef MESSAGEELEMENT_H
#define MESSAGEELEMENT_H

#include <QString>

class MessageElement
{
  public:
    MessageElement(QString id, QString text, QString initials);

    QString getId() const;
    QString getText() const;
    QString getInitials() const;

  private:
    QString m_id;
    QString m_text;
    QString m_initials;
};

#endif // MESSAGEELEMENT_H
