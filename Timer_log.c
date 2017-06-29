int BizReloadHdd(SBizStoreDevManage *psStorge)

	VD_BOOL  m_Started;	//初始化完成，服务开启
	CMutex m_Mutex;
	u8 m_MaxSensorNum;	//本机传感器数目
	u8 m_MaxIpcChn;		//通道数目
	
	CTimer **pp_ChnRequestSnapTimer;	//每个通道一个
	volatile u32 *p_ChnReqTypeMask;	//请求抓图标记，抓图类型
	
	//是否要上传报警触发时刻到前置时间点的该通道所有图片
	//共有m_MaxIpcChn个变量，每一位指示报警源
	u32 * p_UploadPreRec_Sensor;//有效位数: m_MaxSensorNum
	u32 * p_UploadPreRec_IPCMD;
	u32 * p_UploadPreRec_IPCEXT;
	//是否要上传当前时刻该通道所有图片
	//共有m_MaxIpcChn个变量，每一位指示报警源
	u32 * p_UploadCur_Sensor;//有效位数: m_MaxSensorNum
	u32 * p_UploadCur_IPCMD;
	u32 * p_UploadCur_IPCEXT;
	//
	time_t *p_ChnTimeLast;//通道定时最后操作时间
	time_t **pp_ChnRecSensor;//录像配置-- 事件-- sensor报警，chn最后保存时间[chn][sensor]
	time_t **pp_ChnRecIPCMD;//录像配置-- 事件-- IPCMD报警，chn最后保存时间
	time_t **pp_ChnRecIPCEXT;//录像配置-- 事件-- IPCEXT报警，chn最后保存时间
	time_t **pp_ChnSGSensor;//上传中心-- 报警-- sensor报警，chn最后上传时间
	time_t **pp_ChnSGIPCMD;//上传中心-- 报警-- IPCMD报警，chn最后上传时间
	time_t **pp_ChnSGIPCEXT;//上传中心-- 报警-- IPCEXT报警，chn最后上传时间
	EM_ALARM_STATUS *p_SensorStatus;	//本机报警状态
	EM_ALARM_STATUS *p_IPCMDStatus;	//IPC移动侦测状态
	EM_ALARM_STATUS *p_IPCEXTStatus;	//IPC外部报警状态
	
	CMutex *p_ChnMutex;	//通道信息锁
	//用于报警
	
	volatile u32 m_ChnSensorMask;//每一位表示一个传感器
	volatile u32 m_ChnIPCMDMask;
	volatile u32 m_ChnIPCEXTMask;
	sTimeRange *p_SensorRange;
	sTimeRange *p_IPCMDRange;
	sTimeRange *p_IPCEXTRange;

	char PoliceID[TEXTLEN];
	char PassWord[TEXTLEN];


typedef enum
{
	TypeSensor = 0,	// 0
	TypeMD,			// 1
	TypeIPCEXT,		// 2
	TypeAlarmMax,
} EM_ALARM_TYPE;

typedef enum
{
	EM_ALARM_NONE = 0,	// 0 无报警，初始状态和整个报警活动结束状态
	EM_ALARM_TIGGER,	// 1 报警触发
	EM_ALARM_ING,		// 2 报警中
	EM_ALARM_END,		// 3 报警解除
	EM_ALARM_STILL,	// 4	报警延迟延录
	EM_ALARM_MAX,
} EM_ALARM_STATUS;

typedef enum
{
	//upload
	TypeManualTEST = 0,	// 0 测试图像上传--监管平台--测试保养
	TypeManualMAINTAIN,	// 1 保养图像上传
	TypeManualACCEPT,	// 2 验收管理上传
	TypeDaily,			// 3 日常
	//record
	TypePreSnap,			// 4 预录
	TypeTime,			// 5 定时-录像配置--抓图参数
	TypeManual,			// 6 手动截图
	//upload & record
	TypeAlarmSensor,		// 7 本地传感器报警
	TypeMotionDet,		// 8 移动侦测
	TypeAlarmIPCEXT,		// 9 IPC外部报警
	TypeSnapMax,
} EM_SNAP_TYPE;
	
int UploadPic(EM_SNAP_TYPE type, u8 AlarmChn, u8 IPCChn, struct timeval *ptv, char *SnapData, u32 DataSize);
s32 upload_sg_proc(SSG_MSG_TYPE *pmsg, time_t time, char *SnapData, unsigned int DataSize);


通道M	本机N报警	联动图像上传
		IPC N报警
		IPC N移动侦测
		
CfgPtn.Channel	CfgPtn.Local CfgPtn.Alarm1	CfgPtn.LinkPicUpload
				CfgPtn.Motion
		
strcpy(msg.note, GetParsedString("&CfgPtn.Motion"));
	
	
//yaogang modify 20141209
//深广平台参数
typedef struct
{
	char AgentID[100];
	char CenterIP[100];
	u8 RunEnable;//运行状态启用
	u8 AlarmEnable;//报警联动启用
	u8 DailyPicEnable;//日常图像启用
} SBizSGParam;

//报警图片配置，每个报警通道一个结构
//m路本地，n路IPC外部报警(m 16--n 32)
typedef struct
{
	u8 PreTimes;		//前置时间
	u8 Interval;		//间隔时间
	u8 StillTimes;		//延录时间
	u8 AlarmInput;	//输入端子
	u32 IpcChn;		//每个IPC通道各占一位，0xffff ffff表示所有通道
} SBizAlarmPicCFG;

//日常图片配置
typedef struct
{
	u8 TimeEnable;	//定时上传时间使能
	u8 hour;
	u8 min;
	u8 sec;
} SBizSGTime;

typedef struct
{
	SBizSGTime Time1;		//定时上传时间1 
	SBizSGTime Time2;		//定时上传时间2
	u32 IpcChn1;		//每个IPC通道各占一位，0xffff ffff表示所有通道
	u32 IpcChn2;		//每个IPC通道各占一位，0xffff ffff表示所有通道
} SBizDailyPicCFG;

#if 0
typedef struct
{
	u8 TimeEnable;	//定时上传时间使能
	u8 hour;
	u8 min;
	u8 sec;
} SBizSGTime;
typedef struct
{
	u8 PreTimes;		//前置时间
	u8 Interval;		//间隔时间
	u8 StillTimes;		//延录时间
	u8 AlarmInput;	//输入端子
	u32 IpcChn;		//16个IPC通道各占一位，0x1000 0000表示所有通道
} SBizAlarmPicCFG;
typedef struct
{
	SBizSGTime Time1;		//定时上传时间1 
	SBizSGTime Time2;		//定时上传时间2
	u32 IpcChn1;		//16个IPC通道各占一位，0x1000 0000表示所有通道
	u32 IpcChn2;		//16个IPC通道各占一位，0x1000 0000表示所有通道
} SBizDailyPicCFG;
typedef struct
{
	char AgentID[100];
	char CenterIP[100];
	u8 RunEnable;//运行状态启用
	u8 AlarmEnable;//报警联动启用
	u8 DailyPicEnable;//日常图像启用
	SBizAlarmPicCFG SAlarmPicParam;//报警图片配置参数
	SBizDailyPicCFG SDailyPicParam;//日常图片配置参数
} SBizSGParam;
#endif

//开机设置时间
ModSysComplexInit()
	cur = read_rtc(1);
	printf("utc : system current time : %d, date : %s\n", (int)cur, ctime(&cur));	
	stime(&cur);
	
//设置时间
void CPageBasicConfigFrameWork::OnSave1()
	BizSysComplexDTSet
		SysComplexDTSet
			ModSysComplexDTSet
				modSysCmplx_SetTime
					write_rtc(t,1);//set rtc
//刷新时间
modSysCmplx_UpTimeThreadFunc()

//自动同步时间服务器
PageBasicConfigFrameWork.cpp
	keepsynchronizing() //thread		
SBizSystemPara bizSysPara;
	bizSysPara.nSyscCheck	//自动同步时间服务器
