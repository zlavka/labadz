#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QList"
#include "QMessageBox"
#include "QComboBox"
#include "QColorDialog"
#include "QPushButton"

#include "drawwindow.h" //ПОДКЛЮЧЕНИЕ КЛАССОВ
#include "pendialog.h"
#include "brushdialog.h"
#include "pixel.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "curve.h"
#include "broken.h"
#include "polygon.h"


int lastCount=0;
int n;
bool delay=false;
QString space="*****************";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->hide();
    ui->tableWidget->setColumnCount(9);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_start_clicked() //Начало рисования объекта
{
    for (int i=1; i<ui->tableWidget->rowCount(); i=i+2)         //ЦИКЛ ПРОХОДА ПО СТРОКА С СOMBOBOX'ами
    {
        switch ((ui->tableWidget->cellWidget(i,0))->property("mode").toInt())
        {
        case 0:     //ДЛЯ ТОЧКИ
        {
            pixel px;

            myPen pen;
            QColor color;
            color.setRgb((ui->tableWidget->cellWidget(i,3)->property("colorR").toInt()),
                         (ui->tableWidget->cellWidget(i,3)->property("colorG").toInt()),
                         (ui->tableWidget->cellWidget(i,3)->property("colorB").toInt()),
                         255);
            pen.setColor(color);
            pen.setPStyle(ui->tableWidget->cellWidget(i,3)->property("style").toInt());
            pen.setThick(ui->tableWidget->cellWidget(i,3)->property("thick").toInt());

            px.setX((ui->tableWidget->item(i,1)->text()).toInt());
            px.setY((ui->tableWidget->item(i,2)->text()).toInt());
            px.draw(ui->DrawSpace->getImage(), pen.getPen());
            break;
        }
        case 1:     //ДЛЯ ПРЯМОЙ
        {
            line ln;

            myPen pen;
            QColor color;
            color.setRgb((ui->tableWidget->cellWidget(i,5)->property("colorR").toInt()),
                         (ui->tableWidget->cellWidget(i,5)->property("colorG").toInt()),
                         (ui->tableWidget->cellWidget(i,5)->property("colorB").toInt()),
                         255);
            pen.setColor(color);
            pen.setPStyle(ui->tableWidget->cellWidget(i,5)->property("style").toInt());
            pen.setThick(ui->tableWidget->cellWidget(i,5)->property("thick").toInt());

            ln.setX((ui->tableWidget->item(i,1)->text()).toInt());
            ln.setY((ui->tableWidget->item(i,2)->text()).toInt());
            ln.setX_2((ui->tableWidget->item(i,3)->text()).toInt());
            ln.setY_2((ui->tableWidget->item(i,4)->text()).toInt());
            ln.draw(ui->DrawSpace->getImage(), pen.getPen());
            break;
        }
        case 2:     //ДЛЯ ПРЯМОУГОЛЬНИКА
        {
            rectangle rect;

            myPen pen;
            QColor color;
            color.setRgb((ui->tableWidget->cellWidget(i,5)->property("colorR").toInt()),
                         (ui->tableWidget->cellWidget(i,5)->property("colorG").toInt()),
                         (ui->tableWidget->cellWidget(i,5)->property("colorB").toInt()),
                         255);
            pen.setColor(color);
            pen.setPStyle(ui->tableWidget->cellWidget(i,5)->property("style").toInt());
            pen.setThick(ui->tableWidget->cellWidget(i,5)->property("thick").toInt());

            myBrush brush;
            QColor Bcolor;
            Bcolor.setRgb((ui->tableWidget->cellWidget(i,6)->property("colorR").toInt()),
                          (ui->tableWidget->cellWidget(i,6)->property("colorG").toInt()),
                          (ui->tableWidget->cellWidget(i,6)->property("colorB").toInt()),
                          255);
            brush.setColor(Bcolor);
            brush.setBStyle(ui->tableWidget->cellWidget(i,6)->property("style").toInt());

            rect.setX((ui->tableWidget->item(i,1)->text()).toInt());
            rect.setY((ui->tableWidget->item(i,2)->text()).toInt());
            rect.setWidth((ui->tableWidget->item(i,3)->text()).toInt());
            rect.setHeight((ui->tableWidget->item(i,4)->text()).toInt());
            rect.draw(ui->DrawSpace->getImage(), pen.getPen(), brush.getBrush());
            break;
        }
        case 3:     //ДЛЯ ЭЛЛИПСА
        {
            ellipse elli;

            myPen pen;
            QColor color;
            color.setRgb((ui->tableWidget->cellWidget(i,5)->property("colorR").toInt()),
                         (ui->tableWidget->cellWidget(i,5)->property("colorG").toInt()),
                         (ui->tableWidget->cellWidget(i,5)->property("colorB").toInt()),
                         255);
            pen.setColor(color);
            pen.setPStyle(ui->tableWidget->cellWidget(i,5)->property("style").toInt());
            pen.setThick(ui->tableWidget->cellWidget(i,5)->property("thick").toInt());

            myBrush brush;
            QColor Bcolor;
            Bcolor.setRgb((ui->tableWidget->cellWidget(i,6)->property("colorR").toInt()),
                          (ui->tableWidget->cellWidget(i,6)->property("colorG").toInt()),
                          (ui->tableWidget->cellWidget(i,6)->property("colorB").toInt()),
                          255);
            brush.setColor(Bcolor);
            brush.setBStyle(ui->tableWidget->cellWidget(i,6)->property("style").toInt());

            elli.setX((ui->tableWidget->item(i,1)->text()).toInt());
            elli.setY((ui->tableWidget->item(i,2)->text()).toInt());
            elli.setRad1((ui->tableWidget->item(i,3)->text()).toInt());
            elli.setRad2((ui->tableWidget->item(i,4)->text()).toInt());
            elli.draw(ui->DrawSpace->getImage(), pen.getPen(), brush.getBrush());
            break;
        }
        case 4:     //ДЛЯ ДУГИ
        {
            curve arc;

            myPen pen;
            QColor color;
            color.setRgb((ui->tableWidget->cellWidget(i,7)->property("colorR").toInt()),
                         (ui->tableWidget->cellWidget(i,7)->property("colorG").toInt()),
                         (ui->tableWidget->cellWidget(i,7)->property("colorB").toInt()),
                         255);
            pen.setColor(color);
            pen.setPStyle(ui->tableWidget->cellWidget(i,7)->property("style").toInt());
            pen.setThick(ui->tableWidget->cellWidget(i,7)->property("thick").toInt());

            arc.setX((ui->tableWidget->item(i,1)->text()).toInt());
            arc.setY((ui->tableWidget->item(i,2)->text()).toInt());
            arc.setWidth((ui->tableWidget->item(i,3)->text()).toInt());
            arc.setHeight((ui->tableWidget->item(i,4)->text()).toInt());
            arc.setStartAngle((ui->tableWidget->item(i,5)->text()).toInt());
            arc.setEndAngle((ui->tableWidget->item(i,6)->text()).toInt());
            arc.draw(ui->DrawSpace->getImage(), pen.getPen());
            break;
        }
        }
    }
    if (!ui->DrawSpace->isVisible())
    {
        ui->DrawSpace->setVision(!ui->DrawSpace->isVisible());
    }
    repaint();
}


void MainWindow::on_pushButton_clear_clicked()      //ОЧИСТКА ВИДЖЕТА
{
    ui->DrawSpace->clearImage();
}


void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)     //ДЕЙСТВИЯ ПРИ ИЗМЕНЕНИИ ЭЛЕМЕНТА ТАБЛИЦЫ
{
    int col=item->column();
    int row=item->row();
    if (((col!=0)&&(row%2!=0))&&(delay==false))      //ЕСЛИ ЗАДЕРЖКА ОТСУТСВУЕТ, И ИЗМЕНЁНА ЯЧЕЙКА ДЛЯ ПОЛЬЗОВАТЕЛЬСКОГО ВВОДА
    {
        bool flag_int;
        bool fault=false;
        QString number=item->text();
        int num=number.toInt(&flag_int,10);

        if (flag_int)       //ЕСЛИ БЫЛО ВВЕДЕНО ЧИСЛО
        {
            switch (ui->tableWidget->cellWidget(row,0)->property("mode").toInt())       //ПРОВЕРКА ВЫБРАНОЙ ФИГУРЫ В COMBOBOX'е
            {
            case 0:     //ДЛЯ ТОЧКИ
            {
                if ((col==1)&&((num<0)||(num>1150)))        //ПРОВЕРКА Х
                    fault=true;
                if ((col==2)&&((num<0)||(num>411)))         //ПРОВЕРКА Y
                    fault=true;
                if (fault)                                  //ЕСЛИ ВВЕДЕНЫ НЕДОПУСТИМЫЕ X ИЛИ Y
                {
                    item->setText("0");
                    QMessageBox::information(0,"Ошибка","Координаты за пределами окна! (размер окна 1150х411)",QMessageBox::Ok);
                }
                else
                    *item = QTableWidgetItem(number);
                break;
            }
            case 1:     //ДЛЯ ПРЯМОЙ
            {
                if (((col==1)||(col=3))&&((num<0)||(num>1150)))
                    fault=true;
                if (((col==2)||(col=4))&&((num<0)||(num>411)))
                    fault=true;
                if (fault)
                {
                    item->setText("0");
                    QMessageBox::information(0,"Ошибка","Координаты за пределами окна! (размер окна 1150х411)",QMessageBox::Ok);
                }
                else
                    *item = QTableWidgetItem(number);
                break;
            }
            case 2:     //ДЛЯ ПРЯМОУГОЛЬНИКА
            case 3:     //ДЛЯ ЭЛЛИПСА
            {
                if ((col==1)&&((num<0)||(num>1150)))
                    fault=true;
                if ((col==2)&&((num<0)||(num>411)))
                    fault=true;
                if (fault)
                {
                    item->setText("0");
                    QMessageBox::information(0,"Ошибка","Координаты за пределами окна! (размер окна 1150х411)",QMessageBox::Ok);
                }
                else
                    *item = QTableWidgetItem(number);
                break;
            }
            case 4:     //ДЛЯ ДУГИ
            {
                if ((col==1)&&((num<0)||(num>1150)))
                    fault=true;
                if ((col==2)&&((num<0)||(num>411)))
                    fault=true;
                if (fault)
                {
                    item->setText("0");
                    QMessageBox::information(0,"Ошибка","Координаты за пределами окна! (размер окна 1150х411)",QMessageBox::Ok);
                }
                else
                    if (((col==5)||(col==6))&&((num<(-360))||(num>360)))         //ЕСЛИ ВВЁДЕН УГОЛ >360 ИЛИ <0 ГРАДУСОВ
                    {
                        if (num<(-360))
                            num=-360;
                        else
                            num=360;
                        *item = QTableWidgetItem(QString::number(num));
                    }
                break;
            }
            }           //КОНЕЦ ПРОВЕРКИ ВЫБРАНОЙ ФИГУРЫ В COMBOBOX'е
        }
        else    //ЕСЛИ БЫЛО ВВЕДЕНО НЕ ЧИСЛО
        {
            item->setText("0");
            QMessageBox::information(0,"Ошибка","Введены некорректные данные!",QMessageBox::Ok);
        }
    }
}



void MainWindow::on_spinBox_ObjectCount_valueChanged(int arg1)
{
    delay = true;           //DELAY ОТКЛЮЧАЕТ ПРОВЕРКУ НА ВВОД ДАННЫХ В ТАБЛИЦУ НА ВРЕМЯ ДОБАВЛЕНИЕ В НЕЁ НОВОЙ СТРОКИ


    if (arg1>0)             //СКРЫТИЕ ТАБЛИЦЫ ПРИ КОЛ-ВЕ ОБЪЕКТОВ=0
    {
        if (ui->tableWidget->isHidden())
            ui->tableWidget->show();
    }
    else                    //ОТОБРАЖЕНИЕ ТАБЛИЦЫ ПРИ КОЛ-ВЕ ОБЪЕКТОВ>0
        if (ui->tableWidget->isVisible())
            ui->tableWidget->hide();
    if (lastCount<arg1)         //ЕСЛИ КОЛ-ВО ОБЪЕКТОВ БЫЛО УВЕЛИЧЕНО
    {
        if (ui->spinBox_ObjectCount->value()<5)
            ui->tableWidget->setGeometry(140,10,1030,60+38*(arg1-1));
        else
            ui->tableWidget->setGeometry(140,10,1030,175);
        int change=arg1-lastCount;
        int index=(lastCount+(lastCount-1)+2);     //НОМЕР ПОСЛЕДНЕЙ СТРОКИ В ТАБЛИЦЕ
        ui->tableWidget->setRowCount(lastCount*2+change*2);
        QComboBox *combo;                   //ОБЪЯВЛЕНИЕ ОБЪЕКТОВ ПЕРЕД ЦИКЛОМ ЗАПОЛНЕНИЯ ТАБЛИЦЫ
        QPushButton *penButton;
        QTableWidgetItem *item;
        QTableWidgetItem *item1;
        QTableWidgetItem *item12;
        QTableWidgetItem *item2;
        QTableWidgetItem *item22;
        QTableWidgetItem *item3;
        QTableWidgetItem *item4;
        QTableWidgetItem *item42;
        QTableWidgetItem *item5;
        QTableWidgetItem *item52;
        QTableWidgetItem *item6;
        QTableWidgetItem *item62;
        QTableWidgetItem *item7;
        QTableWidgetItem *item72;
        QTableWidgetItem *item8;
        QTableWidgetItem *item82;
        for (int i=index; i<=index+change*2; i=i+2)
        {
            item = new QTableWidgetItem;        //УСТАНОВКА ТЕКСТА И ЦВЕТА ДЛЯ ITEM'ОВ
            item1 = new QTableWidgetItem;
            item12 = new QTableWidgetItem;
            item2 = new QTableWidgetItem;
            item22 = new QTableWidgetItem;
            item3 = new QTableWidgetItem;
            item4 = new QTableWidgetItem;
            item42 = new QTableWidgetItem;
            item5 = new QTableWidgetItem;
            item52 = new QTableWidgetItem;
            item6 = new QTableWidgetItem;
            item62 = new QTableWidgetItem;
            item7 = new QTableWidgetItem;
            item72 = new QTableWidgetItem;
            item8 = new QTableWidgetItem;
            item82 = new QTableWidgetItem;

            item->setText("Объект");
            item->setBackgroundColor(Qt::darkYellow);
            item1->setText("X");
            item1->setBackgroundColor(Qt::darkYellow);
            item12->setText("0");
            item2->setText("Y");
            item2->setBackgroundColor(Qt::darkYellow);
            item22->setText("0");
            item3->setText("Перо");
            item3->setBackgroundColor(Qt::darkYellow);
            item4->setText(space);
            item4->setBackgroundColor(Qt::darkYellow);
            item42->setText(space);
            item5->setText(space);
            item5->setBackgroundColor(Qt::darkYellow);
            item6->setText(space);
            item6->setBackgroundColor(Qt::darkYellow);
            item52->setText(space);
            item62->setText(space);
            item7->setText(space);
            item7->setBackgroundColor(Qt::darkYellow);
            item72->setText(space);
            item8->setText(space);
            item8->setBackgroundColor(Qt::darkYellow);
            item82->setText(space);

            combo = new QComboBox;          //ЗАДАНИЕ ЭЛЕМЕНТОВ COMBOBOX
            combo->addItem("Точка");
            combo->addItem("Линия");
            combo->addItem("Прямоугольник");
            combo->addItem("Эллипс");
            combo->addItem("Дуга");
            combo->setProperty("row", (int) i);        //СВОЙСТВО COMBOBOX (Номер строки)
            combo->setProperty("mode", (int) 0);       //СВОЙСТВО COMBOBOX (Текущий индекс)
            connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_currentIndexChanged(int)));    //СОЕДИНЕНИЕ СИГНАЛА ИЗМЕНЕНИЕЯ ИНДЕКСА С СООТВЕТСВУЮЩИМ СЛОТОМ

            penButton = new QPushButton;        //ЗАДАНИЕ КНОПКИ ПЕРА
            penButton->setText("Установить");
            connect(penButton,SIGNAL(clicked()),this, SLOT(pushButton_pen_clicked()));      //СОЕДИНЕНИЕ СИГНАЛА CLICK С СООТВЕТСВУЮЩИМ СЛОТОМ
            penButton->setProperty("thick", 1);     //СВОЙСТВО PENBUTTON (Толщина пера)
            penButton->setProperty("style", 0);     //СВОЙСТВО PENBUTTON (Стиль пера)
            penButton->setProperty("colorR", 0);     //СВОЙСТВО PENBUTTON (Составляющие цвета пера)
            penButton->setProperty("colorG", 0);
            penButton->setProperty("colorB", 0);
            ui->tableWidget->setItem(i-1,0,item);       //РАССТАНОВКА ITEM'о и ВИДЖЕТОВ В ЯЧЕЙКИ
            ui->tableWidget->setItem(i-1,1,item1);
            ui->tableWidget->setItem(i,1,item12);
            ui->tableWidget->setItem(i-1,2,item2);
            ui->tableWidget->setItem(i,2,item22);
            ui->tableWidget->setItem(i-1,3,item3);
            ui->tableWidget->setCellWidget(i,3,penButton);
            ui->tableWidget->setItem(i-1,4,item4);
            ui->tableWidget->setItem(i,4,item42);
            ui->tableWidget->setItem(i-1,5,item5);
            ui->tableWidget->setItem(i,5,item52);
            ui->tableWidget->setItem(i-1,6,item6);
            ui->tableWidget->setItem(i,6,item62);
            ui->tableWidget->setItem(i-1,7,item7);
            ui->tableWidget->setItem(i,7,item72);
            ui->tableWidget->setItem(i-1,8,item8);
            ui->tableWidget->setItem(i,8,item82);
            ui->tableWidget->setCellWidget(i,0,combo);
        }
    }
    else        //ЕСЛИ КОЛ-ВО ОБЪЕКТОВ БЫЛО УМЕНЬШЕНО
    {
        if (ui->spinBox_ObjectCount->value()<5)
            ui->tableWidget->setGeometry(140,10,1030,60+38*(arg1-1));
        else
            ui->tableWidget->setGeometry(140,10,1030,175);
        int change=lastCount-arg1;               //РАЗНОСТЬ МЕЖДУ СТАРЫМ И ТЕКУЩИМ КОЛ-ВОМ ЭЛЕМЕНТОВ
        int index=(lastCount+(lastCount-1));     //НОМЕР ПОСЛЕДНЕЙ СТРОКИ В ТАБЛИЦЕ
        for (int i=index; i>index-change*2;i=i-1)       //УДАЛЕНИЕ НЕНУЖНЫХ СТРОК ТАБЛИЦЫ
        {
            ui->tableWidget->removeRow(i);
        }
        ui->tableWidget->setRowCount(lastCount*2-change*2);     //УСТАНОВКА НОВОГО КОЛ-ВА СТРОК
                                               //НОВОЕ "ПОСЛЕДНЕЕ" ЗНАЧЕНИЕ КОЛ-ВА ЭЛЕМЕНТОВ
    }

    for (int i=0; i<ui->tableWidget->rowCount()-1; i=i+2)       //УСТАНОВКА ЗАПРЕТА НА ИЗМЕНЕНИЕ ФУНКЦИОНАЛЬНЫХ ЯЧЕЕК
    {
        for (int j=0; j<ui->tableWidget->columnCount(); j++)
        {
            if (j>=4)
            {
                ui->tableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled);
                ui->tableWidget->item(i+1,j)->setFlags(Qt::ItemIsEnabled);
            }
            else
            {
                ui->tableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled);
            }
        }
    }

    for (int i=1;i<(ui->tableWidget->rowCount());i=i+2)     //ОЧИСТКА ОТ ЛИШНИХ ДЛЯ ТОЧКИ PushButton
    {
        for (int j=4; j<=8;j++)
        {
            if (ui->tableWidget->cellWidget(i,j)!=NULL)
                ui->tableWidget->removeCellWidget(i,j);
        }
    }
    lastCount=arg1;
    delay=false;        //СНЯТИЕ ЗАДЕРЖКИ ПРОВЕРКИ НА ВВОД
}


void MainWindow::comboBox_currentIndexChanged(int value)            //ДЕЙСТВИЕ ПРИ ИЗМЕНЕНИИ ФИГУРЫ В COMBOBOX'е
{
    delay = true;         //ЗАДЕРЖКА ДЛЯ ОТКЛЮЧЕНИЯ ПРОВЕРКИ ВВОДИМЫХ ДАННЫХ
    int nRow = sender()->property("row").toInt();       //СТРОКА, В КОТОРОЙ НАХОДИТСЯ COMBOBOX
    sender()->setProperty("mode",value);

    QPushButton *penButton;             //ЗАДАНИЕ КНОПКИ ПЕРА
    penButton = new QPushButton;
    penButton->setText("Установить");
    connect(penButton,SIGNAL(clicked()),this, SLOT(pushButton_pen_clicked()));
    penButton->setProperty("thick", 1);
    penButton->setProperty("style", 0);
    penButton->setProperty("colorR", 0);
    penButton->setProperty("colorG", 0);
    penButton->setProperty("colorB", 0);

    QPushButton *brushButton;           //ЗАДАНИЕ КНОПКИ КИСТИ
    brushButton = new QPushButton;
    brushButton->setText("Установить");
    connect(brushButton,SIGNAL(clicked()),this, SLOT(pushButton_brush_clicked()));
    brushButton->setProperty("style", 0);
    brushButton->setProperty("colorR", 0);
    brushButton->setProperty("colorG", 0);
    brushButton->setProperty("colorB", 0);


    QTableWidgetItem *item1 = new QTableWidgetItem;     //ITEM'ы ДЛЯ СЛУЧАЕВ, КОГДА КОЛ-ВО СТОЛБОЦОВ В НОВОЙ ФИГУРЫ БОЛЬШЕ ЧЕМ У СТАРОЙ
    item1->setText("0");
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText("0");
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText("0");
    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setText("0");
    switch (value)
    {
    case 0:         //ВЫБОР ТОЧКИ
    {
        ui->tableWidget->item(nRow-1,1)->setText("X");
        ui->tableWidget->item(nRow-1,1)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,1)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow,1)->setText("0");
        ui->tableWidget->item(nRow,1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,2)->setText("Y");
        ui->tableWidget->item(nRow-1,2)->setBackgroundColor(Qt::darkYellow);
        ui->tableWidget->item(nRow-1,2)->setFlags(Qt::ItemIsEnabled);

        ui->tableWidget->item(nRow,2)->setText("0");
        ui->tableWidget->item(nRow,2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,3)->setText("Перо");
        ui->tableWidget->item(nRow-1,3)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setCellWidget(nRow,3,penButton);

        for (int i=4;i<=8;i++)          //ЦИКЛ ОЧИСТКИ ОСТАВШИХСЯ ЯЧЕЕК
        {
            ui->tableWidget->item(nRow-1,i)->setText(space);
            ui->tableWidget->item(nRow-1,i)->setFlags(Qt::ItemIsEnabled);
            if (ui->tableWidget->cellWidget(nRow,i)!=NULL)
                ui->tableWidget->removeCellWidget(nRow,i);
            ui->tableWidget->item(nRow,i)->setText(space);
            ui->tableWidget->item(nRow,i)->setFlags(Qt::ItemIsEnabled);
        }
        break;
    }
    case 1:     //ВЫБОР ПРЯМОЙ
    {
        ui->tableWidget->item(nRow-1,1)->setText("Х начала");
        ui->tableWidget->item(nRow-1,1)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,1)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow-1,2)->setText("Y начала");
        ui->tableWidget->item(nRow-1,2)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,2)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow-1,3)->setText("Х конца");
        ui->tableWidget->item(nRow-1,3)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,3)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,3)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,3);
        }
        ui->tableWidget->setItem(nRow,3,item1);
        ui->tableWidget->item(nRow,3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,4)->setText("Y конца");
        ui->tableWidget->item(nRow-1,4)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,4)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,4)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,4);
        }
        ui->tableWidget->setItem(nRow,4,item2);
        ui->tableWidget->item(nRow,4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,5)->setText("Перо");
        ui->tableWidget->item(nRow-1,5)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setCellWidget(nRow,5,penButton);

        QTableWidgetItem *item;
        for (int i=6;i<=8;i++)          //ЦИКЛ ОЧИСТКИ ОСТАВШИХСЯ ЯЧЕЕК
        {
            ui->tableWidget->item(nRow-1,i)->setText(space);
            ui->tableWidget->item(nRow-1,i)->setFlags(Qt::ItemIsEnabled);

            if  (ui->tableWidget->cellWidget(nRow,i)!=NULL)
            {
                ui->tableWidget->removeCellWidget(nRow,i);
            }
            item = new QTableWidgetItem;
            item->setText(space);
            ui->tableWidget->setItem(nRow,i,item);
            ui->tableWidget->item(nRow,i)->setFlags(Qt::ItemIsEnabled);
        }
        break;
    }
    case 2:     //ВЫБОР ПРЯМОУГОЛЬНИКА
    {
        ui->tableWidget->item(nRow-1,1)->setText("Х");
        ui->tableWidget->item(nRow-1,1)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,1)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow-1,2)->setText("Y");
        ui->tableWidget->item(nRow-1,2)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,2)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow-1,3)->setText("Ширина");
        ui->tableWidget->item(nRow-1,3)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,3)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,3)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,3);
        }
        ui->tableWidget->setItem(nRow,3,item1);
        ui->tableWidget->item(nRow,3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,4)->setText("Высота");
        ui->tableWidget->item(nRow-1,4)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,4)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,4)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,4);
        }
        ui->tableWidget->setItem(nRow,4,item2);
        ui->tableWidget->item(nRow,4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,5)->setText("Перо");
        ui->tableWidget->item(nRow-1,5)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setCellWidget(nRow,5,penButton);

        ui->tableWidget->item(nRow-1,6)->setText("Кисть");
        ui->tableWidget->item(nRow-1,6)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setCellWidget(nRow,6,brushButton);

        QTableWidgetItem *item;
        for (int i=7;i<=8;i++)          //ЦИКЛ ОЧИСТКИ ОСТАВШИХСЯ СТОЛБЦОВ
        {
            ui->tableWidget->item(nRow-1,i)->setText(space);
            ui->tableWidget->item(nRow-1,i)->setFlags(Qt::ItemIsEnabled);

            if  (ui->tableWidget->cellWidget(nRow,i)!=NULL)
                ui->tableWidget->removeCellWidget(nRow,i);
            item = new QTableWidgetItem;
            item->setText(space);
            ui->tableWidget->setItem(nRow,i,item);
            ui->tableWidget->item(nRow,i)->setFlags(Qt::ItemIsEnabled);
        }
        break;
    }
    case 3:         //ВЫБОР ЭЛЛИПСА
    {
        ui->tableWidget->item(nRow-1,1)->setText("Х");
        ui->tableWidget->item(nRow-1,1)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,1)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow-1,2)->setText("Y");
        ui->tableWidget->item(nRow-1,2)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,2)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow-1,3)->setText("Ширина");
        ui->tableWidget->item(nRow-1,3)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,3)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,3)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,3);
        }
        ui->tableWidget->setItem(nRow,3,item1);
        ui->tableWidget->item(nRow,3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,4)->setText("Высота");
        ui->tableWidget->item(nRow-1,4)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,4)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,4)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,4);
        }
        ui->tableWidget->setItem(nRow,4,item2);
        ui->tableWidget->item(nRow,4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,5)->setText("Перо");
        ui->tableWidget->item(nRow-1,5)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setCellWidget(nRow,5,penButton);

        ui->tableWidget->item(nRow-1,6)->setText("Кисть");
        ui->tableWidget->item(nRow-1,6)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setCellWidget(nRow,6,brushButton);

        QTableWidgetItem *item;
        for (int i=7;i<=8;i++)          //ЦИКЛ ОЧИСТКИ ОСТАВШИХСЯ СТОЛБЦОВ
        {
            ui->tableWidget->item(nRow-1,i)->setText(space);
            ui->tableWidget->item(nRow-1,i)->setFlags(Qt::ItemIsEnabled);

            if  (ui->tableWidget->cellWidget(nRow,i)!=NULL)
                ui->tableWidget->removeCellWidget(nRow,i);
            item = new QTableWidgetItem;
            item->setText(space);
            ui->tableWidget->setItem(nRow,i,item);
            ui->tableWidget->item(nRow,i)->setFlags(Qt::ItemIsEnabled);
        }
        break;
    }
    case 4:         //ВЫБОР ДУГИ
    {
        ui->tableWidget->item(nRow-1,1)->setText("Х");
        ui->tableWidget->item(nRow-1,1)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,1)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow-1,2)->setText("Y");
        ui->tableWidget->item(nRow-1,2)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,2)->setBackgroundColor(Qt::darkYellow);

        ui->tableWidget->item(nRow-1,3)->setText("Ширина");
        ui->tableWidget->item(nRow-1,3)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,3)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,3)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,3);
        }
        ui->tableWidget->setItem(nRow,3,item1);
        ui->tableWidget->item(nRow,3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,4)->setText("Высота");
        ui->tableWidget->item(nRow-1,4)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,4)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,4)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,4);
        }
        ui->tableWidget->setItem(nRow,4,item2);
        ui->tableWidget->item(nRow,4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,5)->setText("Начальный угол");
        ui->tableWidget->item(nRow-1,5)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,5)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,5)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,5);
        }
        ui->tableWidget->setItem(nRow,5,item3);
        ui->tableWidget->item(nRow,5)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,6)->setText("Градусная мера");
        ui->tableWidget->item(nRow-1,6)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->item(nRow-1,6)->setBackgroundColor(Qt::darkYellow);

        if  (ui->tableWidget->cellWidget(nRow,6)!=NULL)
        {
            ui->tableWidget->removeCellWidget(nRow,6);
        }
        ui->tableWidget->setItem(nRow,6,item4);
        ui->tableWidget->item(nRow,6)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

        ui->tableWidget->item(nRow-1,7)->setText("Перо");
        ui->tableWidget->item(nRow-1,7)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setCellWidget(nRow,7,penButton);
        break;
    }
    }
    delay = false;      //СНЯТИЕ ЗАДЕРЖКИ
}


void MainWindow::pushButton_pen_clicked()       //КНОПКА ВЫБОРА ПЕРА
{
    PenDialog *dialog = new PenDialog;
    QColor color;
    color.setRgb(sender()->property("colorR").toInt(),      //СЧИТЫВАНИЕ ПРЕДЫДУЩИХ ЗНАЧЕНИЙ ПЕРА (ЦВЕТА. ТОЛЩИНЫ И СТИЛЯ)
                 sender()->property("colorG").toInt(),
                 sender()->property("colorB").toInt(),
                 255);
    dialog->setColor(color);
    dialog->setThick(sender()->property("thick").toInt());
    dialog->setPStyle(sender()->property("style").toInt());
    dialog->preSet();       //ВЫЗОВ МЕТОДА ПОДГОТОВКИ ДИАЛОГОВОГО ОКНА (ВЫСТАВЛЕНИЕ В НЁМ СЧИТАННЫХ РАНЕЕ ПРЕДЫДУЩИХ ПАРАМЕТРОВ)

    if (dialog->exec() == QDialog::Accepted)        //ЕСЛИ В ДИАЛОГОВОМ ОКНЕ БЫЛО НАЖАТО "OK"
    {
        sender()->setProperty("thick", dialog->getThick());     //УСТАНОВКА НОВЫХ ПАРАМЕТРОВ ДЛЯ PenButton'а
        sender()->setProperty("style", dialog->getStyle());
        sender()->setProperty("colorR", dialog->getColor().red());
        sender()->setProperty("colorG", dialog->getColor().green());
        sender()->setProperty("colorB", dialog->getColor().blue());
    }
}


void MainWindow::pushButton_brush_clicked()      //КНОПКА ВЫБОРА ЗАЛИВКИ
{
    BrushDialog *dialog = new BrushDialog;
    QColor color;
    color.setRgb(sender()->property("colorR").toInt(),          //СЧИТЫВАНИЕ ПРЕДЫДУЩИХ ЗНАЧЕНИЙ КИСТИ (ЦВЕТА И СТИЛЯ)
                 sender()->property("colorG").toInt(),
                 sender()->property("colorB").toInt(),
                 255);
    dialog->setColor(color);
    dialog->setBStyle(sender()->property("style").toInt());
    dialog->preSet();                                           //ВЫЗОВ МЕТОДА ПОДГОТОВКИ ДИАЛОГОВОГО ОКНА (ВЫСТАВЛЕНИЕ В НЁМ СЧИТАННЫХ РАНЕЕ ПРЕДЫДУЩИХ ПАРАМЕТРОВ)

    if (dialog->exec() == QDialog::Accepted)
    {
        sender()->setProperty("style", dialog->getStyle());         //УСТАНОВКА НОВЫХ ПАРАМЕТРОВ ДЛЯ brushButton'а
        sender()->setProperty("colorR", dialog->getColor().red());
        sender()->setProperty("colorG", dialog->getColor().green());
        sender()->setProperty("colorB", dialog->getColor().blue());
    }
}
