#include "speech2text.h"

Speech::Speech(QWidget *parent) : QWidget(parent)
{

}


//需要调用postSync函数两次，发起两次请求，第一次获取Token；第二次通过token获取识别文本
/**
 * @brief Speech::getText
 * @param fileName   录制好的语音文件
 * @return   识别出的字符串
 */
QString Speech::getText(QString fileName)
{
     QString accessToken;
    //组装获取token的url
    QString tokenUrl = QString(baiduToken).arg(client_id).arg(client_secret);
    QMap<QString , QString> header;
    header.insert(QString("Content-Type"), QString("audio/pcm;rate=16000"));

    QByteArray requestData; //要发送给服务器的数据
    QByteArray replyData;  //服务器返回的数据

    GetToken m_GetToken;
    bool result = m_GetToken.postSync(tokenUrl, header, requestData, replyData);
    if(result)
    {
        QString key = "access_token";
        accessToken = getJsonValue(replyData, key);
        qDebug() << accessToken;
    }
    else
    {
         this->close();
    }

    //识别语音
    //组合url
    QString Speechurl = QString(baiduSpeech).arg(accessToken);
    //转换文件
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly);
    requestData = file.readAll();
    file.close();

    //再次发起请求
    bool result_1 = m_GetToken.postSync(Speechurl, header, requestData, replyData);
    if(result_1)
    {
        QString key = "result";
        QString text = getJsonValue(replyData, key);
        return text;
    }
    else
    {
         QMessageBox::warning(NULL, "识别提示", "识别失败");
    }
    return "";
}



QString Speech::getJsonValue(QByteArray ba, QString key)
{
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(ba, &parseError);
    if(parseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            //jsonDocument 转换成 Json对象
            QJsonObject jsonObj = jsonDocument.object();

            //监测json对象中是否有所传入的键
            if(jsonObj.contains(key))
            {
                QJsonValue jsonvalue = jsonObj.value(key);
                 //如果是字符串
                if(jsonvalue.isString())
                {
                    return jsonvalue.toString();
                }
                //由于语音识别返回的Json数据中result对应的内容是一个数组，而且参考文档说优先第一个
                else if(jsonvalue.isArray())
                {
                    QJsonArray arr = jsonvalue.toArray();
                    QJsonValue jv = arr.at(0);
                    return jv.toString();
                }
            }
        }
        return "";
    }
}
