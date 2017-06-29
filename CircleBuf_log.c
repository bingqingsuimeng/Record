typedef struct bufinfo
{
	s32 nBufId;//ÿ��buf����һ��id
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
	u8 RunEnable;//����״̬����
	u8 AlarmEnable;//������������
	u8 DailyPicEnable;//�ճ�ͼ������
	SModAlarmPicCFG SAlarmPicParam;//����ͼƬ���ò���
	SModDailyPicCFG SDailyPicParam;//�ճ�ͼƬ���ò���
} SModConfigSGParam;
	SModConfigSGParam sConfig;
	s32 nId = 0;
	ret = ModConfigGetParam(EM_CONFIG_PARA_SG, &sConfig, nId);