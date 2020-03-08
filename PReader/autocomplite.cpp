#include "autocomplite.h"
#include "QFile"
#include "QTextStream"
#include "QRegExp"

Autocomplite::Autocomplite(QObject *parent):QObject(parent)
{

}

Autocomplite::~Autocomplite()
{

}


bool Autocomplite::is_runing() const//проверка работы
{
    return a_runing;
}

bool Autocomplite::is_run() const
{
    return a_run;
}

QString Autocomplite::words_error_traking()
{
    return words_error;
}

QString Autocomplite::words_proverka()
{
    QMap <QString,QStringList>::Iterator itv=hash_word.find("б");
    QStringList temp_QList;
    if(hash_word.contains("б")&&!itv.value().isEmpty())
    {
        temp_QList = itv.value();
        return temp_QList[2];
    }else
    {
        return "ошибка";
    }



}

void Autocomplite::loading_base(QString file)
{
    QStringList temp_qlist;
    QFile loading_file_base(file);

    if(loading_file_base.open(QIODevice::ReadOnly))
    {
    QTextStream load_qts(&loading_file_base);
    while(!load_qts.atEnd())
    {
        QString temp_cash;
        temp_cash=load_qts.readLine();
        if(temp_cash.isEmpty())
        {
            continue;
        }
        if(temp_cash.contains("-"))
        {
            continue;
        }
        temp_qlist << temp_cash;
    }
    loading_file_base.close();
    //

    QString letter_sort;

    temp_qlist.sort();
letter_sort=temp_qlist[0].left(1);
    QStringList vremlist;
    for (int a=0;a<(temp_qlist.size());a++)
    {
        QString letter_temp;
        QString slovo;
        letter_temp=temp_qlist[a];
        slovo = letter_temp;
        letter_temp=letter_temp.left(1);
        if(a==0)
        {


        }

        if (letter_sort==letter_temp)
        {

            vremlist.append(slovo);

        }
        else
        {
            hash_word.insert(letter_sort, vremlist);
           letter_sort = letter_temp;

            vremlist.clear();
        }

    }
   return;
    }else
    {
        words_error = "не загружен фаил";
        return;
    }

}

void Autocomplite::start_search(QString word, int number_words)
{

    a_runing = true;
    found_numb_words=0;
    QStringList temp_words;
    QStringList words_return;
    QString letter = word.left(1);
    if(!a_runing)
    {
        return;
    }
    if(!hash_word.contains(letter))
    {
        return;
    }
    QMap <QString,QStringList>::Iterator itv=hash_word.find(letter);
    if(!a_runing)
    {
        return;
    }
    if(!itv.value().isEmpty())
    {
        temp_words = itv.value();
    }else
    {
        a_runing = false;
        return;
    }
    int start_search_int=0;
    if(!a_runing)
    {
        return;
    }
    for (int a = 0;a<number_words;a++)
    {
        if(!a_runing)
        {

            break;
            return;
        }
        if(temp_words.indexOf(QRegExp("^"+word+".+"),start_search_int)==-1)
        {
            break;
        }else
        {
            start_search_int = temp_words.indexOf(QRegExp("^"+word+".+"),start_search_int);
            words_return.append(temp_words[start_search_int]);
            start_search_int = start_search_int+1;


        }
    }
    if(!a_runing)
    {
        return;
    }
    if(words_return.size()>0)
    {
        int length=100;
        length=length + (words_return[1].size())*30;
        if(!a_runing)
        {
            return;
        }
        int height;
        height=words_return.size()*60;
        QSize size_autocom(length,height);
        emit(finished_search(words_return,size_autocom));






    }
    a_runing = false;
}

QString Autocomplite::proverka() const
{

}



void Autocomplite::run()//запуск потока
{
    a_run=true;
}

void Autocomplite::stop()
{
    a_runing = false;
}
