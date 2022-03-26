#include "main_window_dialog.hxx"
#include "ui_main_window_dialog.h"

void MainWindow::registerHorizontalRailHotkey(HotkeyRecorderWidget::Hotkey hotkey) {

}

void MainWindow::registerVerticalRailHotkey(HotkeyRecorderWidget::Hotkey hotkey) {

}

void MainWindow::on_spinBoxHorizontalHotkeyVkid_valueChanged(int) {

}

void MainWindow::on_spinBoxVerticalHotkeyVkid_valueChanged(int) {

}

bool MainWindow::nativeEvent(const QByteArray& event_type, void* message, qintptr* result) {


    QMainWindow::nativeEvent(event_type, message, result);
}

MainWindow::MainWindow(QWidget* parent)
    :
      QMainWindow                     { parent                            },
      ui                              { new Ui::MainWindow                },
      hotkeyRecorderHorizontalRail    { new HotkeyRecorderWidget { this } },
      hotkeyRecorderVerticalRail      { new HotkeyRecorderWidget { this } },
      horizontalRailHotkeyId          { 0x41414141                        },
      verticalRailHotkeyId            { 0x42424242                        }
{
    ui->setupUi(this);

    setWindowFlags(
                Qt::Dialog
                | Qt::CustomizeWindowHint
                | Qt::WindowTitleHint
                | Qt::WindowCloseButtonHint
                | Qt::WindowMinimizeButtonHint
                | Qt::WindowMaximizeButtonHint
                );

    ui->horizontalLayoutHotkeyRecorders->addWidget(hotkeyRecorderHorizontalRail);
    ui->horizontalLayoutHotkeyRecorders->addWidget(hotkeyRecorderVerticalRail);

    connect(hotkeyRecorderHorizontalRail, SIGNAL(HotkeyRecorded(HotkeyRecorderWidget::WindowsHotkey)),
            this,                         SLOT(registerHorizontalRailHotkey));

    connect(hotkeyRecorderVerticalRail,   SIGNAL(HotkeyRecorded(HotkeyRecorderWidget::WindowsHotkey)),
            this,                         SLOT(registerVerticalRailHotkey));

    hotkeyRecorderHorizontalRail->StartRecording();
    hotkeyRecorderVerticalRail->StartRecording();

    setMaximumHeight(height());
}

MainWindow::~MainWindow() {
    delete ui;
}

