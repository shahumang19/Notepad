#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "File does not exists");
        return;
    }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file_path = file_name;
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    if (file_path == ""){
        on_actionSave_As_triggered();
    }else{
        QFile file(file_path);
        if (!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "..", "File does not exists");
            return;
        }
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        file.flush();
        file.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save As File");
    QFile file(file_name);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "File does not exists");
        return;
    }
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file_path = file_name;
    file.flush();
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok);
    if (ok){
        ui->textEdit->setFont(font);
    }else return;

}
