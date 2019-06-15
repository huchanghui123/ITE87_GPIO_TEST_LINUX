#ifndef GPIO_TEST_H
#define GPIO_TEST_H

#include <QMainWindow>

namespace Ui {
class GPIO_TEST;
}

class GPIO_TEST : public QMainWindow
{
    Q_OBJECT

public:
    explicit GPIO_TEST(QWidget *parent = 0);
    ~GPIO_TEST();
    int init();
    void superio_enter();
    void superio_exit();
    void superio_select(int);
    void superio_set_mode(int,int);
    void get_gpio_info();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GPIO_TEST *ui;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // GPIO_TEST_H
