任务：
1、修改255
2、文件容器数目改少，测试磁盘覆盖
3、文件容器数目不改，频繁关闭、打开文件，使硬盘录满，测试覆盖和大数据搜索

所谓硬盘的CHS，即Cylinder（柱面）、Head（磁头）、Sector（扇区），只要知道了硬盘的CHS的数目，
即可确定硬盘的容量，硬盘的容量=柱面数*磁头数*扇区数*512B。

CPageDiskMgr::OnClkButton()
	void CPageDiskMgr::Format()
		BizSysComplexDMFormat(szDev, EM_BIZFORMAT_FAT32_IFV);
			SysComplexDiskFormat(&sPara);
				ModSysComplexDMFormat(pstrDevPath, emFormatWay);//发信息格式化 EM_MODSYS_CMD_DMFormat
					WriteMsgCmd()//阻塞 sem_wait(&psMsgCmdHdr->acksem);	

modSysCmplx_ThreadFunc(void* param)//该线程处理各种信息
	modSysCmplx_DMFormat();//完成后 AckMsgCmd(pCmd) --> sem_post(&psMsgCmdHdr->acksem);
		pthread_create(&thxdFormat, NULL, modsys_FormatFxn, NULL);//处理进度
		ifly_partition(disk_name, count, 0xc);
			mkfsdos_main (int argc, char **argv)


printf("%s -- ", __func__);


//分区索引
mkfsdos.c	1436
	#define FILE_VECTOR_SIZE	(128*1024*1024)


typedef struct
{
	u16 file_no;//该通道在使用哪个文件容器
	u16 sect_nums;//该文件容器已经使用多少个文件
	u32 start_time;
	u32 end_time;
}PACK_NO_PADDING  chn_last_use_file;//12 bytes

typedef struct
{
	u32 op_nums;					//
	u32 reserved1;				//
	u32 version;					//
	u32 reserved2;				//
	u32 total_file_nums;			//分区文件容器数量
	u32 recorded_file_nums;		//已使用文件容器数量
	u32 full_file_nums;				//
	u32 full_file_offset;				//
	chn_last_use_file chn_info[33];	//
	u8  reserved3[80];				//
	u32 verify;					//
}PACK_NO_PADDING  partition_index_header;//512 bytes

typedef struct
{
	u32 file_no;
	u8  chn_no;
	u8  busy;
	u16 sect_nums;	//该文件容器已经使用多少个文件
	u32 start_time;
	u32 end_time;
}PACK_NO_PADDING file_use_info;//16 bytes

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
	u32 start_position;//该文件在文件容器中的偏移
	u32 end_position;
}PACK_NO_PADDING segment_use_info;//描述文件容器中的一个文件32 bytes

libjpeg.lib STRMBASE.lib winmm.lib kernel32.lib user32.lib gdi32.lib 
winspool.lib comdlg32.lib advapi32.lib
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

回放
void CPageStartFrameWork::OnClkStartBtn()
	BizStartPlayback(EM_BIZPLAY_TYPE_TIME,&sBizSearchParam);
		PlaybackStart(&sBizPbStart);
			PlayBackByTime((SBizSearchPara *)psPbStart->para);
				ModPlayBackByTime(psBizManager->hPb, (SPBSearchPara*)pSearchParam);
					SearchRecFiles(pSPbManager,&sSearchParam);
						search_all_rec_file(gp_sHddManager,&sSearch,(recfileinfo_t*)nRecFileInfos,MAX_SEARCH_NUM);
							search_rec_file(&phinfo->ptn_index[j], search, fileinfo_buf + search_count, max_nums-search_count, i, j);
							
					SBizSearchPara sBizSearchParam;
					tmstrTmp.tm_hour = 0;
					tmstrTmp.tm_min = 0;
					tmstrTmp.tm_sec = 0;
					sBizSearchParam.nStartTime = mktime(&tmstrTmp);
					
					tmstrTmp.tm_hour = 23;
					tmstrTmp.tm_min = 59;
					tmstrTmp.tm_sec = 59;
					sBizSearchParam.nEndTime = mktime(&tmstrTmp);
					sBizSearchParam.nStartTime -= GetTimeZoneOffset(nTimeZone);
					sBizSearchParam.nEndTime -= GetTimeZoneOffset(nTimeZone);
					
					sBizSearchParam.nMaskChn = 0x0000000f;//1101
					sBizSearchParam.nMaskType = 0xff;
				

custommp4_open:
custommp4_t* custommp4_open(char *filename,u8 open_mode,u32 open_offset)
custommp4_file_properties_object_init(&file->fpot);
	int custommp4_file_properties_object_init(file_properties_object_t *pfpot)
	{
		pfpot->obj.object_id = CUSTOMMP4_file_properties_object;
		pfpot->obj.object_size = sizeof(file_properties_object_t);
		pfpot->video_tracks = 0;
		pfpot->audio_tracks = 0;
		pfpot->start_time = (u32)(time(NULL));
		pfpot->end_time = pfpot->start_time;
		pfpot->file_Size = sizeof(file_properties_object_t)+sizeof(video_stream_properties_object_t)+sizeof(audio_stream_properties_object_t)+sizeof(mdat_vector_object_t);
		//printf("custommp4_file_properties_object_init:file_Size=%d\n",pfpot->file_Size);
		pfpot->reserved1 = 0;
		strncpy(pfpot->describe,CUSTOMMP4_FILE_DESCRIBE,sizeof(pfpot->describe));
		return 1;
	}				
custommp4_video_stream_properties_object_init(&file->vspot);
	int custommp4_video_stream_properties_object_init(video_stream_properties_object_t *pvspot)
	{
		pvspot->obj.object_id = CUSTOMMP4_video_stream_properties_object;
		pvspot->obj.object_size = sizeof(video_stream_properties_object_t);
		pvspot->time_scale = 1000;
		pvspot->width = 352;
		pvspot->height = 288;
		pvspot->frame_rate = 25;
		pvspot->bit_rate = 512*1024;
		pvspot->compressor = str2uint("XVID");
		pvspot->depth = 0x18;
		pvspot->dpi_horizontal = 72;
		pvspot->dpi_vertical = 72;
		pvspot->flags = 0;
		pvspot->reserved1 = 0;
		return 1;
	}
custommp4_audio_stream_properties_object_init(&file->aspot);
custommp4_mdat_vector_object_init(&file->mvot);				
	int custommp4_mdat_vector_object_init(mdat_vector_object_t *pmvot)
	{
		pmvot->obj.object_id = CUSTOMMP4_mdat_vector_object;
		pmvot->obj.object_size = sizeof(mdat_vector_object_t);
		pmvot->number_of_segments = 0;
		pmvot->reserved1 = 0;
		return 1;
	}			
custommp4_mdat_segment_info_table_init(file, file->p_mdat_sect_t);					
	int custommp4_mdat_segment_info_table_init(custommp4_t *file, mdat_segment_info_table_t *p_mdat_sect_t)
	{
		p_mdat_sect_t->video_frames = 0;
		p_mdat_sect_t->audio_frames = 0;
		p_mdat_sect_t->start_time = time(NULL);
		p_mdat_sect_t->end_time = p_mdat_sect_t->start_time;
		p_mdat_sect_t->offset = custommp4_position(file);
		if(file->fpot.video_tracks) p_mdat_sect_t->video_allocated = 3000;
		else p_mdat_sect_t->video_allocated = 0;
		if(file->fpot.audio_tracks) p_mdat_sect_t->audio_allocated = 4000;
		else p_mdat_sect_t->audio_allocated = 0;
		return 1;
	}//no write file				
					
	msot.obj.object_id = CUSTOMMP4_mdat_segment_object;
	msot.obj.object_size = sizeof(msot);
	msot.video_frames = 0;
	msot.audio_frames = 0;
	msot.reserved1 = 0;
	msot.start_time = file->p_mdat_sect_t->start_time;
	msot.end_time = file->p_mdat_sect_t->end_time;
	msot.video_allocated = file->p_mdat_sect_t->video_allocated;
	msot.audio_allocated = file->p_mdat_sect_t->audio_allocated;
	custommp4_write_data(file, &msot, sizeof(msot));				
	
	