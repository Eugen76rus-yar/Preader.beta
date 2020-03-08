#include "file_dialog_android.h"
#include "ui_file_dialog_android.h"
#include "QLineEdit"
#include "QListView"
#include "QFile"
#include "QLabel"

File_Dialog_android::File_Dialog_android(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File_Dialog_android)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(pressed()),this,SLOT(Push_button_action()));
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(clicked_action_widgetlist(QListWidgetItem*)));
    connect(ui->pushButton_2,SIGNAL(pressed()),this,SLOT(chanel_dialog()));
    connect(ui->pushButton_3,SIGNAL(pressed()),this,SLOT(clicked_push_new_file()));
    open_dir(pos_dir);

    ui->lineEdit->hide();
    ui->comboBox->hide();
    ui->comboBox->addItems(QStringList()<<".txt"<<".php"<<".html");






}

File_Dialog_android::~File_Dialog_android()
{
    delete ui;
}

void File_Dialog_android::show_widget_height_size(int height_size, int dpi_y)
{
    height_push_size = dpi_y*0.34;
    open_dir(pos_dir);

}

void File_Dialog_android::open_dir(QString pos_dir)
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
    ui->pushButton_3->setMinimumHeight(height_push_size);
    ui->pushButton_3->setMaximumHeight(height_push_size);
    ui->listWidget->show();

}

void File_Dialog_android::Push_button_action()
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

void File_Dialog_android::clicked_action_widgetlist(QListWidgetItem *item_list_widget)
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
            for(int temp_a=temp_file_fotmat.size();temp_a>0;--temp_a)
            {
               if( temp_file_fotmat[temp_a]==".")
               {

                       temp_file_fotmat = temp_file_fotmat.right(temp_file_fotmat.size() - temp_a);
                       break;


            }

        }
            QString temp_file_name;
            temp_file_name=pos_dir+"/"+item_list_widget->text();
            int a =0;
           if(temp_file_fotmat==".txt"||temp_file_fotmat==".php"||temp_file_fotmat==".html"||temp_file_fotmat==".xml"||temp_file_fotmat=="xml"||temp_file_fotmat=="html"||temp_file_fotmat=="php"||temp_file_fotmat=="txt")
           {

               emit open_file(temp_file_name);
               close();
           }

    }
    }
}

void File_Dialog_android::chanel_dialog()
{
    ui->listWidget->clear();
    close();
    emit close_dialog();
}

void File_Dialog_android::clicked_push_new_file()
{
    if(ui->lineEdit->isHidden())
    {

        QListView *view_list=new QListView(ui->comboBox);
        view_list->setStyleSheet("QListView::item{height:"+QString::number(height_push_size)+"px}");

        ui->comboBox->setView(view_list);




        ui->comboBox->update();
        ui->lineEdit->setMinimumHeight(height_push_size);
        ui->lineEdit->show();
        ui->comboBox->setMinimumHeight(height_push_size);
        ui->comboBox->show();
    }else
    {
        if(!ui->lineEdit->text().isEmpty())
        {
            QFile file_create(pos_dir+"/"+ui->lineEdit->text()+ui->comboBox->currentText());
            file_create.open(QFile::WriteOnly);
            file_create.close();
            open_dir(pos_dir);
        }

        ui->lineEdit->hide();

        ui->comboBox->hide();
    }
}
