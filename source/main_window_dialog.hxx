#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    Ui::MainWindow* ui;

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;
};

#endif // MAINWINDOW_HXX
