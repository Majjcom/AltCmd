#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QHotKey>
#include <QAction>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void trayIconClicked(QSystemTrayIcon::ActivationReason reason);
    void globalHotkey();
    void shortcutEsc();
    void actionExit();

private:
    Ui::MainWindow *ui;
    QShortcut* shortcut_esc;
    QHotkey* hotkey;
    QSystemTrayIcon* system_icon;
    QMenu* menu_tray;
    QAction* action_exit;

    void hideWindow();
    void showWindow();
    void runCmd(bool super, bool show);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent* event);

};
#endif // MAINWINDOW_H
