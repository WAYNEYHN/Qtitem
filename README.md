# README

1. ##### 项目实现的功能：

   1. 一键实现一次性的语音聊天
   2. 文本转语音
   3. 开始聊天
   4. 自动聊天

2. ##### 编译工具：Qt Creator 4.2.1

3. ##### 依赖的库：

   1. libeay32.dll、ssleay32.dll（两个文件已经添加到debug目录中）

4. ##### 具体操作：

   1. 按下**“开始说话”按钮**开始录制音频， 松开发送音频进行识别文本，之后发送给图灵机器人，并语音输出对话内容
   2. 按下**“文本转语音”按钮**发送textedit里的文本信息，并进行语音输出
   3. 按下**“开始聊天”按钮**发送textedit的内容，然后进行机器人对话的语音输出
   4. 按下**“自动聊天”按钮**后，说带关键字‘小’的话，“ding~”表示开始对话，“dong~”表示一次对话完成需要再次唤醒，如果唤醒词中带有“再见”则退出自动聊天）

5. ##### 其他注意事项

   1. 如果运行是语音无法播放，程序输出如下错误

   ```
    DirectShowPlayerService::doRender: Unresolved error code 0x80040266
   ```

   ​			请下载并安装  LAVFilters：https://github.com/Nevcairiel/LAVFilters/releases解决

这是一个智能音箱的学校实训项目，通过调用百度智能语音和图灵机器人的API实现以下功能由于是在windows平台进行开发，所以没有使用snowboy实现智能唤醒，所以通过比较取巧的语音识别+字符串对比实现

# 开发中的问题

1. 网络请求发送报错如下

   ```
   qt.network.ssl: QSslSocket: cannot call unresolved function SSLv23_client_method
   ```

   解决方案：将G:\QT-opensource\Tools\mingw530_32\opt\bin目录下的 **libeay32.dll和ssleay32dll** copy到项目.exe同级目录下或者放到Qt的bin目录下

2. 在播放语音合成模块语音的时候出现

   ```
    DirectShowPlayerService::doRender: Unresolved error code 0x80040266
   ```

   解决方案：下载并安装  LAVFilters：https://github.com/Nevcairiel/LAVFilters/releases解决

3. 录音时出现错误：未报错，经上网查询是录音设备不支持设置的格式
       进行了一个相近格式的转换

4. 设置录音时间时出错

   ​        QTimer，QEventloop在一起实现一个定时关闭录音的系统

5. 使用QMediaPlay类播放Wav文件时出现如下问题

   ```
   DirectShowPlayerService::doSetUrlSource: Unresolved error code 0x80040216 ()
   ```

   解决方案：创建QSound对象以播放