#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QWebEngineView>
#include "../network/APIService.h"
#include "../Launcher.h"

/**
 * @brief The main dashboard and navigation container window
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();
    void applyStyles();

private slots:
    void onModpacksLoaded(const QList<Modpack> &modpacks);
    void onLoadFailed(const QString &error);
    void onOpenModpackDetail(const Modpack &pack);

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QWebEngineView *webView;

    APIService *apiService;

    Launcher *launcher;
};
