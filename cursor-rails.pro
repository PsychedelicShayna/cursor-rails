TEMPLATE = app
QT += core gui widgets

CONFIG += c++17

QMAKE_CXXFLAGS += /std:c++17

TARGET = cursor-rails

SOURCES += \
    source/main.cpp \
    source/main_window_dialog.cxx

HEADERS += \
    source/main_window_dialog.hxx

FORMS += \
    source/main_window_dialog.ui
