#include "save_ass.h"
#include "ui_save_ass.h"
#include "QChar"

Save_ass::Save_ass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Save_ass)
{
    ui->setupUi(this);



    connect(ui->pushButton,SIGNAL(pressed()),this,SLOT(Push_button_action()));
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(clicked_action_widgetlist(QListWidgetItem*)));
    connect(ui->pushButton_2,SIGNAL(pressed()),this,SLOT(save_file()));
    ui->comboBox->addItems(QStringList()<<".txt"<<".php"<<".html");
}

void Save_ass::show_widget_height_size(int dpi_y)
{
    height_push_size = dpi_y*0.34;
    open_dir(pos_dir);
}

Save_ass::~Save_ass()
{
    delete ui;
}

void Save_ass::open_dir(QString pos_dir)
{
    ui->listWidget->clear();
    QDir dir(pos_dir);
    dir_list_info = dir.entryInfoList();
    for (int i = 0;i<dir_list_info.size();++i)
    {
        QFileIconProvider prov_file_icon;

        ui->listWidget->addItem(dir_list_info.at(i).fileName());
        ui->listWidget->setIconSize(QSize(height_push_size/2,height_push_size/2));
        ui->listWidget->item(i)->setIcon(prov_file_icon.icon(dir_list_info.at(i)));
        ui->listWidget->item(i)->setSizeHint(QSize(0,height_push_size));

    }
    ui->pushButton->setMinimumHeight(height_push_size);
    ui->pushButton->setMaximumHeight(height_push_size);
    ui->pushButton_2->setMinimumHeight(height_push_size);
    ui->pushButton_2->setMaximumHeight(height_push_size);

    ui->listWidget->show();
}

void Save_ass::Push_button_action()
{
    if(pos_dir!=(QDir::rootPath()+"sdcard"))
    {
        ui->listWidget->clear();
        for(int temp_a=pos_dir.size();temp_a>0;--temp_a)
        {
           if( pos_dir[temp_a]=="/")
           {

                   pos_dir = pos_dir.left(temp_a);
                   open_dir(pos_dir);
                   break;

        }
        }

    }else
    {

ui->listWidget->clear();
emit close_dialog();
    close();
    }
}

void Save_ass::clicked_action_widgetlist(QListWidgetItem *item_list_widget)
{
    QFileInfo file_info(pos_dir+"/"+item_list_widget->text());
    bool temp=file_info.isDir();
    if(file_info.isDir())
    {
        pos_dir=pos_dir+"/"+item_list_widget->text();
        open_dir(pos_dir);
    }else
    {
        if(file_info.isFile())
        {
            QString temp_file_fotmat= item_list_widget->text();
            QString temp_file_name_n;
            for(int temp_a=temp_file_fotmat.size();temp_a>0;--temp_a)
            {

               if( temp_file_fotmat[temp_a]==".")
               {
                   temp_file_name_n=temp_file_fotmat.left(temp_a);

                       temp_file_fotmat = temp_file_fotmat.right(temp_file_fotmat.size() - temp_a);

                       break;


            }

        }

            QString temp_file_name;
            temp_file_name=pos_dir+"/"+item_list_widget->text();
            int a =0;
           if(temp_file_fotmat==".txt"||temp_file_fotmat==".php"||temp_file_fotmat==".html"||temp_file_fotmat==".xml"||temp_file_fotmat=="xml"||temp_file_fotmat=="html"||temp_file_fotmat=="php"||temp_file_fotmat=="txt")
           {

               ui->lineEdit->setText(temp_file_name_n);
           }

    }
    }

}

void Save_ass::chanel_dialog()
{

}

void Save_ass::save_file()
{
if(!ui->lineEdit->text().isNull())
{


    QString temp_file_name;
    temp_file_name=pos_dir+"/"+ui->lineEdit->text()+ui->comboBox->currentText();


       emit(save_file(temp_file_name));

}
}


