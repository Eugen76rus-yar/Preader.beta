#ifndef SAVE_ASS_H
#define SAVE_ASS_H

#include <QWidget>
#include <QDir>
#include <QListWidget>
#include <QFileInfoList>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QPushButton>
#include <QSize>
#include <QFileIconProvider>
#include "QLineEdit"

namespace Ui {
class Save_ass;
}

class Save_ass : public QWidget
{
    Q_OBJECT

public:
    explicit Save_ass(QWidget *parent = 0);
    void show_widget_height_size(int dpi_y);
    ~Save_ass();

private:
    Ui::Save_ass *ui;
    QListWidget *widget_list = new QListWidget;
    QString pos_dir = QDir::rootPath()+"sdcard";
    QFileInfoList dir_list_info;

    int height_push_size;
    void open_dir(QString pos_dir);
private slots:
    void Push_button_action();
    void clicked_action_widgetlist(QListWidgetItem *item_list_widget);
    void chanel_dialog();
    void save_file();
signals:
    void save_file(QString file);
    void close_dialog();

};

#endif // SAVE_ASS_H
