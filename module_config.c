initialize step:
	testUI.cpp: CChallenger::Initialize()
		biz.c: BizInit()//��һ�ε���
			biz_manager.c: DoBizInit()
				biz_config.c: ConfigInit()
					mod_config.c: ModConfigInit()	gStrCustomFileName: /dev/mtd/5
						
NVR ��ȡ���õ�������
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
	int sec_num;		//????��y
	int hz_num;			//oo��?��y
}HZMB_HEAD;

typedef struct _HZMB_SECTOR{
	char str[8];		//1??����?��?��?��?,?����?��??�䨰?,���騰?,����?-�̨��̨�
	int offset;			//?????����Y?a��???��?
	int next;			//??��???????��??����?o?
}HZMB_SECTOR;

m_pSectors = (HZMB_SECTOR *)(pBuffer + sizeof(HZMB_HEAD));
m_pChars = (char *)(pBuffer + sizeof(HZMB_HEAD) + m_pHead->sec_num * sizeof(HZMB_SECTOR));

OnInputChanged m_nChars: 92
buf: ��, 0xe7 0x88 0xb1
buf: ��, 0xe5 0x93 0x80
buf: ��, 0xe6 0x8c 0xa8
buf: ��, 0xe7 0xa2 0x8d
buf: ��, 0xe5 0x9f 0x83