#ifndef LOADING_L_H
#define LOADING_L_H

#include <QWidget>

namespace Ui {
class Loading_l;
}

class Loading_l : public QWidget
{
    Q_OBJECT

public:
    explicit Loading_l(QWidget *parent = nullptr);
    ~Loading_l();

private:
    Ui::Loading_l *ui;
};

#endif // LOADING_L_H
