#include "FormDialog.h"

FormDialog::FormDialog(QWidget* parent)
    : BaseDialog(parent) {
}

void FormDialog::addFormRow(QVBoxLayout* layout, const QString& labelText, QLineEdit*& lineEdit) {
    QLabel* label = new QLabel(labelText, this);
    lineEdit = new QLineEdit(this);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    formFields.append(lineEdit);
}
