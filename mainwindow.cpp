#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const auto labeller = {ui->kos1, ui->kos2, ui->kos3,
                          ui->kos4, ui->kos5, ui->kos6,
                          ui->kos7, ui->kos8, ui->kos9};

    for (QLabel *label : labeller) {
        auto *timer = new QTimer(this);
        kuyular.insert(label, {timer, false});

        label->installEventFilter(this);
        label->setScaledContents(true);
        label->setPixmap(kuyuGorseli);

        connect(timer, &QTimer::timeout, this, [this, label] {
            Kuyu &kuyu = kuyular[label];
            kuyu.kostebekDisarida = !kuyu.kostebekDisarida;
            label->setPixmap(kuyu.kostebekDisarida ? kostebekGorseli : kuyuGorseli);
            kuyu.timer->setInterval(kuyu.kostebekDisarida
                ? QRandomGenerator::global()->bounded(500, 1000)
                : QRandomGenerator::global()->bounded(1000, 4000));
        });
        timer->start(QRandomGenerator::global()->bounded(1000, 4000));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress
        && static_cast<QMouseEvent *>(event)->button() == Qt::LeftButton) {
        auto *label = qobject_cast<QLabel *>(obj);
        auto kuyu = kuyular.find(label);
        if (kuyu != kuyular.end() && kuyu->kostebekDisarida) {
            kuyu->kostebekDisarida = false;
            kuyu->timer->stop();
            label->setPixmap(sersemKostebekGorseli);
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
