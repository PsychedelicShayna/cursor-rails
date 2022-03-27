#include "main_window_dialog.hxx"
#include "ui_main_window_dialog.h"

qsizetype ApplyStylesheetFile(QWidget* widget, const QString& stylesheet_file_path) {
    QFileInfo style_sheet_file_info { stylesheet_file_path };

    if(style_sheet_file_info.exists() && style_sheet_file_info.isFile()) {
        QFile style_sheet_file_stream { stylesheet_file_path };

        if(style_sheet_file_stream.open(QFile::ReadOnly)) {
            const QByteArray& style_sheet_data { style_sheet_file_stream.readAll() };
            style_sheet_file_stream.close();

            if(style_sheet_data.size()) {
                QFileInfo resource_file_info { QString { "%1/%2.rcc" }.arg(style_sheet_file_info.path(), style_sheet_file_info.completeBaseName()) };

                if(resource_file_info.exists() && resource_file_info.isFile()) {
                    QResource::registerResource(resource_file_info.absoluteFilePath());
                }

                widget->setStyleSheet(QString::fromLocal8Bit(style_sheet_data));
            }

            return style_sheet_data.size();
        }
    }
}

MainWindow::CursorRailData::CursorRailData(const uint32_t& hotkey_id)
    :
      hotkeyId    { hotkey_id  },
      hotkeyVkid  { NULL       },
      railRect    { 0, 0, 0, 0 },
      cursorPos   { 0, 0       },
      activated   { false      }
{

}

void MainWindow::toggleHorizontalRailActivated() {
    if(horizontalRail.activated) {
        horizontalRail.activated = false;
        ClipCursor(nullptr);
    } else {
        POINT cursor_position;

        if(GetCursorPos(&cursor_position)) {
            RECT new_rail_rect;

            HWND desktop_window { GetDesktopWindow() };

            if(GetWindowRect(desktop_window, &new_rail_rect)) {
                new_rail_rect.top = cursor_position.y - 1;
                new_rail_rect.bottom = cursor_position.y;

                horizontalRail.railRect = new_rail_rect;
                GetCursorPos(&horizontalRail.cursorPos);

                horizontalRail.activated = true;
                ui->checkBoxHorizontalRail->setChecked(true);

                verticalRail.activated = false;
                ui->checkBoxVerticalRail->setChecked(false);

                timerApplyActivatedRails->start(300);
            }
        }
    }
}

void MainWindow::toggleVerticalRailActivated() {
    if(verticalRail.activated) {
        verticalRail.activated = false;
        ClipCursor(nullptr);
    } else {
        POINT cursor_position;

        if(GetCursorPos(&cursor_position)) {
            RECT new_rail_rect;

            HWND desktop_window { GetDesktopWindow() };

            if(GetWindowRect(desktop_window, &new_rail_rect)) {
                new_rail_rect.left = cursor_position.x - 1;
                new_rail_rect.right = cursor_position.x;

                verticalRail.railRect = new_rail_rect;
                GetCursorPos(&horizontalRail.cursorPos);

                verticalRail.activated = true;
                ui->checkBoxVerticalRail->setChecked(true);

                horizontalRail.activated = false;
                ui->checkBoxHorizontalRail->setChecked(false);

                timerApplyActivatedRails->start(300);
            }
        }
    }
}

void MainWindow::registerHorizontalRailHotkey(HotkeyRecorderWidget::Hotkey hotkey) {
    UnregisterHotKey(HWND(winId()), horizontalRail.hotkeyId);
    RegisterHotKey(HWND(winId()), horizontalRail.hotkeyId, MOD_NOREPEAT | hotkey.Modifiers, hotkey.Vkid);
    horizontalRail.hotkeyVkid = hotkey.Vkid;
    ui->spinBoxHorizontalHotkeyVkid->setValue(hotkey.Vkid);
}

void MainWindow::registerVerticalRailHotkey(HotkeyRecorderWidget::Hotkey hotkey) {
    UnregisterHotKey(HWND(winId()), verticalRail.hotkeyId);
    RegisterHotKey(HWND(winId()), verticalRail.hotkeyId, MOD_NOREPEAT | hotkey.Modifiers, hotkey.Vkid);
    verticalRail.hotkeyVkid = hotkey.Vkid;
    ui->spinBoxVerticalHotkeyVkid->setValue(hotkey.Vkid);
}

bool MainWindow::nativeEvent(const QByteArray& event_type, void* message, qintptr* result) {
    MSG* msg { reinterpret_cast<MSG*>(message) };

    if(msg->message == WM_HOTKEY) {
        if(msg->wParam == horizontalRail.hotkeyId) {
            emit horizontalRailHotkeyPressed();
            return true;
        }

        else if(msg->wParam == verticalRail.hotkeyId) {
            emit verticalRailHotkeyPressed();
            return true;
        }
    }

    QMainWindow::nativeEvent(event_type, message, result);
}

MainWindow::MainWindow(QWidget* parent)
    :
      QMainWindow                     { parent                            },
      ui                              { new Ui::MainWindow                },
      hotkeyRecorderHorizontalRail    { new HotkeyRecorderWidget { this } },
      hotkeyRecorderVerticalRail      { new HotkeyRecorderWidget { this } },
      horizontalRail                  { 0x41414141                        },
      verticalRail                    { 0x42424242                        },
      timerApplyActivatedRails        { new QTimer { this }               }
{
    ui->setupUi(this);

    ApplyStylesheetFile(this, "./styles/indigo.qss");

    setWindowFlags(
                Qt::Dialog
                | Qt::CustomizeWindowHint
                | Qt::WindowTitleHint
                | Qt::WindowCloseButtonHint
                | Qt::WindowMinimizeButtonHint
                | Qt::WindowMaximizeButtonHint
                );

    hotkeyRecorderHorizontalRail->setPlaceholderText("Horizontal Rail Toggle Hotkey");
    hotkeyRecorderVerticalRail->setPlaceholderText("Vertical Rail Toggle Hotkey");

    ui->checkBoxHorizontalRail->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBoxHorizontalRail->setFocusPolicy(Qt::NoFocus);

    ui->checkBoxVerticalRail->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkBoxVerticalRail->setFocusPolicy(Qt::NoFocus);

    ui->horizontalLayoutHotkeyRecorders->addWidget(hotkeyRecorderHorizontalRail);
    ui->horizontalLayoutHotkeyRecorders->addWidget(hotkeyRecorderVerticalRail);

    connect(hotkeyRecorderHorizontalRail, &HotkeyRecorderWidget::HotkeyRecorded,
            this,                         &MainWindow::registerHorizontalRailHotkey);

    connect(hotkeyRecorderVerticalRail,   &HotkeyRecorderWidget::HotkeyRecorded,
            this,                         &MainWindow::registerVerticalRailHotkey);

    connect(this,                         &MainWindow::horizontalRailHotkeyPressed,
            this,                         &MainWindow::toggleHorizontalRailActivated);

    connect(this,                         &MainWindow::verticalRailHotkeyPressed,
            this,                         &MainWindow::toggleVerticalRailActivated);

    connect(ui->spinBoxHorizontalHotkeyVkid, &QSpinBox::valueChanged, [this](quint32 new_value) -> void {
        if(horizontalRail.hotkeyVkid != new_value) {
            HotkeyRecorderWidget::Hotkey hotkey;
            hotkey.Vkid = new_value;

            hotkeyRecorderHorizontalRail->clear();
            registerHorizontalRailHotkey(hotkey);
        }
    });

    connect(ui->spinBoxVerticalHotkeyVkid, &QSpinBox::valueChanged, [this](quint32 new_value) -> void {
        if(verticalRail.hotkeyVkid != new_value) {
            HotkeyRecorderWidget::Hotkey hotkey;
            hotkey.Vkid = new_value;

            hotkeyRecorderVerticalRail->clear();
            registerVerticalRailHotkey(hotkey);
        }
    });

    connect(timerApplyActivatedRails, &QTimer::timeout, [this]() -> void {
        POINT cursor_position { 0, 0 };

        if(!GetCursorPos(&cursor_position)) {
            return;
        }

        if(horizontalRail.activated && !verticalRail.activated) {
            SetCursorPos(cursor_position.x, horizontalRail.cursorPos.y);
            ClipCursor(&horizontalRail.railRect);
        }

        else if(verticalRail.activated && !horizontalRail.activated) {
            SetCursorPos(verticalRail.cursorPos.x, cursor_position.y);
            ClipCursor(&verticalRail.railRect);
        }

        else {
            horizontalRail.activated = false;
            verticalRail.activated = false;
            ui->checkBoxHorizontalRail->setChecked(false);
            ui->checkBoxVerticalRail->setChecked(false);
            ClipCursor(nullptr);

            timerApplyActivatedRails->stop();
        }
    });

    hotkeyRecorderHorizontalRail->StartRecording();
    hotkeyRecorderVerticalRail->StartRecording();

    setMaximumHeight(height());
}

MainWindow::~MainWindow() {
    delete ui;
}

