#include "globals.h"
//#include <QApplication>
#include <QGuiApplication>
#include <QString>
#include <QDir>
#include <QDebug>

#include "stdio.h"

QString Globals::m_ApplicationUsage = "PRIVATE";
QString Globals::m_resourcePath;

/**
 * @brief logFile
 */
FILE * logFile = NULL;

Globals::Globals()
{

}

Globals::~Globals()
{

}

void Globals::initPath(){
#ifdef Q_OS_ANDROID
    m_resourcePath = "assets:/";
#endif
#ifdef WIN32

    QDir dir(qApp->applicationDirPath() +"/texture"); //we have an installed version
    if (dir.exists())
             m_resourcePath = qApp->applicationDirPath() + "/";
    else m_resourcePath = qApp->applicationDirPath() + "/../../Enigma/"; //we are running from QtCreator
#else
    QDir dir = QDir(qApp->applicationDirPath() + "/../Enigma/");
    m_resourcePath = dir.absolutePath() + "/";
#endif
}



QString Globals::resourcePath()
{
    if(m_resourcePath.isEmpty())
        initPath();
    return m_resourcePath;
}

QString Globals::texturePath()
{
    return resourcePath() + "texture/";
}

QString Globals::modelPath()
{
    return resourcePath() + "models/";
}

QString Globals::soundPath()
{
    return resourcePath() + "sound/";
}

void Globals::setApplicationUsage(const QString &usage)
{
  qDebug() << "Globals::setApplicationUsage called. Setting mode: " << usage;
  m_ApplicationUsage =  usage;
}

QUrl Globals::qmlResourcePath() const
{
#ifdef Q_OS_ANDROID
        return resourcePath();
#else
        return QUrl::fromLocalFile(resourcePath());
#endif
}
QUrl Globals::qmlTexturePath() const
{
#ifdef Q_OS_ANDROID
        return texturePath();
#else
        return QUrl::fromLocalFile(texturePath());
#endif
}

QString Globals::cppResourcePath() const
{
    return "file://" + resourcePath();
}

QString Globals::applicationUsage() const
{
    return m_ApplicationUsage;
}



void enigmaMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(logFile, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(logFile, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(logFile, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(logFile, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(logFile, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        fflush(logFile);
        abort();
    }
    fflush(logFile);
}

bool setGlobalMessageHandler(const char *logFileName){
    logFile = fopen(logFileName, "w");
    if(logFile){
        qInstallMessageHandler(enigmaMessageOutput);
        return true;
    }else return false;
}

