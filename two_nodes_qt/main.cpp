#include "one_node.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OneNode w;
    w.show();
    return a.exec();
}
