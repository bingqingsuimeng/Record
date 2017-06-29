biz_types.h
PageSearch.h
PageSearch.cpp

void CPageSearch::SearchFilesWithFile()
{
	EMBIZFILETYPE emFileType = EM_BIZFILE_REC;
	sSearchResult.nFileNum = 0;
	memset(sSearchResult.psRecfileInfo, 0, 4000*sizeof(SBizRecfileInfo));
	
	sSearchPara.nMaskType = 0xf;
	sSearchPara.nMaskChn = nMaskChn;
	sSearchPara.nStartTime = 
		MakeTimeForBackup(
			tSysDate.year,
			tSysDate.month,
			tSysDate.day,
			0,
			0,
			0
		);
	sSearchPara.nEndTime = 
		MakeTimeForBackup(
			tSysDate.year,
			tSysDate.month,
			tSysDate.day,
			23,
			59,
			59
		);
		
	if( 0==BizSysComplexDMSearch(
		emFileType,
		&sSearchPara, 
		&sSearchResult, 
		4000 ))
	......
}

void CPageSearch::SearchFilesWithEvent()
{
	EMBIZFILETYPE emFileType = EM_BIZFILE_REC;
	sSearchResult0.nFileNum = 0;
	memset(sSearchResult0.psRecfileInfo, 0, 4000*sizeof(SBizRecfileInfo));
	
	memset(&sSearchPara, 0, sizeof(sSearchPara));
	sSearchPara.nMaskType |= 1<<i;
	sSearchPara.nMaskChn = nMaskChn;
	sSearchPara.nStartTime = mktime(&tM);
	sSearchPara.nEndTime = mktime(&tM);
	int nTimeZone = GetTimeZone();
	sSearchPara.nStartTime -= GetTimeZoneOffset(nTimeZone);
	sSearchPara.nEndTime -= GetTimeZoneOffset(nTimeZone);
	
	if( 0==BizSysComplexDMSearch(
		emFileType,
		&sSearchPara, 
		&sSearchResult0, 
		4000 ))
	......
}

typedef struct 
{
	u8 nMaskType;
	u32 nMaskChn;
	u32 nStartTime;
	u32 nEndTime;
	void* pReserverInfo;
} SBizSearchPara;

typedef struct
{
	u8 nChn;
	u8 nType;
	u32 nStartTime;
	u32 nEndTime;
	u8 nFormat;  //N制式下 10 = D1，13 = CIF  P制式下 0 = D1， 3 = CIF    
	u8 nStreamFlag;  //0:视频流;1:音频流
	u32 nSize;
	u32 nOffset;
	u8 nDiskNo;
	u8 nPtnNo;
	u16 nFileNo;
} PACK_NO_PADDING SBizRecfileInfo;

// 2.11 文件搜索结果结构体
typedef struct
{
	u16 nFileNum;
	SBizRecfileInfo *psRecfileInfo;//用于存放数据的文件信息数组
} PACK_NO_PADDING SBizSearchResult;
/*************************************************/
typedef struct 
{
	u8 nMaskType;
	u32 nMaskChn;
	u32 nStartTime;
	u32 nEndTime;
	void* pReserverInfo;
} SSearchPara;
// 2.17  文件信息参数
typedef struct
{
	u8 nChn;
	u8 nType;
	u32 nStartTime;
	u32 nEndTime;
	u8 nFormat;      //N制式下 10 = D1，13 = CIF  P制式下 0 = D1， 3 = CIF
	u8 nStreamFlag;  //0:视频流;1:音频流
	u32 nSize;
	u32 nOffset;
	u8 nDiskNo;
	u8 nPtnNo;
	u16 nFileNo;
} PACK_NO_PADDING SRecfileInfo;

// 2.11 文件搜索结果结构体
typedef struct
{
	u16 nFileNum;
	SRecfileInfo *psRecfileInfo;//用于存放数据的文件信息数组
} PACK_NO_PADDING SSearchResult;
/*
	函数功能:文件搜索
	输入参数：
		emFileType:
			类型:EMBIZFILETYPE
			含义:文件类型
		psSearchPara:
			类型:SBIZSearchPara
			含义:搜索条件
		psSearchResul:
			类型:SBizSearchResult
			含义:传入用于存放搜索结果结构体
		nMaxFileNum:
			类型:u16
			含义:psRecfileList的最大个数
	返回：
		类型:s32
		含义:返回成功,失败,或错误值
		取值:0成功;非0失败或错误值
*/
s32 BizSysComplexDMSearch(EMBIZFILETYPE emFileType, SBizSearchPara* psSearchPara, SBizSearchResult* psSearchResult, u16 nMaxFileNum)
	s32 SysComplexDiskSearch(SBizDiskSearch* pSPara)
	
/*
9.	s32 ModSysComplexDMSearch(EMFILETYPE emFileType, SSearchPara* psSearchPara, SSearchResult* psSearchResult, u16 nMaxFileNum;)
	函数功能:文件搜索
	输入参数：
		emFileType:
			类型:EMFILETYPE
			含义:文件类型
		psSearchPara:
			类型:SSearchPara
			含义:搜索条件
		psSearchResul:
			类型:SSearchResult
			含义:传入用于存放搜索结果结构体
		nMaxFileNum:
			类型:u16
			含义:psRecfileList的最大个数
	返回：
		类型:s32
		含义:返回成功,失败,或错误值
		取值:0成功;非0失败或错误值
*/
s32 ModSysComplexDMSearch(	EMFILETYPE emFileType,
							SSearchPara* psSearchPara,
							SSearchResult* psSearchResult,
							u16 nMaxFileNum )
	在此函数中判断emFileType是录像还是图片						
	s32 modSysComplex_Search_do( PSSearch para )
	
	
	
typedef struct
{
	u32  channel_no;
	u8   play_no;
	u8   type;
	u32  start_time;
	u32  end_time;
	u32  card_no;
	u8   mask;
}PACK_NO_PADDING search_param_t;

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

typedef struct
{
	u8	channel_no;//u32  ChaMask | 1<<chn
	u8	type;
	u8	snap_format;  //格式,0-jpeg,1-bmp,默认jpeg 
	u8	reserver;
	u16 	width;
	u16	height;
	u32	size;
	u32	offset;
	u8	disk_no;
	u8	ptn_no;
	u16	file_no;
	u32	start_time;
	u32	start_timeus;
} PACK_NO_PADDING recsnapinfo_t;