struct RealPlayClientInfo_t
{
	unsigned char	rcv_chn; //channel
	unsigned char	streamtype; //0 main stream, 1 substream
	pFrameCallBack	pEncFrameCBFunc; //Call back function to encode
	unsigned int	dwEncFrameContent; //Context for encoder callback function to identify play reciever
	pDecFrameCallBack	pDecFrameCBFunc; //Call back function to decode
	unsigned int	dwDecFrameContent; //Context for decoder callback function to identify play reciever
	//csp modify 20130423
	unsigned char	wnd_num;
	unsigned char	wnd_index;
	unsigned char	reserved[6];
};

//sdk
struct ifly_monitor_t
{
	u8 channel;
	void* pDeviceHandle;
	struct IFLY_MediaRcvPara_t video_rcv;
	struct IFLY_MediaRcvPara_t audio_rcv;
	struct IFLY_RecordPara_t record_para;
	struct IFLY_RecordPara_t record_para2;
	struct IFLY_Snapshot_t snap_shot;
	struct ifly_monitor_t* pNext;
};


struct IFLY_MediaRcvPara_t
{
	ifly_stearmrcv_t* prcv_t;
	ifly_TCP_Stream_Req req;

	NETDVR_VideoProperty_t* p_video_property;
	NETDVR_AudioProperty_t* p_audio_property;

	CAudioPlay *pAudioPlay;

	Decoder_Handle decoder_hdr;
	hiVOICE_ADPCM_STATE_S decaudio_hdr;

#ifdef DEC_AVCDEC
	avcdYUVbuffer_s m_recoBuf;
	avcdYUVbuffer_s m_refBuf;
#endif

	BYTE bVideoDecFlag;
	BYTE bDecKeyFrameFlg;
	MutexHandle dec_lock;
	
	pFrameCallBack pFrameCB;
	u32 dwContentRaw;
	MutexHandle cb_raw_lock;
	
	pDecFrameCallBack pDecFrameCB;
	u32 dwContent;
	MutexHandle cb_dec_lock;
	
	fmt_type_t fmt;

	u8 rcv_type;

	struct IFLY_RecordPara_t *p_record_para;
	struct IFLY_Snapshot_t *p_snapshot;

	struct IFLY_RecordPara_t *p_record_para2;

	BOOL bPreviewAudioMute;

	u32 dwOldVideoFrameId;
	u32 bInterrupted;

	ifly_spspps_t  spspps;

	unsigned char* p_frmdecBuf;

	u16 wCurrFrmWidth;
	u16 wCurrFrmHeight;
	unsigned char byDeinterlacing;

	BYTE bOpened;

	//csp modify
	u16 decoder_width;
	u16 decoder_height;
};

typedef struct
{
	SOCKHANDLE	sockfd;
	u8	bStart;
	u32 linkid;
	ifly_TCP_Stream_Req req;
	void* pContent;
#if 0
	DWORD tickTimeLast;
	DWORD time;
	DWORD m_dwCount;
	BOOL first;
#endif
}ifly_stearmrcv_t;

ctrlprotocol.h
//������������ṹ
typedef struct 
{
	u8 command;							//0��Ԥ�� 1���ļ��ط� 2��ʱ��ط� 3���ļ����� 4������ 
										//5 VOIP 6 �ļ���֡���� 7 ʱ�䰴֡���� 8 ͸��ͨ��
										//9 Զ�̸�ʽ��Ӳ�� 10 ������ץͼ 11 ��·��ʱ��ط� 12 ��ʱ�������ļ�
	union		//72byte
	{
		struct
		{
			u8		chn;				//Ԥ��ͨ��
			u8		type;				//0:��������Ƶ 1����������Ƶ 2����������Ƶ
		}Monitor_t;						//Ԥ�� command = 0
		
		struct
		{
			char	filename[64];		//�طŵ��ļ�
			u32		offset;				//�ļ�ƫ��
		}FilePlayBack_t; 				//�ļ��ط� command = 1,�� command = 6
		
		struct
		{
			u8		channel;			//ͨ����
			u16		type;				//����
			u32		start_time;			//��ʼʱ��
			u32		end_time;			//��ֹʱ��
		}TimePlayBack_t ;				//ʱ��ط� command = 2,�� command = 7
		
		struct
		{
			char	filename[64];		//���ص��ļ�
			u32		offset;				//�ļ�ƫ��
			u32		size;				//�ļ���С
		}FileDownLoad_t;				//�ļ����� command = 3
		
		struct
		{
			u32		size;				//�ļ�����
			u32		verify;				//У���
			u16		version;			//�ļ��汾��
			u16		updateType;			//0:�������� 1���������
		}Update_t;						//Զ������  command = 4��
		
		//VOIP command
		u8 voipreserved;				//VOIPԤ�� command = 5��

		//͸��ͨ��
		u8 SerialPort;					//͸��ͨ�� 1-232����  2-485����	command = 8��

		//Զ�̸�ʽ��Ӳ��
		u8 formatHddIndex;				//Ҫ��ʽ����Ӳ�̺� 0��ʼ

		struct
		{
			u16		chnMask;			//ͨ���� ��λ ��ָͨ��1-16
			u16		type;				//����
			u32		start_time;			//��ʼʱ��
			u32		end_time;			//��ֹʱ��
			u16		chn17to32Mask;		//ͨ��17-32 ��λ
		}MultiTimePlayBack_t ;			//��·ʱ��ط� command = 11��12
	};
	u8	reserved[7];					//Ԥ��	
}ifly_TCP_Stream_Req;


1��Ԥ����ʼ���رա�ʹ��PrewiewHandle
2����̨����
3��¼���ѯ
4��¼��طſ�ʼ���ر�
5��¼��طſ���
6��¼�񱸷�
7��¼���ͽ������ط�
8���Խ���������ͨ��


//stream					
	C_Lock *plock4stream;//mutex
	VD_BOOL bthread_stream_running;
	VD_BOOL bthread_stream_exit;//�ⲿ�����߳��˳�
	int stream_cnt;
	int idle_cnt;//���м������߳̿���1���Ӻ��˳�
	CSemaphore sem_exit;//�ȴ�threadStreamRcv�˳��ź���
	SDev_StearmRcv_t stearm_rcv[MaxMediaLinks]; //�������ṹMaxMediaLinks
	void threadStreamRcv(uint param);
	Threadlet m_threadlet_stream_rcv;


class CMediaStream : public CObject
{
public:
	int Start();
	int Stop();
	virtual int dealFrameFunc(FRAMEHDR *pframe_hdr);
	virtual int dealStateFunc(EM_STREAM_STATE_TYPE state, int param);//param: �ļ����ؽ���ֵ

	CMediaStream()
	: bstart(0)
	, dev_ip(0)
	, dev_idx(-1)
	, stream_idx(-1)
	{
		memset(&req, 0, sizeof(ifly_TCP_Stream_Req));
	}
	
protected:
	u8	bstart;
	u32 dev_ip;
	s32 dev_idx;
	s32 stream_idx;
	ifly_TCP_Stream_Req req;
};

typedef struct _SDev_StearmRcv_t
{
	u8 bstart;
	int	sockfd;	
	u32 linkid;
	ifly_TCP_Stream_Req req;
	CMediaStream* pStream; //ָ���������ṹ��Ԥ�����طš��ļ�����

	_SDev_StearmRcv_t()
	: bstart(0)
	, sockfd(INVALID_SOCKET)
	, linkid(-1)
	, pStream(NULL)
	{
		memset(&req, 0, sizeof(ifly_TCP_Stream_Req));
	}
} SDev_StearmRcv_t;


