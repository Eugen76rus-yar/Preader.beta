#ifndef SETTING_WIDGET_H
#define SETTING_WIDGET_H

#include <QWidget>

namespace Ui {
class Setting_widget;
}

class Setting_widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting_widget(QWidget *parent = nullptr);
    ~Setting_widget();
    void set_push_size_h(int h);
    void set_setting(bool autow,int words_count);


private slots:
    void open();
    void save();
    void save_ass();
    void new_files();
signals:
    void open_signal();
    void save_signal();
    void save_ass_signal();
    void new_files_signal();
    void set_setting_form_signal(bool autow,int words_count);

private:
    Ui::Setting_widget *ui;

protected:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // SETTING_WIDGET_H
