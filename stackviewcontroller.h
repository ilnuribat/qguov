#ifndef STACKVIEWCONTROLLER_H
#define STACKVIEWCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QSettings>

class StackViewController : public QObject
{
    Q_OBJECT
  public:
    explicit StackViewController(QObject *parent = nullptr);

  signals:

  public slots:
  private:
    QSettings *settings;
};

#endif // STACKVIEWCONTROLLER_H
