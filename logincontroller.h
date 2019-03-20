#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QJsonObject>
#include <QJsonArray>
#include "httpclient.h"
#include "stackviewcontroller.h"

class LoginController : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
  Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
  Q_PROPERTY(QString resultMessage READ resultMessage NOTIFY resultMessageChanged)
  Q_PROPERTY(QObject *stackView WRITE setStackView)

public:
  explicit LoginController(QObject *parent = nullptr);

  QString login();
  void setLogin(const QString login);

  QString password();
  void setPassword(const QString password);

  QString resultMessage() const;

  void setStackView(QObject *stackView);

signals:
  void loginChanged();
  void passwordChanged();
  void resultMessageChanged();

public slots:
  void submitLogin();
  void loginResponse(QJsonObject &jsonObject);

private:
  QString m_login;
  QString m_password;
  QSettings *settings;
  QString m_resultMessage = "good!";
  StackViewController *m_stackView;

public slots:
};

#endif // LOGINCONTROLLER_H
