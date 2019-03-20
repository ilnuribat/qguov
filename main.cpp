#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "httpclient.h"
#include "logincontroller.h"
#include "stackviewcontroller.h"
#include "chatsmodel.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQuickStyle::setStyle("Material");

  qmlRegisterType<LoginController>("QGuov.Controller.Login", 1, 0, "LoginController");
  qmlRegisterType<StackViewController>("QGuov.Controller.StackView", 1, 0, "StackViewController");
  qmlRegisterType<ChatsModel>("QGuov.Model.ChatsModel", 1, 0, "ChatsModel");

  QQmlApplicationEngine engine;

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  QObject *obj = engine.findChild<QObject*>("stackView");

  if (obj) {
    qDebug() << "object found!";
  } else {
    qDebug() << "object not found";
  }

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
