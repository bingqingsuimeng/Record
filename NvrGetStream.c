
//yaogang modify 20151222

#define NVR_PROTOCOL

#define PRO_TYPE_NVR		0X100//搜索并添加NVR


//设备信息
typedef struct 
{
	u32	deviceIP; 						//设备IP  
	u16	devicePort;						//设备端口 
	char device_name[32];				//设备名称
	char device_mode[32];				//设备型号
	u8	maxChnNum;						//最大通道数
	u8	maxAduioNum;					//最大音频数
	u8	maxSubstreamNum;				//最大子码流数
	u8	maxPlaybackNum;					//最大回放数
	u8	maxAlarmInNum;					//最大报警输入数
	u8	maxAlarmOutNum;					//最大报警输出数
	u8	maxHddNum;						//最大硬盘数
	u8 	nNVROrDecoder;	//区别NVR和解码器--- 跃天
	u8	reserved[15];					//预留
}PACK_NO_PADDING ifly_DeviceInfo_t;


#define CTRL_CMD_GETDEVICEINFO			CTRL_CMD_BASE+3			//??μ?éè±?D??￠
#define CTRL_CMD_LOGIN					CTRL_CMD_BASE+1			//??3ìμ????üá?
#define CTRL_CMD_ALARMUPLOADCENTER		CTRL_CMD_BASE+76		//±¨?ˉé?′??DD?


typedef struct
{
	int valid;//标示该结构是否有效
	int cmd_fd;//命令通道SOCKET
	struct chn_info **ppchn_info;//保存该NVR的所有通道信息的指针
	//引用计数，用于在删除该NVR的所有通道后，销毁该结构
	//成功申请该NVR的一个码流+1，断开一个码流-1
	int ref_cnt;
	//当ref_cnt == 0时tm记录当前时间，延时DestroyNvrDelayTime后销毁
	time_t tm;
	ifly_DeviceInfo_t dev_info;
	ifly_loginpara_t login;
	
	pthread_mutex_t lock;
} NVR_info;

typedef struct chn_info
{
	//private 
	u8 nvr_chn;//标示是已经连接上NVR的第几个通道，不区分主/子码流
	u8 sys_chn;//标示是系统的第几个通道，区分主/子码流

	u8 eventLoopWatchVariable;//码流接收线程退出条件
	pthread_t pid;//码流接收线程ID
	int cap_fd;//码流数据接收SOCKET
	u32 link_id;//用于关闭码流
	RealStreamCB pStreamCB;//数据回调
	unsigned int dwContext;//回调参数
	int video_width;//码流宽
	int video_height;//码流高
	//
	NVR_info *pnvr_info;
	
	pthread_mutex_t lock;
} CHN_info;

//网络消息同步
#define BufSize	(1024)
static u8 *pbuf_snd = NULL;
static u8 *pbuf_rcv = NULL;
static volatile int g_dwSyncAckLen = 0;
static pthread_mutex_t g_hSyncMutex;//同一时刻只能有一处网络对话
static sem_t g_hSyncSem;//线程接收ACK后唤醒发送方

视频丢失报警





















