#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget* parent = nullptr);

private slots:
    void onRegister();

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* confirmPasswordEdit;
    QPushButton* registerButton;
};

#endif // REGISTERDIALOG_H
