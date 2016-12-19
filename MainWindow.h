#include <QMainWindow>

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

#include "AddFeedDialog.h"
#include "FeedModel.h"
#include "RssModel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotReadyRead();

    void on_feedTableView_clicked(const QModelIndex &index);

    void on_addBtn_clicked();

    void on_rssTableView_clicked(const QModelIndex &index);

    void on_removeBtn_clicked();

    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);

private:
    void OnActionAdd();
    void OnActionRemove();
    void OnActionQuit();
    void OnActionAbout();

private:
    Ui::MainWindow *_ui;

    FeedModel *_model;
    RssModel *_rssModel;
    QNetworkAccessManager *_manager;
    QNetworkReply *_reply;
    AddFeedDialog *_addDialog;
};
