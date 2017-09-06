#include "dialogaddstudent.h"
#include "ui_dialogadddevice.h"

DialogAddStudent::DialogAddStudent(int row, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DialogAddStudent)
{
    ui->setupUi(this);
    setupModel();
    if(row==-1){
        model->insertRow(model->index(row,0));
        mapper->toLast();
    } else{
        mapper->setCurrentModelIndex(model->index(row,0));
    }
    createUI();
}
DialogAddStudent::~DialogAddStudent()
{
    delete ui;
}
void DialogAddStudent::setupModel()
{
    model = new QSqlTableModel(this);
    model->setTable(STUDENT);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->StudentLineEdit,1);
    mapper->addMapping(ui->DateLineEdit,2);
    mapper->addMapping(ui->AgeLineEdit,3);
    connect(ui->previousButton,SIGNAL(clicked()),mapper,SLOT(toPrevious()));
    connect(ui->nextButton,SIGNAL(clicked()),mapper,SLOT(toNext()));
    connect(mapper,SIGNAL(currentIndexChanged(int)),this,SLOT(updateButtons(int)));
}
void DialogAddStudent::createUI()
{
    QString yearRange = "(?:[0-2]?[0-9]?[0-9]?[0-9])";
    QRegExp yearRegex = ("^"+yearRange+"$");
    QRegExpValidator *yearValidator = new QRegExpValidator(yearRegex,this);
    ui->YearLineEdit->setValidator(ipValidator);
}
void DialogAddStudent::on_buttonBox_accepted()
{
    QSqlQuery query;
    QString str = QString("SELECT EXISTS(SELECT" STUDENT_NAME "FROM" STUDENT
                          "WHERE(" STUDENT_NAME "=%1'"
                          "OR" STUDENT_YEAR "='%2')"
                          "AND id NOT LIKE '%3')").arg(ui->StudentLineEdit->text(),ui->YearLineEdit->text(),ui->AgeLineEdit->text(),model->data(model->index(mapper->currentIndex(),0),Qt::DisplayRole).toString());
    query.prepare(str);
    query.exec();
    query.next();
    if(query.value(0)!=0)
    {

    }
    else
    {
        mapper->submit();
        model->submitAll();
        emit signalReady();
        this->close();
    }
}

void DialogAddStudent::accept()
{

}

void DialogAddStudent::updateButtons(int row)
{
    ui->previousButton->setEnabled(row>0);
    ui->nextButton->setEnable(row<model->rowCount()-1);
}
