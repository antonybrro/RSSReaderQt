#include "FeedModel.h"

FeedModel::FeedModel(QObject *parent) :
    QStandardItemModel(parent)
{
}

FeedModel::~FeedModel()
{
}

void FeedModel::AddItem(QPair<QString, QString> item)
{
    QStandardItem *nameItem = new QStandardItem(item.first);
    nameItem->setData(item.first);

    QStandardItem *linkItem = new QStandardItem(item.second);
    linkItem->setData(item.second);

    QList<QStandardItem*> list;
    list << nameItem << linkItem;

    appendRow(list);
}

void FeedModel::CreateHeader()
{
    setHorizontalHeaderItem(0, new QStandardItem("Name"));
    setHorizontalHeaderItem(1, new QStandardItem("Link"));
}
