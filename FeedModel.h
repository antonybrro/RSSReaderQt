#include <QStandardItemModel>

class FeedModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit FeedModel(QObject *parent = 0);
    ~FeedModel();

    void AddItem(QPair<QString, QString> item);
    void CreateHeader();

};
