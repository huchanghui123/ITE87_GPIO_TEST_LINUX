#include "gpio_test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GPIO_TEST w;
    w.show();

    return a.exec();
}
