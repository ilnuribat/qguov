QT += quick quickcontrols2 websockets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
  main.cpp \
  logincontroller.cpp \
  stackviewcontroller.cpp \
  chatsmodel.cpp \
  httpclient.cpp \
  globalstore.cpp \
  chatlistcontroller.cpp \
    chatcontroller.cpp \
    messagesmodel.cpp \
    cpp/websocket/websocket.cpp \
    cpp/websocket/messageaddedsubscription.cpp \
    messagegql.cpp \
    directgql.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
  logincontroller.h \
  stackviewcontroller.h \
  chatsmodel.h \
  httpclient.h \
  globalstore.h \
  chatlistcontroller.h \
    chatcontroller.h \
    messagesmodel.h \
    cpp/websocket/websocket.h \
    cpp/websocket/messageaddedsubscription.h \
    messagegql.h \
    directgql.h

DISTFILES += \
  initPage.qml \
  login.qml \
  main.qml \
  chatList.qml \
    Chat.qml \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    logo.png

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
