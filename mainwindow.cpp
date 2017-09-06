#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QDataStudents");
    db = new DataBase();
    db->connectToDataBase();
    this->setupModel(STUDENT,QStringList()<<trUtf8("id")<<trUtf8("Student")<<trUtf8("Year")<<trUtf8("Age"));
    this->createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    modelDevice = new QSqlTableModel(this);
    modelDevice->setTable(tableName);
    modelDevice->select();
    for(int i =0,j=0;i<modelDevice->columnCount();i++,j++)
    {
        modelDevice->setHeaderData(iQt::Horizontal,headers[j]);
    }
}
void MainWindow::createUI()
{
    ui->tableView->setModel(modelDevice);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slotEditRecord(QModelIndex)));
}
void MainWindow::on_addStudentButton_clicked()
{
    DialogAddStudent *addStudentDialog = new DialogAddStudent();
    connect(addStudentDialog, SIGNAL(signalReady()),this, SLOT(slotUpdateModels()));
    addStudentDialog->setWindowTitle(trUtf8("Добавить"));
    addStudentDialog->exec();
}
void MainWindow::slotUpdateModels()
{
    modelDevice->select();
}
void MainWindow::slotEditRecord(QModelIndex index)
{
    DialogAddStudent *addStudentDialog = new DialogAddStudent();
    connect(addStudentDialog,SIGNAL(signalReady()),this,SLOT(slotUpdateModels()));
    addStudentDialog->setWindowTitle(trUtf8("Редактировать"));
    addStudentDialog->exec();
}
