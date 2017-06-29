DiskInfoUpdate.cpp:
	modSysCmplx_StorgeNotify(&sStoreMgr, EM_SYSEVENT_DISKCHANGED, 0);
	
s32 modSysCmplx_StorgeNotify(
	SStoreDevManage *psMgr,
	s32 	evt,
	s32 	emRslt
)
{
	PFNSysNotifyCB 	pCb;
	SEventPara		sEvPara;
	
	if(NULL != psMgr)
	{
		memcpy(&sEvPara.sStoreMgr, psMgr, sizeof(sEvPara.sStoreMgr));
	}
	else
	{
		sEvPara.emResult = emRslt;
	}
	pCb = sModSysIns.pFNSysNotifyCB;
	EvNotify(pCb, evt, &sEvPara);
	
	return 0;	
}

mod_syscomplex.c
	s32 ModSysComplexInit( PSModSysCmplxInit pSysCmplxInit )
	{
		psModSysCplx->pFNSysNotifyCB = pSysCmplxInit->pSysNotifyCB;
	}
	
biz_syscomplex.c : 
	s32 SysComplexInit(u8 nEnable, SBizSysComplex* psInitPara)
	{
		......
		SModSysCmplxInit sModSysCmplx;
		sModSysCmplx.pDMHdr 		= psInitPara->hddHdr;
		sModSysCmplx.pSysNotifyCB 	= SysComplexEventDeal;
		sModSysCmplx.pUpTimeCB 		= SysComplexDataTimeTick;
		sModSysCmplx.pSysResetCB 	= sysComplex_resetcb;
		sModSysCmplx.pStopRecCB		= sysComplexStopRecCB;
		sModSysCmplx.pResumeRecCB	= sysCompleResumeRecCB;        
		sModSysCmplx.pDisablePanelCB = FrontBoardEnable;
		sModSysCmplx.pGetLogoSizeCB	= GetJpgSize;
		sModSysCmplx.nTimeZone = sysPara.nTimeZone;//csp modify 20131213
		
		ret = ModSysComplexInit(&sModSysCmplx);
		......
	}


void SysComplexEventDeal(EMSYSEVENT emSysEvent, SEventPara *psEventPara)
{
    if (psEventPara)
    {
        SBizEventPara sBizEventPara;
        
        switch (emSysEvent)
        {
        	......
        	case EM_SYSEVENT_SATARELOAD:
			case EM_SYSEVENT_DISKCHANGED:
				sBizEventPara.emType = (emSysEvent == EM_SYSEVENT_SATARELOAD) ? EM_BIZ_EVENT_SATARELOAD : EM_BIZ_EVENT_DISKCHANGED;
				sBizEventPara.sStoreMgr.nDiskNum = psEventPara->sStoreMgr.nDiskNum;
				sBizEventPara.sStoreMgr.psDevList = psEventPara->sStoreMgr.psDevList;
			break;
        	......
        }
        SendBizEvent(&sBizEventPara);
	}
}

biz_manager.c
s32 SendBizEvent(SBizEventPara* psBizEventPara)
{
    if (NULL == psBizEventPara)
    {
        return BIZ_ERR_EVENT_NULL;
    }
	
    return DealCmdWithoutMsg(psBizEventPara);
    //return SendBizInnerMsgCmd(EM_BIZMSG_EVENT_CB, (void *)psBizEventPara);
}

s32 DealCmdWithoutMsg(SBizEventPara* sBizEventPara)
{
	if(NULL == sBizEventPara)
	{
		return -1;
	}
	
	return g_sBizManager.sBizPara.pfnBizEventCb(sBizEventPara);
}

BizData.cpp
	sBizInitPara.pfnBizEventCb = BizEventCB;
	BizInit(&sBizInitPara);
	
void CPageBasicConfigFrameWork::RecvNotifyClose()	//Ô¾Ìì½âÂë°åCMS remote CTRL
	
page[EM_PAGE_BASICCFG]->UpdateData(UDM_GUIDE);
page[EM_PAGE_BASICCFG]->Open();
	
((CPageShenGuangConfig*)g_pPages[EM_PAGE_SG_PLATFORM])->Open();
((CPageShenGuangConfig*)g_pPages[EM_PAGE_SG_PLATFORM])->RecvNotify(chn, ErrVal);

{CTRL_CMD_CLOSE_GUIDE, DealRemoteCmd_CloseGuide},

s32 netComm_NotifySGuploadState(u32 chn, EM_MSG_TYPE type, u8 bState )
{
	SNetStateNotify sNotify;

	if (!bModInited )//|| (time(NULL) - inittime < 2*60 ) )
		return 1;

	printf("%s type: %d\n", __func__, type);
	
	memset(&sNotify, 0, sizeof(sNotify));
	
	sNotify.eAct 		= EM_NET_STATE_SG;EM_NET_STATE_REMOTE_CLOSE_GUIDE
	sNotify.sRslt.state 	=  chn;
	sNotify.sRslt.nErr 	= bState;

	if (pNotify != NULL)
	{
		if ( (type == EM_PIC_MAINTAIN_UPLOAD) 
			|| (type == EM_PIC_TEST_UPLOAD)
			|| (type == EM_PIC_ACCEPT_UPLOAD) 
			|| (type == EM_REPAIR_CHECK)
			|| (type == EM_MAINTAIN_CHECK) 
			|| (type == EM_VideoMonitor_Fault)
			//||((type >= EM_SYS_Other) && (type <= EM_ElectronicPatrol_Fault))
			)
		{
			pNotify((void*)&sNotify);
		}
	}
	
	return 0;
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	