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

    Q_INVOKABLE void handleAuthToken();

    void goChatsListPage();

  signals:
    void goToPageChanged(QString page);

  public slots:
  private:
    QSettings *settings;
    QString m_lastGoToPage;
};

#endif // STACKVIEWCONTROLLER_H
