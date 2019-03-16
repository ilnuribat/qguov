#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QDebug>
class LoginController : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
  Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
  Q_INVOKABLE void submitLogin();

public:
  explicit LoginController(QObject *parent = nullptr);

  QString login();
  void setLogin(const QString login);

  QString password();
  void setPassword(const QString password);

signals:
  void loginChanged(QString login);
  void passwordChanged(QString password);

private:
  QString m_login;
  QString m_password;

public slots:
};

#endif // LOGINCONTROLLER_H
