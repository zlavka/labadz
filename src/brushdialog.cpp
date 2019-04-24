#include "brushdialog.h"
#include "ui_brushdialog.h"
#include "QColorDialog"


BrushDialog::BrushDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushDialog)
{
    ui->setupUi(this);
}

void BrushDialog::preSet()
{
    ui->comboBox_style->setCurrentIndex(this->getStyle());
    repaint();
}

BrushDialog::~BrushDialog()
{
    delete ui;
}

void BrushDialog::on_pushButton_ok_clicked()
{
    this->setBStyle(ui->comboBox_style->currentIndex());
    this->accept();
}


void BrushDialog::on_pushButton_color_clicked()
{
    QColorDialog colorDialog;
    this->setColor(colorDialog.getColor(getColor(),this));
    repaint();
}

void BrushDialog::on_comboBox_style_currentIndexChanged(int index)
{
    if (index==0)
        ui->pushButton_color->setEnabled(false);
    else
        ui->pushButton_color->setEnabled(true);
}
