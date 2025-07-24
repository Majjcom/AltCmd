#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsDropShadowEffect>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>
#include <QMenuBar>
#include <QTimer>
#include <QDebug>
#include <QDir>

#include <Windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowType::FramelessWindowHint);
    setWindowFlag(Qt::WindowType::WindowStaysOnTopHint);
    setWindowFlag(Qt::WindowType::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowIcon(QIcon("://icon.png"));

    system_icon = new QSystemTrayIcon(this);
    system_icon->setToolTip("Alt Cmd App");
    system_icon->setIcon(QIcon("://icon.png"));
    system_icon->show();

    hotkey = new QHotkey(QKeySequence(Qt::ALT + Qt::Key_Space), true, this);

    shortcut_esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    shortcut_esc->setContext(Qt::ShortcutContext::WidgetWithChildrenShortcut);

    action_exit = new QAction("Exit", this);

    menu_tray = new QMenu(this);
    menu_tray->addAction(action_exit);

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(ui->widget);
    effect->setBlurRadius(50);
    effect->setColor(QColor(0, 0, 0, 100));
    effect->setOffset(0, 10);
    ui->widget->setGraphicsEffect(effect);

    connect(
        shortcut_esc,
        SIGNAL(activated()),
        this,
        SLOT(shortcutEsc())
    );

    connect(
        hotkey,
        SIGNAL(activated()),
        this,
        SLOT(globalHotkey())
    );

    connect(
        system_icon,
        SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this,
        SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason))
    );

    connect(
        action_exit,
        SIGNAL(triggered()),
        this,
        SLOT(actionExit())
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    //qDebug() << "Event: " << event;
    if (event->key() == Qt::Key_Return)
    {
        bool show = event->modifiers() & Qt::ControlModifier;
        if (event->modifiers() & Qt::ShiftModifier)
        {
            runCmd(true, show);
        }
        else
        {
            runCmd(false, show);
        }
        event->accept();
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::runCmd(const bool super, const bool show)
{
    QString cmd = ui->lineEdit->text();
    if (cmd.isEmpty())
    {
        hideWindow();
        return;
    }

    HINSTANCE hResult = ::ShellExecuteA(
        NULL,
        super ? "runas" : "open",
        "cmd.exe",
        QString("/c %0").arg(cmd).toLocal8Bit().data(),
        QDir::homePath().toLocal8Bit().data(),
        show
    );

    if ((INT_PTR)hResult <= 32)
    {
        QMessageBox::critical(this, "Error", QString("Run command error.\nError code is: %0").arg((INT_PTR)hResult));
    }
    else
    {
        ui->lineEdit->clear();
        hideWindow();
    }
}

void MainWindow::actionExit()
{
    QApplication::quit();
}

void MainWindow::globalHotkey()
{
    if (this->isHidden())
    {
        showWindow();
    }
    else
    {
        hideWindow();
    }
}

void MainWindow::shortcutEsc()
{
    hideWindow();
}

void MainWindow::hideWindow()
{
    hide();
}

void MainWindow::showWindow()
{
    show();
    ui->lineEdit->selectAll();

    QTimer::singleShot(300, [=]{
        this->activateWindow();
        ui->lineEdit->setFocus();
    });

}

void MainWindow::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::ActivationReason::Context:
        menu_tray->exec(cursor().pos());
        break;
    case QSystemTrayIcon::ActivationReason::Trigger:
        showWindow();
        break;
    default:
        break;
    }
}
