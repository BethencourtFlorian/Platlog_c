#ifndef CONNEXIONPAGE_H
#define CONNEXIONPAGE_H

#include <QDialog>

namespace Ui {
class ConnexionPage;
}

class ConnexionPage : public QDialog
{
    Q_OBJECT

public:
    explicit ConnexionPage(QWidget *parent = nullptr);
    ~ConnexionPage();
    int onClick(void);

private:
    Ui::ConnexionPage *ui;
};

#endif // CONNEXIONPAGE_H
