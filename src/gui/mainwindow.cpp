#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_Ui(std::make_unique<Ui::MainWindow>())
{
    m_Ui->setupUi(this);
}

MainWindow::~MainWindow()
{
}
