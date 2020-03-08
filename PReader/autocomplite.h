#ifndef AUTOCOMPLITE_H
#define AUTOCOMPLITE_H
#include "QObject"
#include "QString"
#include "QStringList"
#include "QMap"
#include "QSize"


class Autocomplite:public QObject
{
    Q_OBJECT
private:
    //база слов для быстрого доступа
    QMap <QString,QStringList> hash_word;
    //количество найденых слов
    int found_numb_words;



public:
     explicit Autocomplite(QObject *parent = 0);
    ~Autocomplite();

//основные для работы
    bool a_runing = false;
    bool a_run=false;

    bool is_runing() const;
    bool is_run() const;

    //отладка ошибок
    QString words_error = "нет";
    QString words_error_traking();
    //временый !!!!!!!удалить
    QString words_proverka();







    QString proverka() const;
signals:
void finished_search(QStringList list,QSize size_polog);
void stop_search();



public slots:
    void run();
    void stop();
    //загрузка базы слов
     void loading_base(QString file);
     //поиск автодополнение, т.е. слов
     void start_search(QString word,int number_words);

};

#endif // AUTOCOMPLITE_H
