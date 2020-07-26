#include "robot.h"
#include "widget.h"
robot::robot(QWidget *parent) : QWidget(parent)
{

}

/**
 * @brief robot::Robot
 * @param text
 * @return
 */
QByteArray robot::Robot(QString text)//图灵机器人文本对话模块
{

    QNetworkRequest request;
    QJsonObject date=  JsonData(text);
    //组装url
    request.setUrl(QString("http://openapi.tuling123.com/openapi/api/v2"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QJsonDocument document=QJsonDocument(date);
    QByteArray byteArray = document.toJson(QJsonDocument::Indented);

    //发送请求
    QNetworkAccessManager AcceseNet;
    QNetworkReply *reply = AcceseNet.post(request, byteArray);

    //阻塞以等待服务器应答
    QEventLoop l;
    connect(reply, &QNetworkReply::finished, &l, &QEventLoop::quit);
    l.exec();   //死循环， reply发出信号，结束循环

    //如果返回不为空且请求未出错返回获取的数据在widget中解析
    if(reply != nullptr&& reply->error() == QNetworkReply::NoError)
    {
        result = reply->readAll();  //读取服务器返回数据
        return result;
    }
    else
    {
        qDebug() << "请求失败";
        return "";
    }
}


//封装Json
QJsonObject robot::JsonData(QString date)
{
    QJsonObject provideInfo;
    QJsonObject Text;
    QJsonObject Image;
    QJsonObject Info;
    QJsonObject UserLocation;
    Text.insert("text", date);
    UserLocation.insert("city","宝鸡");
    UserLocation.insert("province","陕西");
    Info.insert("location",UserLocation);
    provideInfo.insert("inputText",Text);
    provideInfo.insert("inputImage",Image);
    provideInfo.insert("selfInfo",Info);

    QJsonObject user;
    user.insert("apiKey","89056739672c4b0b9cc73bb20779b814");
    user.insert("userId","645679");


   //对要发送的Json数据进行嵌套 组装
    QJsonObject *JsonData = new QJsonObject;
    JsonData->insert("reqType",0);
    JsonData->insert("perception",provideInfo);
    JsonData->insert("userInfo",user);
    qDebug() << *JsonData;
    return *JsonData;
}


