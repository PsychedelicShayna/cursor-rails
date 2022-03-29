#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#include <Windows.h>

#include <QtCore/QResource>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QTimer>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>

#include <hotkey_recorder_widget.hpp>
#include <vkid_table_widget.hpp>

#include "vkid_table_widget_dialog.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern qsizetype ApplyStylesheetFile(QWidget* widget, const QString& stylesheet_file_path);

class MainWindow : public QMainWindow {
Q_OBJECT

signals:
    void horizontalRailHotkeyPressed();
    void verticalRailHotkeyPressed();

protected:
    Ui::MainWindow* ui;

    VkidTableWidgetDialog* vkidTableWidgetDialog;

    HotkeyRecorderWidget* hotkeyRecorderHorizontalRail,
                        * hotkeyRecorderVerticalRail;

    struct CursorRailData {
        uint32_t    hotkeyId;
        uint32_t    hotkeyVkid;
        RECT        railRect;
        POINT       cursorPos;
        bool        activated;

        CursorRailData(const quint32& hotkey_id);
    } horizontalRail, verticalRail;

    QTimer* timerApplyActivatedRails;

public slots:
    void toggleHorizontalRailActivated();
    void toggleVerticalRailActivated();

    void registerHorizontalRailHotkey(HotkeyRecorderWidget::Hotkey hotkey);
    void registerVerticalRailHotkey(HotkeyRecorderWidget::Hotkey hotkey);

    void spawnVkidTableDialog();

protected:
    virtual void mousePressEvent(QMouseEvent* mouse_press_event) override;
    virtual bool nativeEvent(const QByteArray& event_type, void* message, qintptr* result) override;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() override;
};

#endif // MAINWINDOW_HXX
