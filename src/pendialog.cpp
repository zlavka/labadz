#include "pendialog.h"
#include "ui_pendialog.h"
#include "QColorDialog"
#include "QPainter"


PenDialog::PenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PenDialog)
{
    ui->setupUi(this);
}

void PenDialog::preSet()
{
    ui->spinBox_thick->setValue(this->getThick());
    ui->comboBox_style->setCurrentIndex(this->getStyle());
    repaint();
}

PenDialog::~PenDialog()
{
    delete ui;
}


void PenDialog::on_pushButton_ok_clicked()
{
    this->setThick(ui->spinBox_thick->value());
    this->setPStyle(ui->comboBox_style->currentIndex());
    this->accept();
}

void PenDialog::on_pushButton_color_clicked()
{
    QColorDialog colorDialog;
    this->setColor(colorDialog.getColor(getColor(),this));
    repaint();
}

