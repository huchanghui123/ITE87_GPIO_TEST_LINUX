#include "gpio_test.h"
#include "ui_gpio_test.h"
#include "QMessageBox"
#include "QDebug"
#include "sys/io.h"
#include "stdlib.h"

/* IO Ports */
#define REG		0x2e
#define VAL		0x2f

#define GPIO		0x07
#define LDNREG		0x07

GPIO_TEST::GPIO_TEST(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GPIO_TEST)
{
    ui->setupUi(this);
    init();
}

GPIO_TEST::~GPIO_TEST()
{
    delete ui;
}

void GPIO_TEST::closeEvent(QCloseEvent *event)
{
    printf("colse!!!\n");
    superio_exit();
    iopl(0);
}

int GPIO_TEST::init()
{
    int ret = iopl(3);
    if(ret == -1)
    {
        QMessageBox msg;
        msg.setText("iopl error.");
        msg.exec();
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        return -1;
    }
    superio_enter();
    superio_select(GPIO);
    get_gpio_info();
}

void GPIO_TEST::superio_enter()
{
    outb(0x87, REG);
    outb(0x01, REG);
    outb(0x55, REG);
    outb(0x55, REG);
}

void GPIO_TEST::superio_select(int ldn)
{
    outb(LDNREG, REG);
    outb(ldn, VAL);

    outb(0x2c, REG);
    outb(0x89, VAL);
}

void GPIO_TEST::superio_set_mode(int addr, int val)
{
    outb(addr, REG);
    outb(val, VAL);
}

void GPIO_TEST::superio_exit()
{
    outb(0x02, REG);
    outb(0x02, VAL);
}

void GPIO_TEST::get_gpio_info()
{
    outb(0xcf, REG);
    unsigned char c1 = inb(VAL);
    unsigned char c2 = inb(0xa07);
    qDebug() << c1 << c2 << endl;
    QString gp_m = QString::number(c1,16);
    QString gp_v = QString::number(c2,16);
    qDebug() << gp_m << gp_v << endl;
    ui->label_3->setText("GPIO MODE:"+gp_m);
    ui->label_4->setText("GPIO VALUE:"+gp_v);
}

void GPIO_TEST::on_pushButton_clicked()
{
    QString mString = ui->lineEdit->text().trimmed();
    bool ok;
    int val = mString.toInt(&ok,16);
    qDebug() << val << endl;
    superio_set_mode(0xcf,val);
    ui->lineEdit->setText("");
    get_gpio_info();
}

void GPIO_TEST::on_pushButton_2_clicked()
{
    QString mString = ui->lineEdit_2->text().trimmed();
    bool ok;
    int val = mString.toInt(&ok,16);
    qDebug() << val << endl;
    superio_set_mode(0xcf,0xff);
    outb(val,0xa07);
    ui->lineEdit_2->setText("");
    get_gpio_info();
}
