#include "logger.h"

Logger::Logger(QObject *parent) :
    QObject(parent)
{
}

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("(%1) ").arg(dt);

    switch (type)
    {
        case QtDebugMsg:
            txt += QString("[Debug] \t %1").arg(msg);
            fprintf(stdout, "%s\n", txt.toAscii().constData());
            break;
        case QtWarningMsg:
            txt += QString("[Warning] \t %1").arg(msg);
            fprintf(stderr, "%s\n", txt.toAscii().constData());
            break;
        case QtCriticalMsg:
            txt += QString("[Critical] \t %1").arg(msg);
            fprintf(stderr, "%s\n", txt.toAscii().constData());
            break;
        case QtFatalMsg:
            txt += QString("[Fatal] \t %1").arg(msg);
            fprintf(stderr, "%s\n", txt.toAscii().constData());
            abort();
            break;
    }

#ifdef LOG_TO_FILE
    QFile outFile("log.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream textStream(&outFile);
    textStream << txt << endl;
#endif

    fflush(stdout);
    fflush(stderr);
}

void Logger::install()
{

#ifdef LOG_TO_FILE
    QFile outFile("LogFile.log");
    outFile.remove();
#endif
    qInstallMessageHandler(customMessageHandler);
}
