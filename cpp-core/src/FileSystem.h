#pragma once

#include <QString>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

class FileSystem {
public:
    /**
     * @brief Get the path to the launcher data directory
     */
    static QString getLauncherDataDir();

    /**
     * @brief Get the path to instances directory
     */
    static QString getInstancesDir();

    /**
     * @brief Get the path to the metadata versions directory
     */
    static QString getMetaVersionsDir();
    
    /**
     * @brief Read instance JSON metadata from disk
     */
    static QJsonObject readInstanceJson(const QString &instanceId);

    /**
     * @brief Read version JSON metadata from disk
     */
    static QJsonObject readVersionJson(const QString &version);
    
    /**
     * @brief Sanitize a modpack name to be filesystem-safe
     */
    static QString sanitizeFolderName(const QString &name);

    /**
     * @brief Generate a unique folder name for an instance
     */
    static QString generateInstanceFolderName(const QString &modpackName);
    
    /**
     * @brief Helper to ensure a directory exists
     */
    static bool ensureDirExists(const QString &path);
};
