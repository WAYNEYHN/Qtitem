#ifndef TEXT2SPEECH_H
#define TEXT2SPEECH_H

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include "gettoken.h"
class text2Speech : public QWidget
{
    Q_OBJECT
public:
    explicit text2Speech(QWidget *parent = 0);

    QByteArray playeText(QString text);
    QString getJsonValue(QByteArray ba, QString key);
signals:

public slots:

private:

};

#endif // TEXT2SPEECH_H
