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
//码流传输请求结构
typedef struct 
{
	u8 command;							//0：预览 1：文件回放 2：时间回放 3：文件下载 4：升级 
										//5 VOIP 6 文件按帧下载 7 时间按帧下载 8 透明通道
										//9 远程格式化硬盘 10 主机端抓图 11 多路按时间回放 12 按时间下载文件
	union		//72byte
	{
		struct
		{
			u8		chn;				//预览通道
			u8		type;				//0:主码流视频 1：主码流音频 2：子码流视频
		}Monitor_t;						//预览 command = 0
		
		struct
		{
			char	filename[64];		//回放的文件
			u32		offset;				//文件偏移
		}FilePlayBack_t; 				//文件回放 command = 1,或 command = 6
		
		struct
		{
			u8		channel;			//通道数
			u16		type;				//类型
			u32		start_time;			//开始时间
			u32		end_time;			//终止时间
		}TimePlayBack_t ;				//时间回放 command = 2,或 command = 7
		
		struct
		{
			char	filename[64];		//下载的文件
			u32		offset;				//文件偏移
			u32		size;				//文件大小
		}FileDownLoad_t;				//文件下载 command = 3
		
		struct
		{
			u32		size;				//文件长度
			u32		verify;				//校验和
			u16		version;			//文件版本号
			u16		updateType;			//0:主板升级 1：面板升级
		}Update_t;						//远程升级  command = 4；
		
		//VOIP command
		u8 voipreserved;				//VOIP预留 command = 5；

		//透明通道
		u8 SerialPort;					//透明通道 1-232串口  2-485串口	command = 8；

		//远程格式化硬盘
		u8 formatHddIndex;				//要格式化的硬盘号 0开始

		struct
		{
			u16		chnMask;			//通道数 按位 特指通道1-16
			u16		type;				//类型
			u32		start_time;			//开始时间
			u32		end_time;			//终止时间
			u16		chn17to32Mask;		//通道17-32 按位
		}MultiTimePlayBack_t ;			//多路时间回放 command = 11，12
	};
	u8	reserved[7];					//预留	
}ifly_TCP_Stream_Req;


1、预览开始、关闭。使用PrewiewHandle
2、云台控制
3、录像查询
4、录像回放开始、关闭
5、录像回放控制
6、录像备份
7、录像发送解码器回放
8、对解码器设置通道


//stream					
	C_Lock *plock4stream;//mutex
	VD_BOOL bthread_stream_running;
	VD_BOOL bthread_stream_exit;//外部控制线程退出
	int stream_cnt;
	int idle_cnt;//空闲计数，线程空闲1分钟后退出
	CSemaphore sem_exit;//等待threadStreamRcv退出信号量
	SDev_StearmRcv_t stearm_rcv[MaxMediaLinks]; //数据流结构MaxMediaLinks
	void threadStreamRcv(uint param);
	Threadlet m_threadlet_stream_rcv;


class CMediaStream : public CObject
{
public:
	int Start();
	int Stop();
	virtual int dealFrameFunc(FRAMEHDR *pframe_hdr);
	virtual int dealStateFunc(EM_STREAM_STATE_TYPE state, int param);//param: 文件下载进度值

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
	CMediaStream* pStream; //指向具体的流结构，预览、回放、文件备份

	_SDev_StearmRcv_t()
	: bstart(0)
	, sockfd(INVALID_SOCKET)
	, linkid(-1)
	, pStream(NULL)
	{
		memset(&req, 0, sizeof(ifly_TCP_Stream_Req));
	}
} SDev_StearmRcv_t;


