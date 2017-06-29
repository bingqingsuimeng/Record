	VD_BOOL  m_Started;	//��ʼ����ɣ�������
	CMutex m_Mutex;
	u8 m_MaxSensorNum;	//������������Ŀ
	u8 m_MaxIpcChn;		//ͨ����Ŀ
	
	CTimer **pp_ChnRequestSnapTimer;	//ÿ��ͨ��һ��
	volatile u32 *p_ChnReqTypeMask;	//����ץͼ��ǣ�ץͼ����
	
	//�Ƿ�Ҫ�ϴ���������ʱ�̵�ǰ��ʱ��������ͼƬ
	//����m_MaxIpcChn��������ÿһλָʾ����Դ
	u32 * p_UploadPreRec_Sensor;//��Чλ��: m_MaxSensorNum
	u32 * p_UploadPreRec_IPCMD;
	u32 * p_UploadPreRec_IPCEXT;
	//
	time_t *p_ChnTimeLast;//ͨ����ʱ������ʱ��
	time_t *p_ChnRecSensor;//¼������-- �¼�-- sersor������ʱ��
	time_t *p_ChnRecIPCMD;//¼������-- �¼�-- IPCMD������ʱ��
	time_t *p_ChnRecIPCEXT;//¼������-- �¼�-- IPCEXT������ʱ��
	time_t *p_ChnSGSensor;//�ϴ�����-- ����-- sersor������ʱ��
	time_t *p_ChnSGIPCMD;//�ϴ�����-- ����-- IPCMD������ʱ��
	time_t *p_ChnSGIPCEXT;//�ϴ�����-- ����-- IPCEXT������ʱ��
	EM_ALARM_STATUS *p_SensorStatus;	//��������״̬
	EM_ALARM_STATUS *p_IPCMDStatus;	//IPC�ƶ����״̬
	EM_ALARM_STATUS *p_IPCEXTStatus;	//IPC�ⲿ����״̬
	
	CMutex *p_ChnMutex;	//ͨ����Ϣ��
	//���ڱ���
	
	volatile u32 m_ChnSensorMask;//ÿһλ��ʾһ��������
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
	EM_ALARM_NONE = 0,	// 0 �ޱ�������ʼ״̬���������������״̬
	EM_ALARM_TIGGER,	// 1 ��������
	EM_ALARM_ING,		// 2 ������
	EM_ALARM_END,		// 3 �������
	EM_ALARM_STILL,	// 4	�����ӳ���¼
	EM_ALARM_MAX,
} EM_ALARM_STATUS;


typedef enum
{
	//GUI
	TypeTime = 0,		// 0 ��ʱ-¼������--ץͼ����
	TypeManualTEST,	// 1 ����ͼ���ϴ�--���ƽ̨--���Ա���
	TypeManualMAINTAIN,	// 2 ����ͼ���ϴ�
	TypeManualACCEPT,	// 3 ���չ����ϴ�
	TypePreSnap,		// 4 Ԥ¼
	TypeDaily,	// 5 �ճ�
	TypeAlarm=TypeDaily,
	TypeMotionDet,	// 6 �ƶ����
	TypeAlarmSensor,	// 7 ���ش���������
	TypeAlarmIPCEXT,	// 8 IPC�ⲿ����
	TypeSnapMax,
} EM_SNAP_TYPE;

���������ͱ��������Ҫ�ϴ���Ϣ�����ƽ̨
����ֱ����BizData.cpp

//һ�鱨����Ϣ������GUID������ͬ���ϴ����ƽ̨��һ���ֶ�
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
����AlarmChn������ͨ��msg.chn����ͼ���ϴ�

testUI.cpp EM_DVR_STARTUP

u8 normoal_exit;// 1: ϵͳ�����ػ�0: �쳣�˳�
ϵͳ�ػ�
E7 B3 BB
E7 BB 9F
E5 85 B3
E6 9C BA