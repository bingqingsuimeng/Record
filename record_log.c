typedef struct
{
	u16 file_no;
	u16 sect_nums;
	u32 start_time;
	u32 end_time;
}PACK_NO_PADDING  chn_last_use_file;

typedef struct
{
	u32 op_nums;					//
	u32 reserved1;					//
	u32 version;					//
	u32 reserved2;					//
	u32 total_file_nums;			//总共的文件容器数量
	u32 recorded_file_nums;			//
	u32 full_file_nums;				//
	u32 full_file_offset;			//
	chn_last_use_file chn_info[33];	//
	u8  reserved3[80];				//
	u32 verify;						//
}PACK_NO_PADDING  partition_index_header;

typedef struct
{
	partition_index_header header;	//分区索引头
	FILE *index1;					//索引文件
	FILE *index2;					//备份索引文件
//	u8   *mapdst1;					//索引文件内存映射指针
//	u8   *mapdst2;					//备份索引文件内存映射指针
//	u32  length1;						//索引文件长度
//	u32  length2;						//备份索引文件长度
	u8  *cachedst;
	u32 cachelen;
	u8  valid;						//分区是否有效
#ifndef WIN32
	pthread_mutex_t lock;			//分区使用锁
#endif
	char mountpath[64];				//分区挂载路径
} partition_index;


//索引文件构成 在此函数中可以看出
long seek_to_segment(partition_index *index,partition_index_header *pHeader,int file_no,int sect_no)
{
	if(index->valid)
	{
		//long position = sizeof(partition_index_header) + pHeader->total_file_nums * sizeof(file_use_info) + 8192 * file_no + 32 * sect_no;
		long position = sizeof(partition_index_header) + pHeader->total_file_nums * sizeof(file_use_info) + (NFILE_PER_SECT*32) * file_no + 32 * sect_no;//yaogang hdd
		//32 == sizeof(segment_use_info);
		return position;
	}
	return 0; 
}

typedef struct
{
	u8  type;
	u8  image_format;
	u8  stream_flag;
	u8  video_compressor;// 1:xvid; 2:jpeg; 3:h.264
	u8  audio_compressor;// 1:pcmu; 2:pcma; 3:adpcm
	u8  reserved1[11];
	u32 start_time;
	u32 end_time;
	u32 start_position;
	u32 end_position;
}PACK_NO_PADDING segment_use_info;

typedef struct
{
	u32 file_no;
	u8  chn_no;
	u8  busy;
	u16 sect_nums;
	u32 start_time;
	u32 end_time;
}PACK_NO_PADDING file_use_info;

#define RECTYPE_MASK_TIMER	0x1
#define RECTYPE_MASK_MD		0x2
#define RECTYPE_MASK_ALARM	0x4
#define RECTYPE_MASK_HAND	0x8
#define RECTYPE_MASK_ALL	0x10

//查找
int search_rec_file(partition_index *index,search_param_t *search,recfileinfo_t *fileinfo_buf,int max_nums,u8 disk_no,u8 ptn_no)

//手动开启录像流程
PageStartFrameWork.cpp
	OnClkStartBtn()
	-- case START_TOOLREC:
		m_pPageRecChnSel->Open();
			CPageChnSelect::OnClkButton()
				StartManuelRec();//手动录像启动
					DealManualRec()
						BizStartManualRec(u8 nChn)
							ModRecordStartManual(u8 chn)
								sMsg.nChn = chn;
								sMsg.nMsg = EM_REC_V_MANUAL;
								sMsg.nKey = 1;
								sMsg.data = NULL;
								RecordWriteMsgQueue(0, &sMsg);
	RecordStatusManagerFxn()
		RecordReadMsgQueue(0, &sMsg)
			case EM_REC_ABNORMAL:
				RecordDealRecMsg(&sMsg)
			case EM_REC_V_MANUAL:
				g_RecordStatus[sMsg.nChn] |= 1;
		RecordRefreshStatus((void *)CurRecStatus); -- RecordDeal()//窗口录像图标
	
	RecordDeal()
		SendBizInnerMsgCmd()
			DoBizRecStatusChange()
				VEncMainControl()
					EncodeControl()//第一次运行，会有相关设置，之后 录像 才能启动
						EncodeRequestStart(nChn, emChnType);
							ModEncodeRequestStart(nChn, emChnType, EncodeDeal, nContent) //绑定EncodeDeal，下面录像时码流回调会用
						
//录像开启后写一帧流程
//帧长度+ sizeof(SModRecRecordHeader) 必须小于 (640<<10)，原因RecordMainFxn()中frame_data[640<<10]
IPC_RegisterCallback(DealRealStream, DealStreamState);注册回调
	DealRealStream()
		WriteFrameToVencMainQueue()
			DealMainStream()
			if(stream->len > g_s_EncodeManager.sChnMainManage.nMaxFrameSize)//640k 帧大小限制
				EncodeDeal()
					EncDataDispatch()
						RecordWriteOneFrame()
							
				
s32 RecordWriteOneFrame(u8 nChn, SModRecRecordHeader* psHeader)
	s32 ModRecordWriteOneFrame(u8 chn, SModRecRecordHeader* header)
		s32 RecordWriteFrameToBuf(SModRecRecordHeader* header)
	
s32 RecordWriteFrameToBuf(SModRecRecordHeader* header)
{
	if(((0 == (g_RecordStatus[header->nChn] | g_RecordStatusDelay[header->nChn])) && (0 == g_RecordPreTime[header->nChn] || 0 == g_IsPreRecording[header->nChn])) || (1 == g_ChnPaused[header->nChn]))
	{
		if(uCountOfNoNeed[header->nChn]++ > 200)
		{
			uCountOfNoNeed[header->nChn] = 0;
			fprintf(stderr, "No need to send data! chn = [%d]; function: %s\n", header->nChn, __FUNCTION__);
		}
		return EM_REC_SUCCESS;
	}
	
	判断各种标志决定下面是否写
	
	sem_wait(&nSemForBuffer[header->nChn]);
	#endif
	
	ret = WriteDataToBuf(&g_RecBufInfo[header->nChn], (u8 *)header, sizeof(SModRecRecordHeader));
	if(EM_REC_SUCCESS != ret)
	{
		fprintf(stderr, "function: %s\n", __FUNCTION__);
		sem_post(&nSemForBuffer[header->nChn]);
		return ret;
	}
	ret = WriteDataToBuf(&g_RecBufInfo[header->nChn], header->nDate, header->nDataLength);
	if(EM_REC_SUCCESS != ret)
	{
		fprintf(stderr, "function: %s\n", __FUNCTION__);
		ResumeCircleBufToPast(&g_RecBufInfo[header->nChn], 1, 0);
		sem_post(&nSemForBuffer[header->nChn]);
		return ret;
	}
	
	sem_post(&nSemForBuffer[header->nChn]);
}


s32 ModRecordWriteOneFrame(u8 chn, SModRecRecordHeader* header)
{
	//printf("ModRecordWriteOneFrame-1\n");
	
	if(g_recordinit == 0)
	{
		fprintf(stderr, "error : ModRecordInit not done!\n");
		return EM_REC_HASNOTINIT;
	}
	
	if((chn >= g_ChnNum) || (NULL == header) || (chn != header->nChn))
	{
		fprintf(stderr,"Invalid parameter for function %s !\n", __FUNCTION__);
		return EM_REC_INVALID_PARA;
	}
	
	if(g_DvrHasHdd == 0)
	{
		return EM_REC_SUCCESS;
	}
	
	#if 1
	//unsigned char cur_atx_flag = tl_power_atx_check();
	//if(cur_atx_flag == 0 || g_HotPlugFlag)//电池供电
	if(g_HotPlugFlag)
	{
		RecordResetBuf(chn);
		return EM_REC_SUCCESS;
	}
	#endif
	
	//printf("ModRecordWriteOneFrame-2\n");
	
	return RecordWriteFrameToBuf(header);
}


//预录数据结构
//每通道一个环形管理
typedef struct 
{
	u8 in;
	u8 out;
	u8 total;
	sem_t sem;
} TypePreRecSnapChnCtl;
static TypePreRecSnapChnCtl *p_PreRecSnapChnCtl = NULL;
static FILE *pf_PreRecSnap[2] = {NULL, NULL};	//126/127两个文件容器
#define PreRecSnapNumPerChn (100)
#define SnapSize (128*1024)

#define FILE_VECTOR_SIZE	(256*1024*1024)


/*图片预录
126/127号文件容器给预录使用，每个负责16个通道
文件容器内部16等分，每个通道使用一个16M空间
16M空间存放管理头信息和100张图片
采用环形的方式存放图片
*/
typedef struct
{
	u16 	width;
	u16	height;
	u32	pic_size;		//图片大小
	time_t		tv_sec;	//图片时间
}PACK_NO_PADDING prepic_use_info;

/***************************************************/
保存图片时，需要暂停的时刻
1、格式化过程中
2、正在升级

BOOL modsys_CheckDskInfo()
{
	BOOL bRslt = TRUE;
	
	//备份进行中则不检查
	if(sModSysIns.bBackuping)
	{
		bRslt = FALSE;
	}
	
	//csp modify 20121018
	//格式化过程中中或正在升级则不检查
	if(sModSysIns.bFormating || sModSysIns.bUpdate)
	{
		bRslt = FALSE;
	}
	
	return bRslt;
}

格式化前停止，格式化后恢复
void sysComplexStopRecCB( void )
void sysCompleResumeRecCB( void )


//yaogang modify20150115
static SCircleBufInfo g_RecSnapBufInfo;
static pthread_mutex_t LockSnapBuf;
static pthread_cond_t CondSnapBuf;	//Buf为空，则线程RecordSnapFxn 阻塞
static volatile u32 BufSnapCnt;		//Buf中图片个数


pthread_mutex_lock(&LockSnapBuf);
	
ret = ResetCircleBuf(&g_RecSnapBufInfo);
BufSnapCnt = 0;

pthread_mutex_unlock(&LockSnapBuf);



