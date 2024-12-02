#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class BaseDialog : public QDialog {
    Q_OBJECT

public:
    explicit BaseDialog(QWidget* parent = nullptr);
    virtual ~BaseDialog() = default;

protected:
    void addOkCancelButtons(QVBoxLayout* layout);

    QPushButton* okButton;
    QPushButton* cancelButton;
};

#endif // BASEDIALOG_H
