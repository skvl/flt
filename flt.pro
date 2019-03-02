TRANSLATIONS = translations/ru.ts

HEADERS = DataBase.h \
          HistoryTable.h \
          Settings.h \
          Word.h \
          HistoryRecord.h \
          Sentence.h

SOURCES = main.cpp \
          HistoryRecord.cpp \
          HistoryTable.cpp \
          Word.cpp \
          Settings.cpp \
          DataBase.cpp \
          Sentence.cpp

lupdate_only{
    SOURCES += Settings.qml \
               Results.qml \
               main.qml \
               StartPage.qml \
               History.qml \
               Board.qml
}
