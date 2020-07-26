#ifndef GETTOKEN_H
#define GETTOKEN_H

#include <QWidget>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>
class GetToken : public QWidget
{
    Q_OBJECT
public:
    explicit GetToken(QWidget *parent = 0);

    //对url进行组装和发送并将返回的数据存放在replyData中
    bool postSync(QString url, QMap<QString, QString> header, QByteArray requestData, QByteArray &replyData);


signals:

public slots:
};

#endif // GETTOKEN_H
