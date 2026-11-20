#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHash>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    struct Kuyu {
        QTimer *timer;
        bool kostebekDisarida;
    };

    Ui::MainWindow *ui;
    QHash<QLabel *, Kuyu> kuyular;
    const QPixmap kuyuGorseli{":/new/image/image/kuyu.png"};
    const QPixmap kostebekGorseli{":/new/image/image/kostebek.png"};
    const QPixmap sersemKostebekGorseli{":/new/image/image/SersemKostebek.png"};
};

#endif
