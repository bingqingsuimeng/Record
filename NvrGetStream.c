
//yaogang modify 20151222

#define NVR_PROTOCOL

#define PRO_TYPE_NVR		0X100//���������NVR


//�豸��Ϣ
typedef struct 
{
	u32	deviceIP; 						//�豸IP  
	u16	devicePort;						//�豸�˿� 
	char device_name[32];				//�豸����
	char device_mode[32];				//�豸�ͺ�
	u8	maxChnNum;						//���ͨ����
	u8	maxAduioNum;					//�����Ƶ��
	u8	maxSubstreamNum;				//�����������
	u8	maxPlaybackNum;					//���ط���
	u8	maxAlarmInNum;					//��󱨾�������
	u8	maxAlarmOutNum;					//��󱨾������
	u8	maxHddNum;						//���Ӳ����
	u8 	nNVROrDecoder;	//����NVR�ͽ�����--- Ծ��
	u8	reserved[15];					//Ԥ��
}PACK_NO_PADDING ifly_DeviceInfo_t;


#define CTRL_CMD_GETDEVICEINFO			CTRL_CMD_BASE+3			//??��?������?D??��
#define CTRL_CMD_LOGIN					CTRL_CMD_BASE+1			//??3����????����?
#define CTRL_CMD_ALARMUPLOADCENTER		CTRL_CMD_BASE+76		//����?����?��??DD?


typedef struct
{
	int valid;//��ʾ�ýṹ�Ƿ���Ч
	int cmd_fd;//����ͨ��SOCKET
	struct chn_info **ppchn_info;//�����NVR������ͨ����Ϣ��ָ��
	//���ü�����������ɾ����NVR������ͨ�������ٸýṹ
	//�ɹ������NVR��һ������+1���Ͽ�һ������-1
	int ref_cnt;
	//��ref_cnt == 0ʱtm��¼��ǰʱ�䣬��ʱDestroyNvrDelayTime������
	time_t tm;
	ifly_DeviceInfo_t dev_info;
	ifly_loginpara_t login;
	
	pthread_mutex_t lock;
} NVR_info;

typedef struct chn_info
{
	//private 
	u8 nvr_chn;//��ʾ���Ѿ�������NVR�ĵڼ���ͨ������������/������
	u8 sys_chn;//��ʾ��ϵͳ�ĵڼ���ͨ����������/������

	u8 eventLoopWatchVariable;//���������߳��˳�����
	pthread_t pid;//���������߳�ID
	int cap_fd;//�������ݽ���SOCKET
	u32 link_id;//���ڹر�����
	RealStreamCB pStreamCB;//���ݻص�
	unsigned int dwContext;//�ص�����
	int video_width;//������
	int video_height;//������
	//
	NVR_info *pnvr_info;
	
	pthread_mutex_t lock;
} CHN_info;

//������Ϣͬ��
#define BufSize	(1024)
static u8 *pbuf_snd = NULL;
static u8 *pbuf_rcv = NULL;
static volatile int g_dwSyncAckLen = 0;
static pthread_mutex_t g_hSyncMutex;//ͬһʱ��ֻ����һ������Ի�
static sem_t g_hSyncSem;//�߳̽���ACK���ѷ��ͷ�

��Ƶ��ʧ����





















