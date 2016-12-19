#include <QStandardItemModel>

class RssModel : public QStandardItemModel
{
public:
    explicit RssModel(QObject *parent = 0);
    ~RssModel();

    void AddItem(QPair<QString, QString> item);
};
