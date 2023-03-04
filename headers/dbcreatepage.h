#ifndef DBCREATEPAGE_H
#define DBCREATEPAGE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QGroupBox>

namespace Ui {
class DBCreatePage;
}

class DBCreatePage : public QDialog
{
    Q_OBJECT

public:
    explicit DBCreatePage(QWidget *parent = nullptr);
    ~DBCreatePage();

private slots:
    void on_input_COLNUM_valueChanged(int colnum);

private:
    Ui::DBCreatePage *ui;
};

#endif // DBCREATEPAGE_H
