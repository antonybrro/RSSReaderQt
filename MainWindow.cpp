#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTextCodec>

#include <QDebug>
#include "JsonParser.h"
#include <QXmlStreamReader>
#include <QDesktopServices>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _model = new FeedModel(this);
    _model->CreateHeader();
    _rssModel = new RssModel(this);
    _addDialog = new AddFeedDialog(this);

    _ui->feedTableView->setModel(_model);
    _ui->feedTableView->setEditTriggers(QTableView::NoEditTriggers);
    _ui->feedTableView->verticalHeader()->hide();
    _ui->feedTableView->horizontalHeader()->setStretchLastSection(true);
    _ui->feedTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    _ui->rssTableView->setModel(_rssModel);
    _ui->rssTableView->setEditTriggers(QTableView::NoEditTriggers);
    _ui->rssTableView->horizontalHeader()->hide();
    _ui->rssTableView->horizontalHeader()->setStretchLastSection(true);

    _ui->removeBtn->setEnabled(false);
    _ui->rssTableView->setVisible(false);
    _ui->actionRemove_feed->setEnabled(_ui->removeBtn->isEnabled());

    _manager = new QNetworkAccessManager(this);

    JsonParser::load("model.txt", _model);

    connect(_ui->actionAdd_feed, &QAction::triggered,
            this, &MainWindow::OnActionAdd);
    connect(_ui->actionRemove_feed, &QAction::triggered,
            this, &MainWindow::OnActionRemove);
    connect(_ui->actionQuit, &QAction::triggered,
            this, &MainWindow::OnActionQuit);
    connect(_ui->actionAbout_software, &QAction::triggered,
            this, &MainWindow::OnActionAbout);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_addBtn_clicked()
{
    if (_addDialog->exec() == QDialog::Accepted)
    {
        _model->AddItem(QPair<QString, QString>(_addDialog->GetNameLink(),_addDialog->GetFeedLink()));
    }

    _addDialog->Clear();

    JsonParser::save("model.txt", _model);
}

void MainWindow::on_feedTableView_clicked(const QModelIndex &index)
{
    _rssModel->clear();
    QNetworkRequest request;
    request.setUrl(QUrl(_model->item(index.row(), 1)->data().toString()));
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    _reply = _manager->get(request);
    connect(_reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));

    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));

//    connect(_reply, SIGNAL(sslErrors(QList<QSslError>)),
//            this, SLOT(slotSslErrors(QList<QSslError>)));

    if (index.isValid())
    {
        _ui->removeBtn->setEnabled(true);
        _ui->actionRemove_feed->setEnabled(_ui->removeBtn->isEnabled());
        _ui->rssTableView->setVisible(true);
        _ui->chooseLabel->setVisible(false);
    }
}

void MainWindow::slotReadyRead()
{
    QByteArray content= _reply->readAll();

    QXmlStreamReader xmlstream;
    xmlstream.addData(content);

    QString titleStr;
    QString linkStr;
    QString currentTag;

    while (!xmlstream.atEnd())
    {
        xmlstream.readNext();
        if(xmlstream.isStartElement())
        {
            if(xmlstream.name() == "item")
            {
                if(titleStr != "")
                {
//                    _rssModel->AddItem(QPair<QString, QString>(titleStr, linkStr));
                }
                titleStr.clear();
                linkStr.clear();
            }
            currentTag = xmlstream.name().toString();
        }
        else if(xmlstream.isEndElement())
        {
            if(xmlstream.name() == "item")
            {
                _rssModel->AddItem(QPair<QString, QString>(titleStr, linkStr));

                titleStr.clear();
                linkStr.clear();
            }
        }
        else if(xmlstream.isCharacters() && !xmlstream.isWhitespace())
        {
            if (currentTag == "title")
                titleStr += xmlstream.text().toString();
            else if (currentTag == "link")
                linkStr += xmlstream.text().toString();
        }
    }
}

void MainWindow::on_rssTableView_clicked(const QModelIndex &index)
{
    QDesktopServices::openUrl(QUrl(_rssModel->data(index, Qt::UserRole + 1).toString()));
}

void MainWindow::on_removeBtn_clicked()
{
    _model->removeRow(_ui->feedTableView->currentIndex().row());

    JsonParser::save("model.txt", _model);

    _ui->removeBtn->setEnabled(_model->rowCount() != 0);
    _ui->actionRemove_feed->setEnabled(_ui->removeBtn->isEnabled());
    _ui->rssTableView->setVisible(_model->rowCount() != 0);
    _ui->chooseLabel->setVisible(_model->rowCount() == 0);
}

void MainWindow::slotError(QNetworkReply::NetworkError err)
{
    Q_UNUSED(err)
    QMessageBox::about(this, tr("Ошибка"), tr("Нет связи с сервером"));
}

void MainWindow::slotSslErrors(QList<QSslError> err)
{
    Q_UNUSED(err)
    QMessageBox::about(this, tr("Ошибка"), tr("Невозможно получить RSS,\nнет связи с сервером"));
}
void MainWindow::OnActionAdd()
{
    on_addBtn_clicked();
}

void MainWindow::OnActionRemove()
{
    on_removeBtn_clicked();
}

void MainWindow::OnActionQuit()
{
    QApplication::quit();
}

void MainWindow::OnActionAbout()
{
    QMessageBox::about(this, tr("О Программе"), tr("Эта программа создана в рамках \n"
                                                "курсового проекта, и предоставляет полный функционал \n"
                                                "для чтения RSS лент новостей"));
}
