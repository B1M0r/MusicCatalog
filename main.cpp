#include <QApplication>
#include "MainWindow.h"
#include "LoginDialog.h"

int main(int argc, char *argv[]) {
    QApplication::setStyle("Fusion");
    QApplication app(argc, argv);

    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // Открытие главного окна приложения
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    }

    return 0;
}
