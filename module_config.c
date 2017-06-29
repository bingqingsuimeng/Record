initialize step:
	testUI.cpp: CChallenger::Initialize()
		biz.c: BizInit()//第一次调用
			biz_manager.c: DoBizInit()
				biz_config.c: ConfigInit()
					mod_config.c: ModConfigInit()	gStrCustomFileName: /dev/mtd/5
						
NVR 获取配置调用流程
PageBasicConfigFrameWork.cpp:	int index = GetVideoFormat()
	BizData.cpp:	BizGetPara()
		Biz.c:	DoBizGetPara()
			Biz_manager.c:	ConfigGetSystemPara()
				Biz_config.c:	ModConfigGetParam()
					mod_config.c:	{
						LOCK();	
						memcpy(para, pAllPara->psSystemPara, sizeof(SModConfigSystemParam));
						UNLOCK();						
						
GetContainerDev /dev/mtd/5

PageDesktop.cpp: m_pPageInputTray = new CPageInputTray(CRect(0, 0, 38, 26), NULL, NULL, this);

typedef struct _HZMB_HEAD{
	int sec_num;		//????êy
	int hz_num;			//oo×?êy
}HZMB_HEAD;

typedef struct _HZMB_SECTOR{
	char str[8];		//1??ü×?×?·?′?,?éò?ê??′ò?,×￠ò?,±ê?-μèμè
	int offset;			//?????úèY?aê???ò?
	int next;			//??ò???????μ??úμ?o?
}HZMB_SECTOR;

m_pSectors = (HZMB_SECTOR *)(pBuffer + sizeof(HZMB_HEAD));
m_pChars = (char *)(pBuffer + sizeof(HZMB_HEAD) + m_pHead->sec_num * sizeof(HZMB_SECTOR));

OnInputChanged m_nChars: 92
buf: 爱, 0xe7 0x88 0xb1
buf: 哀, 0xe5 0x93 0x80
buf: 挨, 0xe6 0x8c 0xa8
buf: 碍, 0xe7 0xa2 0x8d
buf: 埃, 0xe5 0x9f 0x83