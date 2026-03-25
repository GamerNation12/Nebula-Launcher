#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "FileSystem.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("LuminaKraft Launcher (C++)");
    window.resize(800, 500);

    QWidget *centralWidget = new QWidget(&window);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *label = new QLabel("Hello from LuminaKraft C++ Skeleton!", centralWidget);
    label->setAlignment(Qt::AlignCenter);
    
    // Setup a modern font style mock
    QFont font = label->font();
    font.setPointSize(16);
    font.setBold(true);
    label->setFont(font);

    layout->addWidget(label);

    QLabel *dirLabel = new QLabel("Launcher Data Dir:\n" + FileSystem::getLauncherDataDir(), centralWidget);
    dirLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(dirLabel);

    QLabel *subLabel = new QLabel("To build this, install Qt 6 and run CMake in this directory.", centralWidget);
    subLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(subLabel);

    window.setCentralWidget(centralWidget);
    window.show();

    return app.exec();
}
