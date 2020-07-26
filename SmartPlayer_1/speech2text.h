#ifndef SPEECH_H
#define SPEECH_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include "gettoken.h"
//获取token相关
const QString baiduToken = "https://openapi.baidu.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2";
const QString client_id = "QzApbGoPq2wwTm2mVWQoVpkG";
const QString client_secret = "RYO4xCGQ9gZaYr68pZACgfs4W6CEGYvE";

//语音识别相关
const QString baiduSpeech = "http://vop.baidu.com/server_api?cuid=liuyu&token=%1&dev_pid=1537";
class Speech : public QWidget
{
    Q_OBJECT
public:
    explicit Speech(QWidget *parent = 0);

    QString getText(QString fileName);

    QString getJsonValue(QByteArray ba, QString key);
signals:

public slots:
};

#endif // SPEECH_H
