TEMPLATE = app
QT += core gui widgets

CONFIG += c++17

QMAKE_CXXFLAGS += /std:c++17

TARGET = cursor-rails

SOURCES += \
    source/main.cpp \
    source/main_window_dialog.cxx \
    source/vkid_table_widget_dialog.cxx

HEADERS += \
    source/main_window_dialog.hxx \
    source/vkid_table_widget_dialog.hxx

FORMS += \
    source/main_window_dialog.ui \
    source/vkid_table_widget_dialog.ui

LIBS += user32.lib

INCLUDEPATH += submodules/qt-hotkey-recorder-widget/source/
SOURCES     += submodules/qt-hotkey-recorder-widget/source/hotkey_recorder_widget.cpp
HEADERS     += submodules/qt-hotkey-recorder-widget/source/hotkey_recorder_widget.hpp

INCLUDEPATH += submodules/qt-vkid-table-widget/source
SOURCES     += submodules/qt-vkid-table-widget/source/vkid_table_widget.cpp
HEADERS     += submodules/qt-vkid-table-widget/source/vkid_table_widget.hpp
