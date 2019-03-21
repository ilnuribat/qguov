#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "httpclient.h"
#include "logincontroller.h"
#include "stackviewcontroller.h"
#include "chatsmodel.h"
#include "globalstore.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQuickStyle::setStyle("Material");

  qmlRegisterType<LoginController>("QGuov.Controller.Login", 1, 0, "LoginController");
  qmlRegisterType<StackViewController>("QGuov.Controller.StackView", 1, 0, "StackViewController");
  qmlRegisterType<ChatsModel>("QGuov.Model.ChatsModel", 1, 0, "ChatsModel");
  qmlRegisterType<GlobalStore>("QGuov.Model.GlobalStore", 1, 0, "GlobalStore");

  QQmlApplicationEngine engine;

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}
