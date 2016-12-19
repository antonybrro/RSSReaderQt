#include <QDialog>

namespace Ui {
    class AddFeedDialog;
}

class AddFeedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFeedDialog(QWidget *parent = 0);
    ~AddFeedDialog();

    QString GetNameLink();
    QString GetFeedLink();
    void Clear();

private:
    Ui::AddFeedDialog *_ui;
};
