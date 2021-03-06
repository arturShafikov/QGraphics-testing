#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clickablegraphicsview.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void hideButtonChecked(bool checked);

private:
    Ui::MainWindow *ui;
    ClickableGraphicsView *graphicsView;
};
#endif // MAINWINDOW_H
