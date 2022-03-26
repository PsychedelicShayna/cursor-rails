#include "main_window_dialog.hxx"
#include "ui_main_window_dialog.h"

MainWindow::MainWindow(QWidget* parent)
    :
      QMainWindow    { parent             },
      ui             { new Ui::MainWindow }
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

