��ʼ��ʱҪע��
g_ThreadManager.RegisterMainThread(ThreadGetID())��
g_TimerManager.Start();
������Ҫ������

#pragma pack( push, 1 )
#pragma pack( pop )

QString to char :
QString dev(QString::fromUtf8("/dev/fb0"));
dev.toUtf8().constData();

QT:
//�ж��Ƿ���IP��ַ
static bool IsIP(QString IP) {
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(IP);
}
    
//���������ʾ��  
ui->btnMenu_Max->setToolTip("���");  

//QComboBox ��Ӷ����Ŀ
QStringList qssName;
qssName << "��ɫ" << "�Һ�ɫ" << "��ɫ" << "ǳ��ɫ" << "���ɫ" << "��ɫ" << "����ɫ" << "��ɫ";
ui->cboxStyle->addItems(qssName);
myHelper::Sleep(300);
ui->cboxStyle->setCurrentIndex(3);

��ѡ��һ����������һ��ͨ��������������ʱ��ͨ�����ᱻ������Ŵ�


�߼������
biz_config:  
	ģ�鹦�ܣ��豸��������ֵ�����ã���Ϣ�������÷����ı�ʱд�� flash��
	interface:
		init()
		get()
		set()
	thread: flash д���߳�
		
biz_dev:
	class CDevManager
	class CDev
	class CDec
	class CNvr
			
biz_net:
	ģ�鹦�ܣ���������ͨ�ţ�ά����������������
		eg: ����ģ����������ģ�飬���������ʱҪ�ص�֪ͨ����ģ�顣
biz_upgrade: �豸����
				
biz_preview:
	
biz_playback:
	
biz_alarm: 	���н��ա���ʾ�����������Ϣ��
			��¼���������б�������������������豸����������豸��
			
note:
	�ı�IP��ַ��
		һ����Ҫ���������롢���ء�DNS�ڴ�����һ�Σ�����������û���޸ģ������޷������鲥��
		��������֮ǰ������socket����Ӧ�����鲥������Ҫ�رպ��ڴδ���
			
mount -o nolock 192.168.1.32:/mnt/nfs /mnt
cd /mnt/NetworkKeyboad
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/NetworkKeyboad
rmmod my_pcf8591
rmmod my_gpio_i2c
insmod my_gpio_i2c.ko
insmod my_pcf8591.ko


mount -o nolock 192.168.1.32:/mnt/nfs /mnt
cd /mnt/NetworkKeyboad
export QT_QWS_DISPLAY="linuxFB:/dev/fb0"
export QT_QWS_FONTDIR=/mnt/qt4.8.6/lib/fonts
export LD_LIBRARY_PATH=/mnt/qt4.8.6/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/NetworkKeyboad

13971587291

ҡ�� AD
����
���	1728		����
����	1390-1960	����
�̰�	1390-1960	����
�ڰ�	1390-1960	Z����

J15 
udhcpc -i eth0

page_dev_mgt  �豸����
����ǽ���ã�ϵͳ���ã�
����ǽ
Ԥ��+ҡ��+��ˢ
�ط�
��������
����
 

git checkout --

��ͻ����취
1��ֱ�ӱ༭��ͻ�ļ�
2��git add -u
3��git commit -m "xxx" //�ύ
4��git push origin master


��ˢ TLClient
enum NETDVR_PTZCONTROL {
	NETDVR_PTZ_COM_STOP = 0,
	NETDVR_PTZ_COM_MOVEUP = 1,
	NETDVR_PTZ_COM_MOVEDOWN = 2,
	NETDVR_PTZ_COM_MOVELEFT = 3,
	NETDVR_PTZ_COM_MOVERIGHT = 4,
	NETDVR_PTZ_COM_ROTATION = 5,
	NETDVR_PTZ_COM_ZOOMADD = 6,
	NETDVR_PTZ_COM_ZOOMSUBTRACT = 7,
	NETDVR_PTZ_COM_FOCUSADD = 8,
	NETDVR_PTZ_COM_FOCUSSUBTRACT = 9,
	NETDVR_PTZ_COM_APERTUREADD = 10,
	NETDVR_PTZ_COM_APERTURESUBTRACT = 11,
	NETDVR_PTZ_COM_LIGHTINGOPEN = 12,
	NETDVR_PTZ_COM_LIGHTINGCLOSE = 13,
	NETDVR_PTZ_COM_WIPERSOPEN = 14,//***************
	NETDVR_PTZ_COM_WIPERSCLOSE = 15,
	NETDVR_PTZ_COM_FAST = 16,
	NETDVR_PTZ_COM_NORMAL = 17,
	NETDVR_PTZ_COM_SLOW = 18,
	NETDVR_PTZ_COM_AUXILIARYOPEN = 19,
	NETDVR_PTZ_COM_AUXILIARYCLOSE = 20,
};

SendCommandToServer(NETDVR_PTZ_COM_WIPERSOPEN);
  	SendCommandToServer(NETDVR_PTZCONTROL ptz_cmd, BYTE aux)
  		NETDVR_PtzCtrl_t ptzCtr;
		ptzCtr.chn = nNumber;
		ptzCtr.cmd = ptz_cmd;
		ptzCtr.aux = aux;
		int nret = NETDVR_PtzControl(nHandle,&ptzCtr);

		
  	
Ԥ��


�ط�


�ļ�����
  	
�����ƹ��ܣ�
1������ǽ������� ��Ѳ�ͽ�������Ϊ һ����Ļ
2���ڵ���ǽ������ ��Ѳ�ͽ����� ������ NVR



./upgrade_pack -h 0x2000000 -m 0x40000000 -b 0 0x60000 u-boot.bin -k 0xc0000 0x3c0000 uImage_3531 -frcramfs 0x480000 0x1160000 rootfs_ext2.gz -t 0x15e0000 0x100000 container.bin -e 0x60000 0x20000 logo_start.jpg -u NR3116