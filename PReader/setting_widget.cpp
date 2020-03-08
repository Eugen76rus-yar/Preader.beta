#include "setting_widget.h"
#include "ui_setting_widget.h"
#include "QAbstractSpinBox"
#include "QFile"
#include "QTextStream"

Setting_widget::Setting_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting_widget)
{
    ui->setupUi(this);
    connect(ui->pushButton_3,SIGNAL(pressed()),SLOT(open()));
    connect(ui->pushButton,SIGNAL(pressed()),SLOT(save()));
    connect(ui->pushButton_2,SIGNAL(pressed()),SLOT(save_ass()));
    connect(ui->pushButton_4,SIGNAL(pressed()),SLOT(new_files()));

    ui->spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    qApp->installEventFilter(this);
}

Setting_widget::~Setting_widget()
{
    delete ui;
}

void Setting_widget::set_push_size_h(int h)
{
    ui->pushButton->setMinimumHeight(h);
    ui->pushButton_2->setMinimumHeight(h);
    ui->pushButton_3->setMinimumHeight(h);
    ui->pushButton_4->setMinimumHeight(h);
    ui->label->setMinimumHeight(h);
    ui->label_2->setMinimumHeight(h);
    ui->label_3->setMinimumHeight(h);
    ui->spinBox->setMinimumHeight(h);
    ui->spinBox->setMinimumHeight(h);
}

void Setting_widget::set_setting(bool autow, int words_count)
{
    if(autow)
    {
        ui->checkBox->setCheckState(Qt::Checked);
    }else
    {
        ui->checkBox->setCheckState(Qt::Unchecked);
    }
    ui->spinBox->setValue(words_count);
}

void Setting_widget::open()
{
    emit(open_signal());
    hide();
}

void Setting_widget::save()
{
    emit(save_signal());
    hide();
}

void Setting_widget::save_ass()
{
    emit(save_ass_signal());
    hide();
}

void Setting_widget::new_files()
{
    emit(new_files_signal());
    hide();
}

bool Setting_widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->label_2)
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
            if(ui->checkBox->checkState()==Qt::Checked)
            {
                ui->checkBox->setCheckState(Qt::Unchecked);
                return true;
            }else
            {
                ui->checkBox->setCheckState(Qt::Checked);
                return true;
            }
        }
    }
    if(watched==this)
    {
    if(event->type()==QEvent::Hide)
    {
        QFile file_read("setting.ini");
        file_read.open(QIODevice::WriteOnly);
        QTextStream strem_write_file(&file_read);
        QString Autocomplite;
        bool Autocomplite_bool;

        int Word_count;
        if(ui->checkBox->checkState()==Qt::Checked)
        {
            Autocomplite="1";
            Autocomplite_bool=true;
        }else
        {
            Autocomplite="0";
            Autocomplite_bool=false;
        }
        QString temp_write;
        Word_count=ui->spinBox->value();
        temp_write="Autocomplite: "+Autocomplite+"\n Word_count: "+QString::number(Word_count);

        strem_write_file<<temp_write;

        emit(set_setting_form_signal(Autocomplite_bool,Word_count));
        file_read.close();
    }
    }
    return false;
}
