#include "AddFeedDialog.h"
#include "ui_AddFeedDialog.h"

AddFeedDialog::AddFeedDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::AddFeedDialog)
{
    _ui->setupUi(this);
}

AddFeedDialog::~AddFeedDialog()
{
    delete _ui;
}

QString AddFeedDialog::GetNameLink()
{
    return _ui->nameLineEdit->text();
}

QString AddFeedDialog::GetFeedLink()
{
    return _ui->linkLineEdit->text();
}

void AddFeedDialog::Clear()
{
    _ui->nameLineEdit->clear();
    _ui->linkLineEdit->clear();
}
