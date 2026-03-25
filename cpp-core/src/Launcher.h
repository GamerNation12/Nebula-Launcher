#pragma once

#include <QObject>
#include <QProcess>
#include <QJsonObject>

/**
 * @brief Manages launching Minecraft operations utilizing QProcess
 */
class Launcher : public QObject {
    Q_OBJECT
public:
    explicit Launcher(QObject *parent = nullptr);
    ~Launcher();

    /**
     * @brief Launch a Minecraft instance by ID
     * @return true if starting triggered successfully
     */
    bool launchInstance(const QString &instanceId, const QJsonObject &auth = QJsonObject());

signals:
    /**
     * @brief Emitted when log output streaming is read
     */
    void logReceived(const QString &line);
    
    void gameStarted();
    void gameFinished(int exitCode);

private slots:
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();
    void onFinished(int exitCode, QProcess::ExitStatus status);

private:
    QProcess *process;
};
