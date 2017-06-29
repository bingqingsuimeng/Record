BUG:
	回卷后，分区初始化了index->pic_header，没有初始化其中的file_pic_use_info

#define ARG_VI_NUM_MAX 				(lib_gbl_info.vi_num_max)
#define ARG_VO_NUM_MAX 				(lib_gbl_info.vo_num_max)
 
cat /proc/umap/vdec
cat /proc/umap/vpss
cat /proc/umap/vo
cat /proc/umap/sys
cat /proc/umap/vb

cat /dev/logmpp

索引文件内部结构：
index_file_size = 512 + nr_files*(16+NFILE_PER_SECT*32);
//512: sizeof(partition_index_header)
//16: sizeof(file_use_info)
//32: sizeof(segment_use_info)

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
	u32 total_file_nums;			//分区文件容器数量
	u32 recorded_file_nums;			//已使用文件容器数量
	u32 full_file_nums;				//已经写满的文件容器数量
	//已经写满的文件容器的file_use_info，
	//经过调整会放在一起,相对于起始file_use_info结构的偏移
	u32 full_file_offset;				
	chn_last_use_file chn_info[33];	//
	u8  reserved3[80];				//
	u32 verify;						//
}PACK_NO_PADDING  partition_index_header;

16
typedef struct
{
	u32 file_no;
	u8  chn_no;
	u8  busy;
	u16 sect_nums;
	u32 start_time;
	u32 end_time;
}PACK_NO_PADDING file_use_info;

32
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
	partition_index_header header;	//分区索引头
	FILE *index1;					//索引文件
	FILE *index2;					//备份索引文件
//	u8   *mapdst1;					//索引文件内存映射指针
//	u8   *mapdst2;					//备份索引文件内存映射指针
//	u32  length1;						//索引文件长度
//	u32  length2;						//备份索引文件长度
	u8	*cachedst;
	u32 cachelen;
	u8  valid;						//分区是否有效
#ifndef WIN32
	pthread_mutex_t lock;			//分区使用锁
#endif
	char mountpath[64];				//分区挂载路径
} partition_index;

typedef struct
{
	u8 is_disk_exist;
	u8 is_partition_exist[MAX_PARTITION_NUM];
	partition_index ptn_index[MAX_PARTITION_NUM];
	long total;
	long free;
	u8 storage_type;//'s'->sata, 'u'->'usb'
	u8 disk_physical_idx;//主板上硬盘的物理编号
	u8 disk_logic_idx;//主板上硬盘的逻辑编号
	u8 disk_system_idx;//系统检测到的硬盘编号sda->0, sdb->1...
	char disk_name[32];//硬盘设备名/dev/sda, /dev/sdb...
	char disk_sn[64];//硬盘序列号、唯一
}HddInfo;


int nTimeZone = GetTimeZone();
time_t nAlarmTime = pPara->sBizAlaStatus.nTime + GetTimeZoneOffset(nTimeZone);

int nTimeZone = GetTimeZone();
time_t nAlarmTime = time(NULL) + GetTimeZoneOffset(nTimeZone);

struct tm tmAlarm;
struct tm* ptm = &tmAlarm;
localtime_r(&nAlarmTime, ptm);


2
SBizSystemPara sysPara;
	memset(&sysPara, 0, sizeof(SBizSystemPara));
	ConfigGetSystemPara(0, &sysPara);
	int nTimeZone = sysPara.nTimeZone;
	time += GetTZOffset(nTimeZone);
	
	struct tm sTime;
	//csp modify
	//sTime = *localtime(&time);
	localtime_r(&time,&sTime);
	
3	
	time_t nowtime = time(NULL);
	
	//csp modify 20131213
	nowtime += ModRecordGetTimeZoneOffset();
	
	//csp modify
	//struct tm *now = localtime(&nowtime);
	struct tm result;
	struct tm *now = &result;
	localtime_r(&nowtime, now);


refresh

//yaogang modify 20141225
/*********************************************************
图片保存方案
文件容器还是256M，图片就保存在文件容器中
所有的图片的索引信息都记录在索引文件中
索引文件结构:
index_file_header
file_use_info * 128 		//分配n 个文件容器，每分区暂定128 个文件容器
pic_use_info * 32768	//图片信息，每文件容器最大图片数量，32768*8k(分辨率352*288)
抓图类型	bit_mask	value
定时			0		
移动侦测	1
报警			2
动测或报警			(1<<1) |(1<<2)
动测且报警			(1<<1) |(1<<2) |(1<<7)
手动			3
智能侦测	4
手动截图	5
回放截图	6
全部类型			0xff
*********************************************************/
typedef struct
{
	u16	file_nums;			//文件容器个数PIC_FILE_NUMS
	u16	file_cur_no;			//当前正在使用的文件容器，用完回卷0xffff
	u32	partition_pic_nums;	//分区保存的图片数量
	time_t		start_sec;	//分区使用开始时间
	suseconds_t	start_usec;
	time_t		end_sec;		//分区使用结束时间
	suseconds_t	end_usec;
	char reserved[24];
	u32 verify; 				//
}PACK_NO_PADDING  partition_pic_index_header;
//32
typedef struct
{
	u16	file_no;
	u8	status;				//使用情况: 未使用、未写满、已写满
	u8	pic_type_mask;		//抓图类型掩码，标识当前文件容器中是否保存过相应类型的图片0
	u32	chn_mask;			//通道掩码，标识当前文件容器中是否保存过相应通道的图片0
	u32	next_pic_pos;			//写下一张图片时的起始位置0xffffffff
	u32	file_pic_nums;		//文件中保存的图片数量
	time_t		start_sec;	//文件容器内第一张图片时间
	suseconds_t	start_usec;
	time_t		end_sec;		//文件容器内最后一张图片时间
	suseconds_t	end_usec;
}PACK_NO_PADDING file_pic_use_info;

/*抓图类型	bit_mask	value
定时			0		
移动侦测	1
报警			2
动测或报警			(1<<1) |(1<<2)
动测且报警			(1<<1) |(1<<2) |(1<<7)
手动			3
智能侦测	4
手动截图	5
回放截图	6
全部类型			0xff
*/
//24
typedef struct
{
	u8	chn;		//通道	
	u8	pic_type;	//抓图类型
	u16	file_no;	//所在文件容器
	u16 	width;
	u16	height;
	u32	file_offset;	//图片存储位置在文件容器内部偏移
	u32	pic_no;	//图片序号
	u32	pic_size;		//图片大小
	time_t		tv_sec;	//图片时间
	suseconds_t	tv_usec;
}PACK_NO_PADDING pic_use_info;

//用于保存图片文件容器数量
#define PIC_FILE_NUMS		128
//图片大小以8K计，文件容器中最多可写入的图片数量
#define PIC_NUMS_PER_FILE	32768


#pragma pack( pop )

typedef struct
{
	partition_index_header header;	//分区索引头
	partition_pic_index_header pic_header;// 分区图片索引头
	FILE *index1;					//索引文件
	FILE *index2;					//备份索引文件
	FILE *pic_idx;					//图片索引文件
	FILE *pic_idx_bk;				//图片备份索引文件
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

pic%05d.ifv

/*抓拍请求条件VVV_CMD_SNAP_CHN*/
typedef struct tagVVV_SNAP_CHN_REQ
{
	unsigned int chn;
    unsigned int snapformat;     /*抓拍格式,0-jpeg,1-bmp,默认jpeg*/
    unsigned int count;          /*连续抓拍张数,默认1*/
    unsigned int timeinterval;   /*抓拍时间间隔,默认500毫秒，单位毫秒*/
	unsigned char reserve[32];
}VVV_SNAP_CHN_REQ_S;

playback.c
typedef struct 
{
	u8   nMaskType;
	u32  nMaskChn;
	u32  nStartTime;
	u32  nEndTime;
	void* pReserverInfo;
} SPBSearchPara;
s32 SearchRecFiles(SPlayBackManager* pSPbMgr,SPBSearchPara* pSearchParam)
	//diskmangat.c 循环查看所有的硬盘分区
	int nFileNum = search_all_rec_file(gp_sHddManager,&sSearch,(recfileinfo_t*)nRecFileInfos,MAX_SEARCH_NUM);
		//partitionindex.c
		int search_rec_file(partition_index *index,search_param_t *search,recfileinfo_t *fileinfo_buf,int max_nums,u8 disk_no,u8 ptn_no)
		
		
			
