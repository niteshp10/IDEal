#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setDir(QString fileDir);
    QString getDir();
    QCharRef check(QString fileName);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButtonCompile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonBuild_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_action_Exit_triggered();

    void on_action_Save_triggered();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    QString fileName;
};

#endif // MAINWINDOW_H
