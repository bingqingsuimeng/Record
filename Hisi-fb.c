�ڼ�������У�һ������豸��ͼ���û��������ݰ����� 
  ��� OSD����ʾ����ָ��ߡ�ͨ���š�ʱ�����Ϣ�����Խ綨�໭����ʾ���֡� 
  GUI ���棺�������ֲ˵�����������Ԫ�أ��û�ͨ������ GUI ��������豸���á� 
  ��꣺�ṩ���������õĽ���˵�������ʽ��

����ͼ�β����:
	Linux Framebuffer��һ�����豸�Ŷ�Ӧһ���Կ���HiFB ����һ�����豸�Ŷ�Ӧһ����
��ͼ�β㣬HiFB ���Թ���������ͼ�β㣬���������оƬ��ء�
	����Hi3535оƬ��HiFB�����Թ���4������ͼ�β㣺ͼ�β�0��ͼ�β�3�����һ����Ϊ��
��㣩 ����Ӧ���豸�ļ�����Ϊ/dev/fb0~/dev/fb3��Hi3535оƬ֧��3������豸�Ͽ��Ե���ͼ��
�㣺��������豸0�����HD0�� ����������豸1�����HD1�� ����������豸0�����
SD0��

eg: HD0 ������Ƶ�㡢G0�������˳��
���µ�������Ϊ����Ƶ�㣬G0��G3��(G3 Ϊ����)

ע��Ϊ����ʾͼ�β㣬ʹ��Hi3535оƬ���û����������ò���������豸��ͨ��VOUģ��Ľ�
�ڣ� �����ͨ��HiFBģ��ӿڲ���ͼ���ʹ֮��ʾ

ע�������ᵽ�������ֱ��ʣ������ֱ��ʣ����û�����buffer�ķֱ��ʣ� ���Դ�ֱ��ʡ���Ļ��ʾ��
���ʡ���ͼ���ݴ��û�����buffer����ʾbuffer�Ĺ���֧�����ţ�Ҳ֧�ֿ���˸��������ʾ
buffer����ʾ�豸�Ĺ��̲�֧�����ţ�Ҳ��֧�ֿ����������Դ�ֱ�������Ļ��ʾ�ֱ���������
ͬ��


mount -o nolock 192.168.1.32:/mnt/nfs /mnt
cd /mnt
export QT_QWS_DISPLAY="linuxFB:/dev/fb0"
export QT_QWS_FONTDIR=/mnt/qt4.8.6/lib/fonts
export LD_LIBRARY_PATH=/mnt/qt4.8.6/lib:$LD_LIBRARY_PATH


QString to char :
QString dev = QLatin1String("/dev/fb0");
dev.toUtf8().constData()

����Ӧ�ñ���
QWSServer::setBackground(QColor(0, 0, 0, 0xff));

����͸�� 0~1 0ȫ͸ 1��͸
setWindowOpacity(0.5);

��ʾ����
#include <QTextCodec>  //���ͷ�ļ�
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale()); //���ñ���
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    MainWindow w;
    w.show();
    
    return a.exec();
}
����Ҫ���ĵĵط� ui->pushButton->setText(tr("�´���"));

���õ���ֵ�ȽϺ͵����ĺ����� <QtGlobal>
eg: 
	int myValue = 10;
	int minValue = 2;
	int maxValue = 6;
	
	int boundedValue = qBound(minValue, myValue, maxValue);
	// boundedValue == 6
        
        

