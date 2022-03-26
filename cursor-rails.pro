TEMPLATE = app
QT += core gui widgets

CONFIG += c++17

QMAKE_CXXFLAGS += /std:c++17

TARGET = cursor-rails

INCLUDEPATH += hotkey-recorder-widget-qt/source/

SOURCES += \
    source/main.cpp \
    source/main_window_dialog.cxx \
    hotkey-recorder-widget-qt/source/hotkey_recorder_widget.cpp

HEADERS += \
    source/main_window_dialog.hxx \
    hotkey-recorder-widget-qt/source/hotkey_recorder_widget.hpp

FORMS += \
    source/main_window_dialog.ui
