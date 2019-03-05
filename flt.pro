QT += multimedia quick quickcontrols2 xml
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#           ORGNAME=\\\"Sergey Kovalev\\\" \
#           APPNAME=\\\"Foreign Language Trainer\\\"


# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
           DataBase.cpp \
           HistoryRecord.cpp \
           HistoryTable.cpp \
           Sentence.cpp \
           Settings.cpp \
           Word.cpp

HEADERS += DataBase.h \
           HistoryRecord.h \
           HistoryTable.h \
           Sentence.h \
           Settings.h \
           Word.h

RESOURCES += qml.qrc translations.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS = translations/ru.ts

lupdate_only{
    SOURCES += Settings.qml \
               Results.qml \
               main.qml \
               StartPage.qml \
               History.qml \
               Board.qml
}
