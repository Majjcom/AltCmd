#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const int font_id = QFontDatabase::addApplicationFont("://fonts/MapleMono-SC-NF-Regular.ttf");
    QFontDatabase::addApplicationFont("://fonts/MapleMono-SC-NF-LightItalic.ttf");
    QString font_name = QFontDatabase::applicationFontFamilies(font_id)[0];

    QFont font(font_name);
    a.setFont(font);

    MainWindow w;
    return a.exec();
}
