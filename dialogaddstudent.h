#ifndef DIALOGADDSTUDENT_H
#define DIALOGADDSTUDENT_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include <database.h>
namespace Ui {
class DialogAddStudent;
}
class DialogAddStudent
{
    Q_OBJECT
public:
    explicit DialogAddStudent(int row =-1, QWidget *parent=0);
    ~DialogAddStudent();
signals:
    void signalReady();
private slots:
    void on_buttonBox_accepted();
    void updateButtons(int row);
private:
    Ui::DialogAddStudent *ui;
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;
private:
    void setupModel();
    void createUI();
    void accept();
};

#endif // DIALOGADDSTUDENT_H
