#include "FileSystem.h"
#include <QStandardPaths>
#include <QRegularExpression>
#include <QDebug>

QString FileSystem::getLauncherDataDir() {
    // Determine AppData path
    QString appData = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    
    // Qt translates AppDataLocation on Windows typically to:
    // C:/Users/<User>/AppData/Roaming/<AppName>
    // We can append our exact custom directory if needed, but AppDataLocation is usually fine.
    
    ensureDirExists(appData);
    return appData;
}

QString FileSystem::getInstancesDir() {
    QString dataDir = getLauncherDataDir();
    QDir dir(dataDir);
    QString instancesPath = dir.absoluteFilePath("instances");
    
    ensureDirExists(instancesPath);
    return instancesPath;
}

QString FileSystem::sanitizeFolderName(const QString &name) {
    QString sanitized = name;
    
    // Replace characters: / \ : * ? " < > | with _
    sanitized.replace(QRegularExpression("[/\\\\:\\*\\?\\\"<>\\|]"), "_");
    
    return sanitized.trimmed();
}

QString FileSystem::generateInstanceFolderName(const QString &modpackName) {
    QString baseName = sanitizeFolderName(modpackName);
    QDir dir(getInstancesDir());
    
    // If the base name doesn't exist, use it directly
    if (!dir.exists(baseName)) {
        return baseName;
    }
    
    // Otherwise, try with (1), (2), (3), etc.
    for (int i = 1; i < 1000; ++i) {
        QString candidateName = QString("%1 (%2)").arg(baseName).arg(i);
        if (!dir.exists(candidateName)) {
            return candidateName;
        }
    }
    
    return baseName; // Fallback
}

bool FileSystem::ensureDirExists(const QString &path) {
    QDir dir(path);
    if (!dir.exists()) {
        if (dir.mkpath(".")) {
            qDebug() << "✅ Created directory:" << path;
            return true;
        } else {
            qDebug() << "❌ Failed to create directory:" << path;
            return false;
        }
    }
    return true;
}
