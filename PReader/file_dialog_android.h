#ifndef FILE_DIALOG_ANDROID_H
#define FILE_DIALOG_ANDROID_H

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
class File_Dialog_android;
}

class File_Dialog_android : public QWidget
{
    Q_OBJECT

public:
    explicit File_Dialog_android(QWidget *parent = 0);
    ~File_Dialog_android();
    void show_widget_height_size(int height_size, int dpi_y);


private:
    Ui::File_Dialog_android *ui;
    QListWidget *widget_list = new QListWidget;
    QString pos_dir = QDir::rootPath()+"sdcard";
    QFileInfoList dir_list_info;

    int height_push_size;
    void open_dir(QString pos_dir);


private slots:

    void Push_button_action();
    void clicked_action_widgetlist(QListWidgetItem *item_list_widget);
    void chanel_dialog();
    void clicked_push_new_file();
signals:
    void open_file(QString file);
    void close_dialog();
};

#endif // FILE_DIALOG_ANDROID_H
