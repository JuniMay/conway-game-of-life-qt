
QT+=widgets
TEMPLATE = app
TARGET = conway-game-of-life-qt
INCLUDEPATH += .
INCLUDEPATH += ./include

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += include/common.h \
           include/game_view.h \
           include/loader.h \
           include/main_window.h \

SOURCES += src/game_view.cpp \
           src/loader.cpp\
           src/main.cpp \
           src/main_window.cpp
