在监控领域中，一般输出设备的图形用户界面内容包括： 
  后端 OSD：显示画面分割线、通道号、时间等信息，用以界定多画面显示布局。 
  GUI 界面：包括各种菜单、进度条等元素，用户通过操作 GUI 界面进行设备配置。 
  鼠标：提供更方便易用的界面菜单操作方式。

叠加图形层管理:
	Linux Framebuffer是一个子设备号对应一个显卡，HiFB 则是一个子设备号对应一个叠
加图形层，HiFB 可以管理多个叠加图形层，具体个数和芯片相关。
	对于Hi3535芯片，HiFB最多可以管理4个叠加图形层：图形层0～图形层3（最后一个层为鼠
标层） ，对应的设备文件依次为/dev/fb0~/dev/fb3。Hi3535芯片支持3个输出设备上可以叠加图形
层：高清输出设备0（简称HD0） 、高清输出设备1（简称HD1） 、标清输出设备0（简称
SD0）

eg: HD0 上有视频层、G0，则叠加顺序
从下到上依次为：视频层，G0，G3。(G3 为鼠标层)

注：为了显示图形层，使用Hi3535芯片的用户必须先配置并启动输出设备（通过VOU模块的接
口） ，最后通过HiFB模块接口操作图像层使之显示

注：上文提到的三个分辨率：画布分辨率（即用户绘制buffer的分辩率） 、显存分辨率、屏幕显示分
辨率。绘图内容从用户绘制buffer到显示buffer的过程支持缩放，也支持抗闪烁；而从显示
buffer到显示设备的过程不支持缩放，也不支持抗闪，所以显存分辨率与屏幕显示分辨率总是相
同。


mount -o nolock 192.168.1.32:/mnt/nfs /mnt
cd /mnt
export QT_QWS_DISPLAY="linuxFB:/dev/fb0"
export QT_QWS_FONTDIR=/mnt/qt4.8.6/lib/fonts
export LD_LIBRARY_PATH=/mnt/qt4.8.6/lib:$LD_LIBRARY_PATH


QString to char :
QString dev = QLatin1String("/dev/fb0");
dev.toUtf8().constData()

整个应用背景
QWSServer::setBackground(QColor(0, 0, 0, 0xff));

窗口透明 0~1 0全透 1不透
setWindowOpacity(0.5);

显示中文
#include <QTextCodec>  //添加头文件
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale()); //设置编码
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    MainWindow w;
    w.show();
    
    return a.exec();
}
在需要中文的地方 ui->pushButton->setText(tr("新窗口"));

常用的数值比较和调整的函数在 <QtGlobal>
eg: 
	int myValue = 10;
	int minValue = 2;
	int maxValue = 6;
	
	int boundedValue = qBound(minValue, myValue, maxValue);
	// boundedValue == 6
        
        

