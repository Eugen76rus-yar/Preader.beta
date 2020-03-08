#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTextEdit"
#include "QScrollBar"
#include "QEvent"
#include "QKeyEvent"
#include "QMouseEvent"
#include "QPoint"
#include "QLabel"
#include "QTimer"
#include "QThread"
#include "autocomplite.h"
#include "QTextCursor"
#include "QColor"
#include "QTextCharFormat"
#include "QSize"
#include "QListWidget"
#include "QRect"
#include "file_dialog_android.h"
#include "QPushButton"
#include "QTime"
#include "setting_widget.h"
#include "save_ass.h"
#include <QtAndroidExtras/QtAndroidExtras>
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int mousepos_y;
    QLabel *lab= new QLabel;
    int scroll;
    bool PressMouse = false;//отслеживание мыши
    int pos1_y;//для аниации скролинга, разница пролистывания
    int y_animaltimer; //у для анимации прокрутки
    int word_count = 3;
    bool autocomplite = true;


     //отслеживание длительности нажатия
    QTimer timer1;
    QTime time_system;
    int time_int_delay;


    QTimer timer2;//для анимации

    //автодополнение инициализация
    QThread *thread_a = new QThread;
    Autocomplite *autocomplite_thread = new Autocomplite;

    File_Dialog_android *file_dialog;


    //загрузка базы
    void load_file_base();
    //для анимации получение размера экрана
    void heightscroll();
    //название файла загрузки
    QString file_name_red;


    //для правильной загрузки
    bool load_file = false;

    //для отсеивания ошибок по сигналу для автодополнения
    bool run_slot_ssaa = false;

    //обьект автодополнения
    QListWidget *list_words_autow;


    //адаптация для андройда
    bool word_input;

    QTimer timerinputmethodsort;


    //слово для проверки
    QString words_autocomplite_ssaa;
    //курсор для автодополнения
    QTextCursor curs_autocomplite_ssaa;
    //сохранение формата текста
    QTextCharFormat standart_format;

    //кнопка

    QPushButton *button_setting;
    int size_left_button;
    int size_width_button;
    //настройки
    Setting_widget *setting_dialog;
    int x_setting_position;
    int y_setting_position;
    int w_setting_position;
    int h_setting_position;

    //dpi
    int dpi_system_y;
    int dpi_system_x;

    //сохранение
    Save_ass *save_widget;

    //функция записи
    void write_file(QString file_name_write_wf);
    //загрузка настроек
    void setting_load_file();









public slots:
    //анимации через таймер
    void timeranimals();
    //загрузка файла
    void load_file_red(QString FileName);

    //автодополнение спец символов
    void special_symbols_and_autocomplite();

   //получение сиглана конца поиска слов
    void finish_words(QStringList list,QSize size_autcomplite);
    //для перезапуска поиска
    void stop_autocomp();
    //слот ввода слова после выбора
    void enterword(QListWidgetItem *item);
    //установка фокуса на ui->textedit
    void close_dialog();
    //меню настроек
    void setting_menu();
    //
    //нитки с setting_menu
    //
    void sm_open_file_dialog();
    void sm_save();
    void sm_save_ass();
    void sa_save_file(QString file_save);
    void sm_new_file();
    //получение настроек
    void sm_set_setting(bool autow, int word_count_f);


signals:
    void start_search_signal(QString word,int size_polog);
    void load_base_signal(QString load_file_name);


protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:

    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
