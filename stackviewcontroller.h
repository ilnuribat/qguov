#ifndef STACKVIEWCONTROLLER_H
#define STACKVIEWCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QSettings>

class StackViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentPage READ currentPage NOTIFY onCurrentPageChanged)

  public:
    explicit StackViewController(QObject *parent = nullptr);

    Q_INVOKABLE void handleAuthToken();

    QString currentPage() const;

  signals:
    void goToPageChanged(QString page);
    void onCurrentPageChanged();

  public slots:
  private:
    QSettings *settings;
    QString m_lastGoToPage;
};

#endif // STACKVIEWCONTROLLER_H
