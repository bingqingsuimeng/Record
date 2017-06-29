typedef struct bufinfo
{
	s32 nBufId;//每个buf分配一个id
	u8* nBufAddr;
	u32 nWrOffset;
	u32 nRdOffset;
	u32 nWrOffsetPast;
	u32 nRdOffsetPast;
	u32 nLength;
	u32 nLenUsed;
	sem_t sem;
}SCircleBufInfo;

log.c
	g_LogMsgQueueInfo.nBufId = 0;
	g_LogMsgQueueInfo.nLength = g_pLogMgr->nMaxLogs * sizeof(SLogMsgHeader);
	
mod_config.c
	g_s_MsgQueueInfo.nBufId = 0;
	g_s_MsgQueueInfo.nLength = 1024 * sizeof(SConfigMsgHeader);
	
	
	
typedef struct
{
	char AgentID[100];
	char CenterIP[100];
	u8 RunEnable;//运行状态启用
	u8 AlarmEnable;//报警联动启用
	u8 DailyPicEnable;//日常图像启用
	SModAlarmPicCFG SAlarmPicParam;//报警图片配置参数
	SModDailyPicCFG SDailyPicParam;//日常图片配置参数
} SModConfigSGParam;
	SModConfigSGParam sConfig;
	s32 nId = 0;
	ret = ModConfigGetParam(EM_CONFIG_PARA_SG, &sConfig, nId);