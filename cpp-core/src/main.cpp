#include <QCoreApplication>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <string>
#include "CommandProcessor.h"

// A thread that safely reads from stdin without blocking the main Qt Event Loop
class StdinReader : public QThread {
    Q_OBJECT
signals:
    void commandReceived(const QJsonObject& cmd);

protected:
    void run() override {
        std::string line;
        // Loop continuously reading from standard input
        while (std::getline(std::cin, line)) {
            QString qtLine = QString::fromStdString(line).trimmed();
            if (qtLine.isEmpty()) continue;
            
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(qtLine.toUtf8(), &err);
            if (err.error == QJsonParseError::NoError && doc.isObject()) {
                emit commandReceived(doc.object());
            } else {
                // Ignore invalid JSON
            }
        }
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    // We use QCoreApplication because this is a headless pure C++ backend
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("LKLauncher");
    
    // Start background thread to process stdin without blocking Event Loop
    CommandProcessor processor;
    StdinReader reader;
    
    // Wire the reader thread to the processor on the main Qt thread
    QObject::connect(&reader, &StdinReader::commandReceived,
                     &processor, &CommandProcessor::processCommand);
                     
    // Send a bootup message to let Tauri know it's ready
    QJsonObject initMsg;
    initMsg["status"] = "ready";
    std::cout << QJsonDocument(initMsg).toJson(QJsonDocument::Compact).toStdString() << std::endl;
                     
    reader.start();
    
    return app.exec();
}
