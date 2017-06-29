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
	u32 total_file_nums;			//�ܹ����ļ���������
	u32 recorded_file_nums;			//
	u32 full_file_nums;				//
	u32 full_file_offset;			//
	chn_last_use_file chn_info[33];	//
	u8  reserved3[80];				//
	u32 verify;						//
}PACK_NO_PADDING  partition_index_header;

typedef struct
{
	partition_index_header header;	//��������ͷ
	FILE *index1;					//�����ļ�
	FILE *index2;					//���������ļ�
//	u8   *mapdst1;					//�����ļ��ڴ�ӳ��ָ��
//	u8   *mapdst2;					//���������ļ��ڴ�ӳ��ָ��
//	u32  length1;						//�����ļ�����
//	u32  length2;						//���������ļ�����
	u8  *cachedst;
	u32 cachelen;
	u8  valid;						//�����Ƿ���Ч
#ifndef WIN32
	pthread_mutex_t lock;			//����ʹ����
#endif
	char mountpath[64];				//��������·��
} partition_index;


//�����ļ����� �ڴ˺����п��Կ���
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

//����
int search_rec_file(partition_index *index,search_param_t *search,recfileinfo_t *fileinfo_buf,int max_nums,u8 disk_no,u8 ptn_no)

//�ֶ�����¼������
PageStartFrameWork.cpp
	OnClkStartBtn()
	-- case START_TOOLREC:
		m_pPageRecChnSel->Open();
			CPageChnSelect::OnClkButton()
				StartManuelRec();//�ֶ�¼������
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
		RecordRefreshStatus((void *)CurRecStatus); -- RecordDeal()//����¼��ͼ��
	
	RecordDeal()
		SendBizInnerMsgCmd()
			DoBizRecStatusChange()
				VEncMainControl()
					EncodeControl()//��һ�����У�����������ã�֮�� ¼�� ��������
						EncodeRequestStart(nChn, emChnType);
							ModEncodeRequestStart(nChn, emChnType, EncodeDeal, nContent) //��EncodeDeal������¼��ʱ�����ص�����
						
//¼������дһ֡����
//֡����+ sizeof(SModRecRecordHeader) ����С�� (640<<10)��ԭ��RecordMainFxn()��frame_data[640<<10]
IPC_RegisterCallback(DealRealStream, DealStreamState);ע��ص�
	DealRealStream()
		WriteFrameToVencMainQueue()
			DealMainStream()
			if(stream->len > g_s_EncodeManager.sChnMainManage.nMaxFrameSize)//640k ֡��С����
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
	
	�жϸ��ֱ�־���������Ƿ�д
	
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
	//if(cur_atx_flag == 0 || g_HotPlugFlag)//��ع���
	if(g_HotPlugFlag)
	{
		RecordResetBuf(chn);
		return EM_REC_SUCCESS;
	}
	#endif
	
	//printf("ModRecordWriteOneFrame-2\n");
	
	return RecordWriteFrameToBuf(header);
}


//Ԥ¼���ݽṹ
//ÿͨ��һ�����ι���
typedef struct 
{
	u8 in;
	u8 out;
	u8 total;
	sem_t sem;
} TypePreRecSnapChnCtl;
static TypePreRecSnapChnCtl *p_PreRecSnapChnCtl = NULL;
static FILE *pf_PreRecSnap[2] = {NULL, NULL};	//126/127�����ļ�����
#define PreRecSnapNumPerChn (100)
#define SnapSize (128*1024)

#define FILE_VECTOR_SIZE	(256*1024*1024)


/*ͼƬԤ¼
126/127���ļ�������Ԥ¼ʹ�ã�ÿ������16��ͨ��
�ļ������ڲ�16�ȷ֣�ÿ��ͨ��ʹ��һ��16M�ռ�
16M�ռ��Ź���ͷ��Ϣ��100��ͼƬ
���û��εķ�ʽ���ͼƬ
*/
typedef struct
{
	u16 	width;
	u16	height;
	u32	pic_size;		//ͼƬ��С
	time_t		tv_sec;	//ͼƬʱ��
}PACK_NO_PADDING prepic_use_info;

/***************************************************/
����ͼƬʱ����Ҫ��ͣ��ʱ��
1����ʽ��������
2����������

BOOL modsys_CheckDskInfo()
{
	BOOL bRslt = TRUE;
	
	//���ݽ������򲻼��
	if(sModSysIns.bBackuping)
	{
		bRslt = FALSE;
	}
	
	//csp modify 20121018
	//��ʽ���������л����������򲻼��
	if(sModSysIns.bFormating || sModSysIns.bUpdate)
	{
		bRslt = FALSE;
	}
	
	return bRslt;
}

��ʽ��ǰֹͣ����ʽ����ָ�
void sysComplexStopRecCB( void )
void sysCompleResumeRecCB( void )


//yaogang modify20150115
static SCircleBufInfo g_RecSnapBufInfo;
static pthread_mutex_t LockSnapBuf;
static pthread_cond_t CondSnapBuf;	//BufΪ�գ����߳�RecordSnapFxn ����
static volatile u32 BufSnapCnt;		//Buf��ͼƬ����


pthread_mutex_lock(&LockSnapBuf);
	
ret = ResetCircleBuf(&g_RecSnapBufInfo);
BufSnapCnt = 0;

pthread_mutex_unlock(&LockSnapBuf);



