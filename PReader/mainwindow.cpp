#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QInputMethodEvent"
#include "QInputEvent"
#include "QFile"
#include "QTextStream"
#include "QIcon"
#include "QDesktopWidget"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    list_words_autow= new QListWidget(ui->textEdit);
    list_words_autow->setStyleSheet("background-color: lightgray");
    list_words_autow->raise();
    list_words_autow->hide();
    file_dialog = new File_Dialog_android(0);
    button_setting = new QPushButton(this);

    QtAndroid::requestPermissionsSync(QStringList()<<"android.permission.WRITE_EXTERNAL_STORAGE"<<"android.permission.READ_EXTERNAL_STORAGE",10);



    //многопоточность
    //соедениения
    connect(thread_a, &QThread::started,autocomplite_thread,&Autocomplite::run);
    //запуск загрузки базы
    connect(this,&MainWindow::load_base_signal,autocomplite_thread,&Autocomplite::loading_base);
    //запуск поиска слова
    connect(this,&MainWindow::start_search_signal,autocomplite_thread,&Autocomplite::start_search);
    //конец поиска
    connect(autocomplite_thread,SIGNAL(finished_search(QStringList,QSize)),this,SLOT(finish_words(QStringList, QSize)));
    //остановка потока поиска для его нового поиска
    connect(autocomplite_thread,&Autocomplite::stop_search,this,&MainWindow::stop_autocomp);


    //соединение автодополнения
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(special_symbols_and_autocomplite()));
    //соединение вставки
    connect (list_words_autow,SIGNAL(itemClicked(QListWidgetItem*)),SLOT(enterword(QListWidgetItem*)));

    //слоты для file_dialog_android
    connect(file_dialog,SIGNAL(close_dialog()),this,SLOT(close_dialog()));
    connect(file_dialog,SIGNAL(open_file(QString)),this,SLOT(load_file_red(QString)));


    //отладка ошибок
    ui->textEdit->setAttribute(Qt::WA_InputMethodEnabled,false);
    autocomplite_thread->moveToThread(thread_a);
    thread_a->start();
    //автозагрузка базы
    //autocomplite_thread->loading_base(":/filebaza.txt");
    emit(load_base_signal("assets:/filebaza.txt"));


    //кнопка настроек и ее стиль
    button_setting->setStyleSheet("border-image: url(\"assets:/Setting.png\")");






    //ui->textEdit->insertPlainText("dsafsdaf\n\rdsafsdf\n\r\n\r\n\rfasfdsaf\n\r\n\r\n\rsfasfdsaf\n\r\n\refdasf\n\r\n\rsfdsafsdafaasrf\n\r fesdfa\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r gsdgsag\n\r\n\r\n\r\n\rdfsadgdsag\n\r\n\r\n\r\n\rfdsags\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\rfdsafsd\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\rdfdsaf\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\rfddsafv\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\rsfasdfads\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\rfdsaf");
    ui->textEdit->verticalScrollBar()->hide();
    ui->textEdit->horizontalScrollBar()->hide();

    //присвоение стандартного формата
    standart_format = ui->textEdit->textCursor().charFormat();



    //сигналы

    connect(&timer2, SIGNAL(timeout()),this,SLOT(timeranimals()));


    //для нажатий отработка времени
    //проверка
    time_system.start();


    //кнопка настроек
    connect(button_setting,SIGNAL(clicked()),SLOT(setting_menu()));
    //настройки
    setting_dialog =new Setting_widget(this);
    setting_dialog->hide();



    //нитки связи с окном настроек


    connect(setting_dialog,&Setting_widget::open_signal,this,&MainWindow::sm_open_file_dialog);
    connect(setting_dialog,&Setting_widget::save_signal,this,&MainWindow::sm_save);
    connect(setting_dialog,&Setting_widget::save_ass_signal,this,&MainWindow::sm_save_ass);
    connect(setting_dialog,&Setting_widget::new_files_signal,this,&MainWindow::sm_new_file);
    connect(setting_dialog,SIGNAL(set_setting_form_signal(bool,int)),this,SLOT(sm_set_setting(bool,int)));

    //виджет сохранения
    save_widget = new Save_ass(this);
    save_widget->hide();

    connect(save_widget,SIGNAL(save_file(QString)),this,SLOT(sa_save_file(QString)));

    setting_load_file();



    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    thread_a->terminate();
    delete ui;
}
//

//
//
//
//

void MainWindow::load_file_base()
{




}
//
//
//
//
//
//
//
//
void MainWindow::heightscroll()
{



    dpi_system_x=qApp->desktop()->physicalDpiX();
    dpi_system_y = qApp->desktop()->physicalDpiY();
    scroll = this->height()/9;


    file_dialog->show_widget_height_size(this->height(),dpi_system_y);

    file_dialog->show();

    file_dialog->setGeometry((this->width()/22),(this->height()/34),(this->width()-(this->width()/11)),(this->height()-(this->height()/17)));
     size_left_button=dpi_system_x*0.12;
     size_width_button = dpi_system_x * 0.43;
     button_setting->setIconSize(QSize(size_width_button-20,size_width_button-20));
     setting_dialog->hide();
     //
     int temp_h_button_setting;
     temp_h_button_setting=dpi_system_y*0.43;
     setting_dialog->set_push_size_h(temp_h_button_setting);




     w_setting_position = dpi_system_x*1.2;

     h_setting_position = temp_h_button_setting*7+9*2+6*9;

     x_setting_position = this->width()-size_left_button-w_setting_position;
     y_setting_position = size_left_button+size_width_button;
     save_widget->hide();
     setting_dialog->hide();
     button_setting->hide();



}

void MainWindow::load_file_red(QString FileName)
{

    load_file = true;
    file_name_red = FileName;
    QFile vfil(FileName);
    if (FileName!="")
    {



        ui->textEdit->clear();
    vfil.open(QIODevice::ReadOnly);
   QTextStream stfile(&vfil);
   QString string;


   while (!stfile.atEnd()) {

    //  ui->textEdit->insertPlainText(stfile.readLine(1));
       string =  stfile.readLine()+"\n\r";
       for(int a = 0;a<string.size();a++)
       {
           ui->textEdit->insertPlainText(string.at(a));
           update();

       }



   }





    vfil.close();
    }
    load_file = false;

}

void MainWindow::timeranimals()
{
    if(y_animaltimer>10)
    {
        //lab->setText(QString::number(y_animaltimer));
        //lab->show();
    int valuetemp = ui->textEdit->verticalScrollBar()->value();
    y_animaltimer = y_animaltimer-20;
    ui->textEdit->verticalScrollBar()->setValue(valuetemp+y_animaltimer/20);
            timer2.stop();
            timer2.setInterval(timer2.interval()/10);
            timer2.start();
}else
    {if(y_animaltimer<-10)
        {
            int valuetemp = ui->textEdit->verticalScrollBar()->value();
            y_animaltimer = y_animaltimer+20;
            ui->textEdit->verticalScrollBar()->setValue(valuetemp+y_animaltimer/20);
                    timer2.stop();
                    timer2.setInterval(timer2.interval()/10);
                    timer2.start();
        }else
        {

        timer2.stop();
        }
    }


}

void MainWindow::special_symbols_and_autocomplite()
{
    setting_dialog->hide();
    list_words_autow->hide();
   // QLabel *lab1 = new QLabel;
   // lab1->setText("words_autocomplite_ssaa");
   // lab1->show();




    QColor color_cursors;
    if(!run_slot_ssaa)
    {
        run_slot_ssaa = true;
        words_autocomplite_ssaa.clear();

        curs_autocomplite_ssaa = ui->textEdit->textCursor();

        curs_autocomplite_ssaa.movePosition(QTextCursor::StartOfWord);
        curs_autocomplite_ssaa.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
        words_autocomplite_ssaa = curs_autocomplite_ssaa.selectedText();
        //lab->setText(words_autocomplite_ssaa);
        //lab->show();
        if(!words_autocomplite_ssaa.isNull())
        {
            if(words_autocomplite_ssaa==">")
            {
                curs_autocomplite_ssaa = ui->textEdit->textCursor();

                curs_autocomplite_ssaa.movePosition(QTextCursor::Left);
                curs_autocomplite_ssaa.movePosition(QTextCursor::StartOfWord);
                curs_autocomplite_ssaa.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
                words_autocomplite_ssaa = curs_autocomplite_ssaa.selectedText();


            }
            if(words_autocomplite_ssaa=="php")
            {
                curs_autocomplite_ssaa.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor,4);




                words_autocomplite_ssaa=curs_autocomplite_ssaa.selectedText();
                if(words_autocomplite_ssaa=="?")
                {
                    curs_autocomplite_ssaa.movePosition(QTextCursor::Right);
                    curs_autocomplite_ssaa.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor,3);






                    curs_autocomplite_ssaa.insertText("php",standart_format);
                   // lab->setText("работает php");
                   // lab->show();




                }
                run_slot_ssaa = false;
                return;

            }


            if(!load_file)
            {
                if(autocomplite)
                {
                if(autocomplite_thread->is_runing())
                {
                    run_slot_ssaa = false;
                    autocomplite_thread->stop();
                    return;
                }else
                {
                emit(start_search_signal(words_autocomplite_ssaa,word_count));
                }
                }
            }

            run_slot_ssaa = false;
            return;
        }

        //на символы
        curs_autocomplite_ssaa = ui->textEdit->textCursor();
        curs_autocomplite_ssaa.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
        words_autocomplite_ssaa = curs_autocomplite_ssaa.selectedText();
        color_cursors = ui->textEdit->textCursor().charFormat().foreground().color();
        if(!words_autocomplite_ssaa.isNull())
        {
            if(words_autocomplite_ssaa == "("&&!load_file)
            {
                curs_autocomplite_ssaa = ui->textEdit->textCursor();
                curs_autocomplite_ssaa.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
                words_autocomplite_ssaa = curs_autocomplite_ssaa.selectedText();
               // lab->setText(") работает");
               // lab->show();
                if(words_autocomplite_ssaa!=")")
                {
                    curs_autocomplite_ssaa.insertText(")");

                    curs_autocomplite_ssaa.movePosition(QTextCursor::Left);
                    ui->textEdit->setTextCursor(curs_autocomplite_ssaa);
                }
                run_slot_ssaa = false;
                return;
            }

            if(words_autocomplite_ssaa=="{"&&!load_file)
            {
                curs_autocomplite_ssaa.insertText("{ \r\n\r\n }");
                curs_autocomplite_ssaa.movePosition(QTextCursor::Left);
                curs_autocomplite_ssaa.movePosition(QTextCursor::Up);
                ui->textEdit->setTextCursor(curs_autocomplite_ssaa);
                run_slot_ssaa = false;
                return;

            }

            if(words_autocomplite_ssaa==">"&&color_cursors==QColor(37,72,177,255))
            {
                ui->textEdit->setTextColor(Qt::black);
                run_slot_ssaa = false;
                return;
            }
            if(words_autocomplite_ssaa=="<")
            {
                if(color_cursors ==QColor(37,72,177,255))
                {
                    run_slot_ssaa = false;
                    return;

                }else
                {
                    QTextCharFormat fmt;
                    fmt.setForeground(QBrush(QColor(37,72,177,255)));
                    if(load_file)
                    {
                        curs_autocomplite_ssaa.insertText("<",fmt);

                    }else
                    {
                        curs_autocomplite_ssaa.insertText("<>",fmt);
                        curs_autocomplite_ssaa.movePosition(QTextCursor::Left);
                        ui->textEdit->setTextCursor(curs_autocomplite_ssaa);

                    }

                }
                run_slot_ssaa = false;
                return;
            }
            if(words_autocomplite_ssaa == "/")
            {
                curs_autocomplite_ssaa = ui->textEdit->textCursor();

                curs_autocomplite_ssaa.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor,2);


                words_autocomplite_ssaa = curs_autocomplite_ssaa.selectedText();

                if(words_autocomplite_ssaa == "//")
                {
                    QTextCharFormat fmt;
                    fmt.setForeground(QBrush(Qt::green));
                    curs_autocomplite_ssaa = ui->textEdit->textCursor();
                    curs_autocomplite_ssaa.movePosition(QTextCursor::Left);
                    curs_autocomplite_ssaa.movePosition(QTextCursor::Left);
                    curs_autocomplite_ssaa.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
                    curs_autocomplite_ssaa.setCharFormat(fmt);
                }
                run_slot_ssaa = false;
                return;

            }

        }


        run_slot_ssaa = false;
    }





}

void MainWindow::finish_words(QStringList list, QSize size_autcomplite)
{
    list_words_autow->clear();
list_words_autow->addItems(list);
QRect rect_temp = QRect(ui->textEdit->cursorRect().bottomLeft(),size_autcomplite);
list_words_autow->setGeometry(rect_temp);
list_words_autow->show();




}

void MainWindow::stop_autocomp()
{
    if(!run_slot_ssaa)
    {
        emit(start_search_signal(words_autocomplite_ssaa,word_count));

    }
}

void MainWindow::enterword(QListWidgetItem *item)
{
    QString wordinsert;

    wordinsert = item->text();
    //qApp->inputMethod()->commit();
  //  QApplication* application = static_cast<QApplication *>(QApplication::instance());












        QTextCharFormat fmt;
        fmt.setForeground(QBrush(item->textColor()));
       // curs_autocomplite_ssaa = ui->textEdit->textCursor();
       // curs_autocomplite_ssaa.movePosition(QTextCursor::StartOfWord);
       // curs_autocomplite_ssaa.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

       // QString string;
      //  string = curs_autocomplite_ssaa.selectedText();
    //   curs_autocomplite_ssaa.insertText(wordinsert);
       // ui->textEdit->insertPlainText(wordinsert);
        //ui->textEdit->setTextCursor(curs_autocomplite_ssaa);
        ui->textEdit->insertPlainText(wordinsert);
        ui->textEdit->setFocus();



     //  curs_autocomplite_ssaa = ui->textEdit->textCursor();
     //  QString words_temp = ui->textEdit->toPlainText();
     //  ui->textEdit->clear();
     //  ui->textEdit->insertPlainText(words_temp);

      // ui->textEdit->setTextCursor(curs_autocomplite_ssaa);





}

void MainWindow::close_dialog()
{

    button_setting->show();
    button_setting->setGeometry((this->width()-size_left_button-size_width_button),size_left_button,size_width_button,size_width_button);

}

void MainWindow::setting_menu()
{
    if(setting_dialog->isHidden())
    {
    setting_dialog->show();
    setting_dialog->setGeometry(x_setting_position,y_setting_position,w_setting_position,h_setting_position);
    }else
    {
        setting_dialog->hide();
    }
}

void MainWindow::sm_open_file_dialog()
{
    file_dialog->show_widget_height_size(this->height(),dpi_system_y);
    file_dialog->show();

    file_dialog->setGeometry((this->width()/22),(this->height()/34),(this->width()-(this->width()/11)),(this->height()-(this->height()/17)));
}

void MainWindow::sm_save()
{
    if(file_name_red.isNull()){
        save_widget->show_widget_height_size(dpi_system_y);
        save_widget->show();

        save_widget->setGeometry((this->width()/22),(this->height()/34),(this->width()-(this->width()/11)),(this->height()-(this->height()/17)));
        save_widget->setFocus();
    }else
    {
        write_file(file_name_red);
    }
}

void MainWindow::sm_save_ass()
{
    save_widget->show_widget_height_size(dpi_system_y);
    save_widget->show();

    save_widget->setGeometry((this->width()/22),(this->height()/34),(this->width()-(this->width()/11)),(this->height()-(this->height()/17)));
    save_widget->setFocus();
}

void MainWindow::sa_save_file(QString file_save)
{
    write_file(file_save);
    save_widget->hide();

}

void MainWindow::sm_new_file()
{
    ui->textEdit->clear();
    file_name_red="";
    file_name_red.clear();
}

void MainWindow::sm_set_setting(bool autow, int word_count_f)
{
    autocomplite = autow;
    word_count=word_count_f;
}

void MainWindow::write_file(QString file_name_write_wf)
{
    QFile file_write(file_name_write_wf);
    if(file_write.open(QIODevice::WriteOnly)){
    QTextStream strem_write_file(&file_write);
    strem_write_file <<ui->textEdit->toPlainText();
    }
    file_write.close();

}

void MainWindow::setting_load_file()
{
    QFile file_read("setting.ini");
    if(file_read.open(QIODevice::ReadOnly))
    {
        QTextStream strem_write_file(&file_read);
        while (!strem_write_file.atEnd())
        {
            QString temp_setting;
            temp_setting=strem_write_file.readLine();
            if(temp_setting.size()>12)
            {
                if(temp_setting.left(12)=="Autocomplite")
                {
                    if(temp_setting.right(1)=="1")
                    {
                        autocomplite=true;
                        continue;

                    }else
                    {
                        if(temp_setting.right(1)=="0")
                        {
                            autocomplite=false;
                            continue;

                        }
                    }

                }

            }
                if(temp_setting.size()>11)

                {
                    QString temp = temp_setting.left(11);
                    if(temp==" Word_count")
                    {
                        QString temp_word_count =temp_setting.right(1);
                        word_count=temp_word_count.toInt();
                    }
                }
            }



    }else
    {
        file_read.open(QIODevice::WriteOnly);
        QTextStream strem_write_file(&file_read);
        strem_write_file<<"Autocomplite: 1\n\r Word_count: 3";
        autocomplite = true;
        word_count=3;
        file_read.close();
    }
    setting_dialog->set_setting(autocomplite,word_count);

}






//события


bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(load_file)
    {
        return false;
    }

    if(!file_dialog->isHidden())
    {
        return false;
    }

if(!save_widget->isHidden())
{
    return false;
}





    //if(watched->isWidgetType())

    if (event->type()==QEvent::KeyPress)
    {

   QKeyEvent *keyevent=static_cast<QKeyEvent*>(event);
   int key_push = keyevent->key();
   key_push= keyevent->key();
   if(keyevent->key()==Qt::Key_F5)
   {



        return false;
   }
   //
   if(key_push == 16777219)
   {
int b=0;

   }
   //enter(return  по факту для linux и android
   if(key_push == 16777220)
   {

if(ui->textEdit->textCursor().charFormat().foreground().color()==Qt::green)
{
    curs_autocomplite_ssaa=ui->textEdit->textCursor();
    curs_autocomplite_ssaa.insertText("\r\n",standart_format);
    ui->textEdit->setFocus();
    return true;
}


   }






    }
    if(event->type() == QEvent::InputMethod)
    {
        QInputMethodEvent *inpudevent = static_cast<QInputMethodEvent*>(event);
        QString temp;

        temp = inpudevent->preeditString();





        if(!temp.size()==0)

            {
            if(autocomplite)
            {

                emit(start_search_signal(temp,word_count));
            }
            setting_dialog->hide();


                return false;
            }





        return false;








    }
    QMouseEvent *keymouse=static_cast<QMouseEvent*>(event);


    if(event->type()==QEvent::MouseButtonPress)
    {
        time_system.restart();




       // timer1.stop();
       // timer1.start();
        time_int_delay=time_system.msec();
        PressMouse = true;
        mousepos_y = keymouse->pos().y();


        if(timer2.isActive()==true)
        {


            timer2.stop();
            return true;
        }

        return  false;

        }

    if(event->type()==QEvent::MouseMove)
    {
        if(PressMouse==true)
        {


            pos1_y=mousepos_y - keymouse->pos().y();
            if(pos1_y > scroll || pos1_y < -scroll)
            {
                if(pos1_y > scroll)
                {
                button_setting->hide();
                setting_dialog->hide();
                }
                int valuetemp = ui->textEdit->verticalScrollBar()->value();



                ui->textEdit->verticalScrollBar()->setValue(valuetemp+pos1_y/(scroll/3));
               // if(timer2.isActive()==false)
               // {
                //    timer1.setInterval(0);
               // timer1.setInterval(1000);
               // timer1.start(950);
               // }

                //lab->setText(QString::number(pos1_y)+"\n\r scrol="+QString::number(scroll)+"/"+QString::number(valuetemp)+"\n\r height"+QString::number(ui->textEdit->height()));
               // lab->show();
                return true;
            }
            return true;
        }
        }

        if(event->type()==QEvent::MouseButtonRelease)
        {


            lab->hide();
            //int tempint = timer1.remainingTime();
            int tempint = time_system.restart();
            y_animaltimer = pos1_y;
            //timer1.deleteLater();


           // timer1.start(0);
            if(tempint>70&tempint<300)
            {
                if(pos1_y > scroll || pos1_y < -scroll)
                {
                 timer2.setInterval(300-tempint);
                 timer2.start();
                 PressMouse = false;
                 button_setting->hide();
                 if(pos1_y<-scroll )
                 {

                     button_setting->show();
                     button_setting->setGeometry((this->width()-size_left_button-size_width_button),size_left_button,size_width_button,size_width_button);

                 }
                 return true;
                }


            }

            button_setting->show();
            button_setting->setGeometry((this->width()-size_left_button-size_width_button),size_left_button,size_width_button,size_width_button);

            PressMouse = false;
            return false;
        }



return false;
}
