初始化时要注意
g_ThreadManager.RegisterMainThread(ThreadGetID())；
g_TimerManager.Start();
这两句要先运行

#pragma pack( push, 1 )
#pragma pack( pop )

QString to char :
QString dev(QString::fromUtf8("/dev/fb0"));
dev.toUtf8().constData();

QT:
//判断是否是IP地址
static bool IsIP(QString IP) {
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(IP);
}
    
//按键添加提示语  
ui->btnMenu_Max->setToolTip("最大化");  

//QComboBox 添加多个条目
QStringList qssName;
qssName << "黑色" << "灰黑色" << "灰色" << "浅灰色" << "深灰色" << "银色" << "淡蓝色" << "蓝色";
ui->cboxStyle->addItems(qssName);
myHelper::Sleep(300);
ui->cboxStyle->setCurrentIndex(3);

请选定一个解码器的一个通道，当报警触发时该通道将会被单画面放大。


逻辑层设计
biz_config:  
	模块功能：设备各种限制值，配置，信息，将配置发生改变时写入 flash。
	interface:
		init()
		get()
		set()
	thread: flash 写入线程
		
biz_dev:
	class CDevManager
	class CDev
	class CDec
	class CNvr
			
biz_net:
	模块功能：管理网络通信，维护网络连接心跳。
		eg: 升级模块依赖网络模块，当网络故障时要回调通知升级模块。
biz_upgrade: 设备升级
				
biz_preview:
	
biz_playback:
	
biz_alarm: 	集中接收、显示、清除报警信息。
			记录报警联动列表，具体的联动处理函数在设备管理里面的设备类
			
note:
	改变IP地址后：
		一、需要把子网掩码、网关、DNS在次设置一次（即便这三个没有修改）否则无法加入组播组
		二、而且之前创建的socket（回应搜索组播）不需要关闭后在次创建
			
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

摇杆 AD
电阻
红白	1728		公共
蓝白	1390-1960	纵向
绿白	1390-1960	横向
黑白	1390-1960	Z轴向

J15 
udhcpc -i eth0

page_dev_mgt  设备管理
电视墙配置（系统设置）
电视墙
预览+摇杆+雨刷
回放
报警管理
升级
 

git checkout --

冲突解决办法
1、直接编辑冲突文件
2、git add -u
3、git commit -m "xxx" //提交
4、git push origin master


雨刷 TLClient
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

		
  	
预览


回放


文件下载
  	
待完善功能：
1、电视墙可以添加 轮巡型解码器作为 一个屏幕
2、在电视墙界面中 轮巡型解码器 可以拖 NVR



./upgrade_pack -h 0x2000000 -m 0x40000000 -b 0 0x60000 u-boot.bin -k 0xc0000 0x3c0000 uImage_3531 -frcramfs 0x480000 0x1160000 rootfs_ext2.gz -t 0x15e0000 0x100000 container.bin -e 0x60000 0x20000 logo_start.jpg -u NR3116