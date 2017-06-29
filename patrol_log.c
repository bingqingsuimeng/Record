一、轮巡相关
//for SBizPreviewPara.emBizPreviewMode /SBizPreviewData
typedef enum
{
    EM_BIZPREVIEW_1SPLIT = 1,
    EM_BIZPREVIEW_4SPLITS = 4, //nModePara=0~最大视频通道数- 1; 0~3 for 1-4; 4-7 for 5-8; 8-11 for 9-12 ....  
    EM_BIZPREVIEW_6SPLITS = 6, //nModePara=0~最大视频通道数 - 1; 0~5 for 1-6; 6-11 for 7-12 ；nModePara 大画面通道号
    EM_BIZPREVIEW_8SPLITS = 8, //类似EM_BIZPREVIEW_6SPLITS
    EM_BIZPREVIEW_9SPLITS = 9, //类似EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_10SPLITS = 10, //类似EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_12SPLITS = 12, //类似EM_BIZPREVIEW_6SPLITS
    EM_BIZPREVIEW_13SPLITS = 13, //类似EM_BIZPREVIEW_6SPLITS
    EM_BIZPREVIEW_16SPLITS = 16, //类似EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_25SPLITS = 24,
    EM_BIZPREVIEW_24SPLITS = 25, //类似EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_36SPLITS = 32, //类似EM_BIZPREVIEW_6SPLITS
    EM_BIZPREVIEW_32SPLITS = 36, //类似EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_64SPLITS = 64, //类似EM_BIZPREVIEW_4SPLITS
    EM_BIZPREVIEW_PIP = 254, //
} EMBIZPREVIEWMODE; //预览窗口分割模式

typedef struct
{
    EMBIZPREVIEWMODE emBizPreviewMode; //预览窗口分割模式
    u8 nModePara; //extend parameter for EMBIZPREVIEWMODE
} SBizPreviewPara;

typedef struct
{
    u8 nIsPatrol; //轮巡是否启用(数字:0=否;1=是)
    u8 nInterval; //轮巡切换时间(数字:单位秒s)
    u8 nPatrolMode; //轮巡时所用的预览模式(数字:参考Mode)
    u8 nStops; //轮巡站数(数字:一个轮回停几个点)
    u8 pnStopModePara[255]; //轮巡每站所使用的预览扩展参数(数字列表:参考ModePara)
} SBizCfgPatrol;

//一、开启轮巡
void CPageStartFrameWork::OnClkStartBtn()  轮巡开关所在界面
	//手动开启轮巡
	ControlPatrol(m_bPatrol);
	|	BizStartPatrol() or BizStopPatrol()
	|		PreviewStartPatrol();
	|			ModPreviewStartPatrol()转到下面
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
		

二、控制参数
typedef struct
{
    u8 nIsPatrol; //轮巡是否启用(数字:0=否;1=是)
    u8 nInterval; //轮巡切换时间(数字:单位秒s)
    u8 nPatrolMode; //轮巡时所用的预览模式(数字:参考Mode)
    //u8 nStops; //轮巡站数(数字:一个轮回停几个点)
    //u8 pnStopModePara[255]; //轮巡每站所使用的预览扩展参数(数字列表:参考ModePara)
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

二、预览相关
EventPreviewFreshDeal()
预览方式的改变会触发调用该函数，比如预览通道数目的改变、双击通道放大。。。
预览通道数目的改变后 对图标和码流的修改可以放在该处
EM_PREVIEW_HideItem = 253,//隐藏控件
桌面双击--16画面切换到1画面
PageDesktop.cpp:
	MsgProc():  XM_LBUTTONDBLCLK
		emCurPreviewMode = EM_BIZPREVIEW_1SPLIT;
		m_pPageStart->SinglePreview(TRUE);
		
		SetCurPreviewMode_CW(emCurPreviewMode);//单画面模式
		SwitchPreview(emCurPreviewMode, nClikChn);//要放大的通道，由鼠标点击区域计算得到
		
			BizStartPreview(&sBPP);
				PreviewStart()
					ModPreviewStart(&sPreviewPara);
						g_sPreviewManager.nIsModeChange = 1;
						tl_preview(PREVIEW_1D1, nFirstChn);
							adjust_vo_ch_attr()
						
					//桌面分割线重绘
					ModeCtrlFxn(void* arg)
						if (g_sPreviewManager.nIsModeChange)
						g_sPreviewManager.sInitPara.pfnPreviewCb(&sPreviewPara);	
						PreviewEventDeal
							SendBizEvent
								DealCmdWithoutMsg
								g_sBizManager.sBizPara.pfnBizEventCb
								EventPreviewFreshDeal		
			
开机启动
testUI.cpp:
	main()
		Initialize()
			BizStartPreview(&sBPP);
					
					
定时刷新通道带宽信息  kbps
PageDesktop.cpp
	m_DeskStreamTimer->Start(this, (VD_TIMERPROC)&CPageDesktop::ShowDeskStreamInfo, 1000,1000);
		
底层使用的通道号(VDEC & VO 64路解码板使用)
