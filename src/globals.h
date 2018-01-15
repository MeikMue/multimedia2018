#ifndef GLOBALS_H
#define GLOBALS_H


#include <QString>
#include <QObject>
#include <QUrl>

#ifdef WIN32
  //#define M_PI 3.1415926
#endif

/**
 * @brief setGlobalMessageHandler redirects all qDebug output to fileName
 * @param logFileName
 */

bool setGlobalMessageHandler(const char * logFileName);

class Globals: public QObject
{
 Q_OBJECT
    Q_PROPERTY(int timeOut READ timeOut WRITE setTimeOut NOTIFY timeOutChanged)

public:
    Globals();
    ~Globals();

    static QString resourcePath();
    static QString texturePath();
    static QString modelPath();
    static QString soundPath();

    /**
     * @brief setApplicationUsage
     * @param usage  Supported usage strings: EXHIBITION, PRIVATE, AUTO_ONLY
     */
    void setApplicationUsage(const QString& usage);

    int timeOut() const
    {
        return m_timeOut;
    }

public slots:
    QUrl qmlResourcePath() const;
    QUrl qmlTexturePath() const;
    QString cppResourcePath() const;

    /**
     * @brief applicationUsage Return usage of application.
     * Supported usage strings: EXHIBITION, PRIVATE, AUTO_ONLY
     * default: PRIVATE
     * @return usage string
     */
    QString applicationUsage() const;


    void setTimeOut(int timeOut)
    {
        if (m_timeOut == timeOut)
            return;

        m_timeOut = timeOut;
        emit timeOutChanged(m_timeOut);
    }

signals:
    void timeOutChanged(int timeOut);

private:
    static QString m_ApplicationUsage;
    static QString m_resourcePath;
    static void initPath();
    int m_timeOut;
};

#endif // GLOBALS_H
