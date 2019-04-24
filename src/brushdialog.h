#ifndef BRUSHDIALOG_H
#define BRUSHDIALOG_H

#include <QDialog>
#include "mybrush.h"

namespace Ui {
    class BrushDialog;
}

class BrushDialog : public QDialog, public myBrush
{
    Q_OBJECT

public:
    explicit BrushDialog(QWidget *parent = 0);
    ~BrushDialog();
    void preSet();

private slots:
    void on_pushButton_color_clicked();

    void on_pushButton_ok_clicked();

    void on_comboBox_style_currentIndexChanged(int index);

private:
    Ui::BrushDialog *ui;
};

#endif // BRUSHDIALOG_H
