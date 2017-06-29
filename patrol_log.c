һ����Ѳ���
//for SBizPreviewPara.emBizPreviewMode /SBizPreviewData
typedef enum
{
    EM_BIZPREVIEW_1SPLIT = 1,
    EM_BIZPREVIEW_4SPLITS = 4, //nModePara=0~�����Ƶͨ����- 1; 0~3 for 1-4; 4-7 for 5-8; 8-11 for 9-12 ....  
    EM_BIZPREVIEW_6SPLITS = 6, //nModePara=0~�����Ƶͨ���� - 1; 0~5 for 1-6; 6-11 for 7-12 ��nModePara ����ͨ����
    EM_BIZPREVIEW_8SPLITS = 8, //����EM_BIZPREVIEW_6SPLITS
    EM_BIZPREVIEW_9SPLITS = 9, //����EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_10SPLITS = 10, //����EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_12SPLITS = 12, //����EM_BIZPREVIEW_6SPLITS
    EM_BIZPREVIEW_13SPLITS = 13, //����EM_BIZPREVIEW_6SPLITS
    EM_BIZPREVIEW_16SPLITS = 16, //����EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_25SPLITS = 24,
    EM_BIZPREVIEW_24SPLITS = 25, //����EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_36SPLITS = 32, //����EM_BIZPREVIEW_6SPLITS
    EM_BIZPREVIEW_32SPLITS = 36, //����EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_64SPLITS = 64, //����EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_PIP = 254, //
} EMBIZPREVIEWMODE; //Ԥ�����ڷָ�ģʽ

typedef struct
{
    EMBIZPREVIEWMODE emBizPreviewMode; //Ԥ�����ڷָ�ģʽ
    u8 nModePara; //extend parameter for EMBIZPREVIEWMODE
} SBizPreviewPara;

typedef struct
{
    u8 nIsPatrol; //��Ѳ�Ƿ�����(����:0=��;1=��)
    u8 nInterval; //��Ѳ�л�ʱ��(����:��λ��s)
    u8 nPatrolMode; //��Ѳʱ���õ�Ԥ��ģʽ(����:�ο�Mode)
    u8 nStops; //��Ѳվ��(����:һ���ֻ�ͣ������)
    u8 pnStopModePara[255]; //��Ѳÿվ��ʹ�õ�Ԥ����չ����(�����б�:�ο�ModePara)
} SBizCfgPatrol;

//һ��������Ѳ
void CPageStartFrameWork::OnClkStartBtn()  ��Ѳ�������ڽ���
	//�ֶ�������Ѳ
	ControlPatrol(m_bPatrol);
	|	BizStartPatrol() or BizStopPatrol()
	|		PreviewStartPatrol();
	|			ModPreviewStartPatrol()ת������
	|
	psPara.nIsPatrol = m_bPatrol;
	BizSetIsPatrolPara(&psPara, 0);
	|	memcpy(g_ConfigAllPara.psPreviewPara, para, sizeof(SModConfigPreviewParam));
	SetDwellStartFlag(1);
	|	nIsDwellStart = flag;//1
	m_pPageChnSel->SetCurDwellStatue(1);
		int CPageChnSelect::SetCurDwellStatue(int flag)
		{
			m_nIsDwell = flag;
		}
				
void ControlPatrol(u8 nEnable)
{
	if(nEnable)
	{
		BizStartPatrol();
	}
	else
	{
		BizStopPatrol();
	}
}
s32 ModPreviewStartPatrol(void)
{
    pthread_mutex_lock(&g_sPreviewManager.lock);

    g_sPreviewManager.sPatrolPara.nIsPatrol = 1;
    g_sPreviewManager.nIsPatrolParaChange = 1;
    
    pthread_mutex_unlock(&g_sPreviewManager.lock);
    
    return 0;
}

void* ModeCtrlFxn(void* arg)
{
	......
	ModPatrolNext();
	......
}
ModPatrolNext()
	ModPreviewStart()
		tl_preview()
		

�������Ʋ���
typedef struct
{
    u8 nIsPatrol; //��Ѳ�Ƿ�����(����:0=��;1=��)
    u8 nInterval; //��Ѳ�л�ʱ��(����:��λ��s)
    u8 nPatrolMode; //��Ѳʱ���õ�Ԥ��ģʽ(����:�ο�Mode)
    //u8 nStops; //��Ѳվ��(����:һ���ֻ�ͣ������)
    //u8 pnStopModePara[255]; //��Ѳÿվ��ʹ�õ�Ԥ����չ����(�����б�:�ο�ModePara)
} SBizCfgPatrol;

sPatrolPara.emPreviewMode = psPara->nPatrolMode;  1 4 9 16

DoBizSetPara--EM_BIZ_PATROLPARA
	ConfigSetCfgPatrol()
		PreviewSetPatrol()
			ModPreviewSetPatrol()
			
s32 PreviewSetPatrol(SPreviewPatrolPara* psPatrolPara)
{
    return ModPreviewSetPatrol(psPatrolPara);
}

����Ԥ�����
EventPreviewFreshDeal()
Ԥ����ʽ�ĸı�ᴥ�����øú���������Ԥ��ͨ����Ŀ�ĸı䡢˫��ͨ���Ŵ󡣡���
Ԥ��ͨ����Ŀ�ĸı�� ��ͼ����������޸Ŀ��Է��ڸô�
EM_PREVIEW_HideItem = 253,//���ؿؼ�
����˫��--16�����л���1����
PageDesktop.cpp:
	MsgProc():  XM_LBUTTONDBLCLK
		emCurPreviewMode = EM_BIZPREVIEW_1SPLIT;
		m_pPageStart->SinglePreview(TRUE);
		
		SetCurPreviewMode_CW(emCurPreviewMode);//������ģʽ
		SwitchPreview(emCurPreviewMode, nClikChn);//Ҫ�Ŵ��ͨ������������������õ�
		
			BizStartPreview(&sBPP);
				PreviewStart()
					ModPreviewStart(&sPreviewPara);
						g_sPreviewManager.nIsModeChange = 1;
						tl_preview(PREVIEW_1D1, nFirstChn);
							adjust_vo_ch_attr()
						
					//����ָ����ػ�
					ModeCtrlFxn(void* arg)
						if (g_sPreviewManager.nIsModeChange)
						g_sPreviewManager.sInitPara.pfnPreviewCb(&sPreviewPara);	
						PreviewEventDeal
							SendBizEvent
								DealCmdWithoutMsg
								g_sBizManager.sBizPara.pfnBizEventCb
								EventPreviewFreshDeal		
			
��������
testUI.cpp:
	main()
		Initialize()
			BizStartPreview(&sBPP);
					
					
��ʱˢ��ͨ��������Ϣ  kbps
PageDesktop.cpp
	m_DeskStreamTimer->Start(this, (VD_TIMERPROC)&CPageDesktop::ShowDeskStreamInfo, 1000,1000);
		
�ײ�ʹ�õ�ͨ����(VDEC & VO 64·�����ʹ��)
