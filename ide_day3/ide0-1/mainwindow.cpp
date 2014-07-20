#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QProcess>
#include<QFileDialog>
#include<QTextStream>
#include <string.h>
#include<QFileInfo>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString ttCompile = "Compile and run the code";
    ui->pushButtonCompile->setToolTip(ttCompile);
    QString ttBuild = "Compile the code";
    ui->pushButtonBuild->setToolTip(ttBuild);
    QString ttRun = "Run the code";
    ui->pushButtonRun->setToolTip(ttRun);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonCompile_clicked()
{
    QProcess proc;
    if(fileName.endsWith(".c",Qt::CaseSensitive) )
       proc.start("gcc "+ fileName);
    if(fileName.endsWith(".cpp",Qt::CaseSensitive) )
       proc.start("g++ "+ fileName);
    else if(fileName.endsWith(".java",Qt::CaseSensitive) )
        proc.start("javac " + fileName);
    proc.waitForFinished();
    QByteArray result = proc.readAllStandardOutput();
    QByteArray error = proc.readAllStandardError();
    QString command1(result);
    QString command2(error);
    ui ->labelError->setText(command2);
    if(command2.isEmpty()) {
        if(fileName.endsWith(".c",Qt::CaseSensitive)||fileName.endsWith(".cpp",Qt::CaseSensitive) )
            proc.start("/home/pushkar/Documents/ide/ide_day1/build-ide0-1-Desktop-Release/a.out");
        else if(fileName.endsWith(".java",Qt::CaseSensitive) )
        {

            QString croped_fileName=fileName.split(".",QString::SkipEmptyParts).at(0);
            QFileInfo fi(croped_fileName);
            QString base = fi.baseName();
            //ui->textEditCoding->setText(croped_fileName);
            QStringList env;
            env << "CLASSPATH=/home/pushkar/";
            proc.setEnvironment(env);
            proc.start("java " + base);

        }
        else if(fileName.endsWith(".py",Qt::CaseSensitive) )
            proc.start("python "+ fileName);

        proc.waitForFinished();
        result = proc.readAllStandardOutput();
        error = proc.readAllStandardError();
        command1.append(result);
        ui ->textEditOutput->setText(command1);
    }
    //ui ->textEditOutput->setText("");
}

void MainWindow::on_pushButtonRun_clicked()
{
    QProcess proc;
    if(fileName.endsWith(".c",Qt::CaseSensitive)||fileName.endsWith(".cpp",Qt::CaseSensitive) )
        proc.start("/home/pushkar/Documents/ide/ide_day1/build-ide0-1-Desktop-Debug/a.out");
    else if(fileName.endsWith(".py",Qt::CaseSensitive) )
        proc.start("python "+ fileName);
    else if(fileName.endsWith(".java",Qt::CaseSensitive) )
    {

        QString croped_fileName=fileName.split(".",QString::SkipEmptyParts).at(0);
        QFileInfo fi(croped_fileName);
        QString base = fi.baseName();
        //ui->textEditCoding->setText(croped_fileName);
        QStringList env;
        env << "CLASSPATH=/home/pushkar/";
        proc.setEnvironment(env);
        proc.start("java " + base);

    }
    proc.waitForFinished();
    QByteArray result = proc.readAllStandardOutput();
    QByteArray error = proc.readAllStandardError();
    QString command1(result + "\n" + error);
    ui->textEditOutput->setText(command1);

    ui->labelError->setText("");
}

void MainWindow::on_pushButtonBuild_clicked()
{
    QProcess proc;
    if(fileName.endsWith(".c",Qt::CaseSensitive))
       proc.start("gcc "+ fileName);
    else if(fileName.endsWith(".cpp",Qt::CaseSensitive) )
        proc.start("g++ "+ fileName);
    else if(fileName.endsWith(".java",Qt::CaseSensitive) )
        proc.start("javac "+ fileName);
    else if(fileName.endsWith(".py",Qt::CaseSensitive))
        proc.start("python "+ fileName);
    proc.waitForFinished();
    QByteArray error = proc.readAllStandardError();
    ui ->textEditOutput->setText("");
    QString command2(error);
    ui ->labelError->setText(command2);
    ui ->textEditOutput->setText("");
}

void MainWindow::on_actionSave_triggered()
{
    fileName = QFileDialog::getSaveFileName(this,
         tr("Save File as ..."), "/home/pushkar", tr("All Files (*.c *.cpp *.java *.py)"));

    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly);
    QByteArray code;
    code.append(ui->textEditCoding->toPlainText());
    file.write(code);        // write to stderr
    file.close();
}

void MainWindow::on_actionOpen_triggered()
{

        fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "", tr("All Files (*.c *.cpp *.java *.py)"));
        QFile file1(fileName);
        if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QString text(file1.readAll());
        //text.append(fileName);
        ui->textEditCoding->setText(text);

}


void MainWindow::on_action_Exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_Save_triggered()
{
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly);
    QByteArray code;
    code.append(ui->textEditCoding->toPlainText());
    file.write(code);        // write to stderr
    //fileName = " ";
    file.close();
}

void MainWindow::on_actionNew_triggered()
{
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly);
    QByteArray code;
    code.append(ui->textEditCoding->toPlainText());
    file.write(code);        // write to stderr
    file.close();
    ui->textEditCoding->setText(" ");
    ui->textEditOutput->setText(" ");
    ui->labelError->setText(" ");
}
