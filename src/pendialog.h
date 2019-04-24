#ifndef PENDIALOG_H
#define PENDIALOG_H

#include <QDialog>
#include "mypen.h"

namespace Ui {
    class PenDialog;
}

class PenDialog : public QDialog, public myPen
{
    Q_OBJECT

public:
    explicit PenDialog(QWidget *parent = 0);
    ~PenDialog();
    void preSet();

private slots:

    void on_pushButton_ok_clicked();

    void on_pushButton_color_clicked();

private:
    Ui::PenDialog *ui;
};

#endif // PENDIALOG_H
