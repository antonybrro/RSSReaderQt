#include "RssModel.h"

#include <QDebug>

RssModel::RssModel(QObject *parent) :
    QStandardItemModel(parent)
{

}

RssModel::~RssModel()
{

}

void RssModel::AddItem(QPair<QString, QString> item)
{
    qDebug() << item.first << item.second;
    QStandardItem *name = new QStandardItem(item.first);
    name->setData(item.second);

    appendRow(name);
}
