#include "BaseDialog.h"

BaseDialog::BaseDialog(QWidget* parent)
    : QDialog(parent) {
}

void BaseDialog::addOkCancelButtons(QVBoxLayout* layout) {
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Отмена", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    layout->addWidget(okButton);
    layout->addWidget(cancelButton);
}
