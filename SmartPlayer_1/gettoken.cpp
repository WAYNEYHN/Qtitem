#include "gettoken.h"

GetToken::GetToken(QWidget *parent) : QWidget(parent)
{

}

/**
 * @brief GetToken::postSync
 * @param url
 * @param header
 * @param requestData 要发送给服务器的数据
 * @param replyData 服务器返回的数据
 * @return
 */
bool GetToken::postSync(QString url, QMap<QString, QString> header, QByteArray requestData, QByteArray &replyData)
{
    //发送请求的对象
    QNetworkAccessManager manager;

    //请求对象
    QNetworkRequest request;
    request.setUrl(url);
    QMapIterator<QString, QString> it(header);
    while(it.hasNext())
    {
        it.next();
        request.setRawHeader(it.key().toLatin1(),it.value().toLatin1());
    }


    QNetworkReply *reply = manager.post(request, requestData);

    QEventLoop l;
    connect(reply, &QNetworkReply::finished, &l, &QEventLoop::quit);
    l.exec();   //死循环， reply发出信号，结束循环

    if(reply != nullptr&& reply->error() == QNetworkReply::NoError)
    {
        replyData = reply->readAll();  //读取服务器返回数据
        return true;
    }
    else
    {
        qDebug() << "请求失败";
        return false;
    }

}
