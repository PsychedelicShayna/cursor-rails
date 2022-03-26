#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QtWidgets/QMainWindow>
#include <hotkey_recorder_widget.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    Ui::MainWindow* ui;

    HotkeyRecorderWidget* hotkeyRecorderHorizontalRail, *hotkeyRecorderVerticalRail;
    uint32_t              horizontalRailHotkeyId,        verticalRailHotkeyId;

    Q_SLOT void registerHorizontalRailHotkey(HotkeyRecorderWidget::Hotkey hotkey);
    Q_SLOT void registerVerticalRailHotkey(HotkeyRecorderWidget::Hotkey hotkey);

    Q_SLOT void on_spinBoxHorizontalHotkeyVkid_valueChanged(int);
    Q_SLOT void on_spinBoxVerticalHotkeyVkid_valueChanged(int);

    virtual bool nativeEvent(const QByteArray& event_type, void* message, qintptr* result) override;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() override;
};

#endif // MAINWINDOW_HXX
