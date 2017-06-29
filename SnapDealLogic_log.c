	VD_BOOL  m_Started;	//初始化完成，服务开启
	CMutex m_Mutex;
	u8 m_MaxSensorNum;	//本机传感器数目
	u8 m_MaxIpcChn;		//通道数目
	
	CTimer **pp_ChnRequestSnapTimer;	//每个通道一个
	volatile u32 *p_ChnReqTypeMask;	//请求抓图标记，抓图类型
	
	//是否要上传报警触发时刻到前置时间点的所有图片
	//共有m_MaxIpcChn个变量，每一位指示报警源
	u32 * p_UploadPreRec_Sensor;//有效位数: m_MaxSensorNum
	u32 * p_UploadPreRec_IPCMD;
	u32 * p_UploadPreRec_IPCEXT;
	//
	time_t *p_ChnTimeLast;//通道定时最后操作时间
	time_t *p_ChnRecSensor;//录像配置-- 事件-- sersor最后操作时间
	time_t *p_ChnRecIPCMD;//录像配置-- 事件-- IPCMD最后操作时间
	time_t *p_ChnRecIPCEXT;//录像配置-- 事件-- IPCEXT最后操作时间
	time_t *p_ChnSGSensor;//上传中心-- 报警-- sersor最后操作时间
	time_t *p_ChnSGIPCMD;//上传中心-- 报警-- IPCMD最后操作时间
	time_t *p_ChnSGIPCEXT;//上传中心-- 报警-- IPCEXT最后操作时间
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
	
	
typedef enum
{
	TypeSensor = 0,	// 0
	TypeMD,	// 1
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
	//GUI
	TypeTime = 0,		// 0 定时-录像配置--抓图参数
	TypeManualTEST,	// 1 测试图像上传--监管平台--测试保养
	TypeManualMAINTAIN,	// 2 保养图像上传
	TypeManualACCEPT,	// 3 验收管理上传
	TypePreSnap,		// 4 预录
	TypeDaily,	// 5 日常
	TypeAlarm=TypeDaily,
	TypeMotionDet,	// 6 移动侦测
	TypeAlarmSensor,	// 7 本地传感器报警
	TypeAlarmIPCEXT,	// 8 IPC外部报警
	TypeSnapMax,
} EM_SNAP_TYPE;

报警触发和报警解除需要上传消息到监管平台
处理直接在BizData.cpp

//一组报警消息的所有GUID编码相同，上传监管平台的一个字段
	s32 *p_GUID_Sensor;
	s32 *p_GUID_IPCMD;
	s32 *p_GUID_IPCEXT;

sprintf(msg.note, "%s%02d%s, %s%02d%s", \
				GetParsedString("&CfgPtn.Local"),
				AlarmChn,
				GetParsedString("&CfgPtn.Alarm1"),
				GetParsedString("&CfgPtn.Channel"), 
				msg.chn,
				GetParsedString("&CfgPtn.LinkPicUpload")
				);
本机AlarmChn报警，通道msg.chn联动图像上传

testUI.cpp EM_DVR_STARTUP

u8 normoal_exit;// 1: 系统正常关机0: 异常退出
系统关机
E7 B3 BB
E7 BB 9F
E5 85 B3
E6 9C BA