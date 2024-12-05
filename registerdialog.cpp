#include "RegisterDialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Register");

    auto layout = new QVBoxLayout(this);

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");
    layout->addWidget(usernameEdit);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setPlaceholderText("Confirm Password");
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(confirmPasswordEdit);

    registerButton = new QPushButton("Register", this);
    layout->addWidget(registerButton);
    connect(registerButton, &QPushButton::clicked, this, &RegisterDialog::onRegister);
}

void RegisterDialog::onRegister() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString confirmPassword = confirmPasswordEdit->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Registration Failed", "All fields must be filled.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Registration Failed", "Passwords do not match.");
        return;
    }

    // Запись данных пользователя в файл
    QFile file("users.txt"); // Имя файла для хранения данных о пользователях
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << username << "," << password << "\n"; // Сохраняем имя и пароль, разделенные запятой
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Could not open file for writing.");
        return;
    }

    QMessageBox::information(this, "Registration Successful", "You have been registered.");
    accept(); // Закрывает диалог с успехом
}
