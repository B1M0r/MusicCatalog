#include "LoginDialog.h"
#include "registerdialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Login");

    auto layout = new QVBoxLayout(this);

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");
    layout->addWidget(usernameEdit);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLogin);

    registerButton = new QPushButton("Register", this);
    layout->addWidget(registerButton);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::onRegister);
}

void LoginDialog::onLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    QFile file("users.txt"); // Путь к файлу с данными пользователей
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open user data file.");
        return;
    }

    QTextStream in(&file);
    bool loginSuccessful = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');

        if (parts.size() == 2) {
            QString storedUsername = parts[0];
            QString storedPassword = parts[1];

            // Проверка на совпадение имени пользователя и пароля
            if (username == storedUsername && password == storedPassword) {
                loginSuccessful = true;
                break;
            }
        }
    }

    file.close();

    if (loginSuccessful) {
        accept(); // Закрывает диалог с успехом
    } else {
        QMessageBox::warning(this, "Login Failed", "Incorrect username or password.");
    }
}

void LoginDialog::onRegister() {
    RegisterDialog registerDialog(this);  // Создаем экземпляр окна регистрации
    if (registerDialog.exec() == QDialog::Accepted) {  // Открываем окно и ждем, пока оно закроется
    }
}
