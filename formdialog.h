#ifndef FORMDIALOG_H
#define FORMDIALOG_H

#include "BaseDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

class FormDialog : public BaseDialog {
    Q_OBJECT

public:
    explicit FormDialog(QWidget* parent = nullptr);

protected:
    void addFormRow(QVBoxLayout* layout, const QString& labelText, QLineEdit*& lineEdit);

private:
    QList<QLineEdit*> formFields;
};

#endif // FORMDIALOG_H
