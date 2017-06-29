//yaogang modify for remote preview thread per chn
#define REMOTE_PREVIEW_THREAD_PER_CHN

#ifdef REMOTE_PREVIEW_THREAD_PER_CHN
	
#else
	
#endif

一、SDK端
//1、添加命令 用在 send_command()
ctrlprotocol.h
eg:
	#define CTRL_CMD_GETSEACHIPCLIST		CTRL_CMD_BASE+162
	
//2、添加函数 提供给上层应用调用
netdvr.h 所需数据结构也在此定义
eg:
	struct NETDVR_ipcSearch
	{
		unsigned short sum;						//total records of found logs
		unsigned short startID;					//if no file is indexed, startID will be 0, or it'll be a value based on index condition's startID(struct NETDVR_logSearchCondition_t)
		unsigned short endID;					//结束的记录,基址为1.当endID和startID相等时,表示之返回一条记录
	
		struct NETDVR_ipcInfo *pIPC;
	};
	
int __stdcall NETDVR_seachIPCList(int Handle,NETDVR_ipcSeachCondition *ipcS,NETDVR_ipcSearch *p_para);

netdvr.def 定义函数调用号
eg:
	NETDVR_seachIPCList					@188
	
//3、调试 打开控制台
int __stdcall NETDVR_startup(void)
{
	......
#if 1
	AllocConsole();
	int nRet = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	FILE* fp = _fdopen(nRet, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("控制台输出\n");
#endif
	......
}


二、NVR端
//1、数据结构
ctrlprotocol.h 同上
	#define CTRL_CMD_GETSEACHIPCLIST		CTRL_CMD_BASE+162
	typedef struct
	{
		u16		sum;						//总记录数		
		u16		startID;					//开始的记录,基址为1.当无返回数据时,startID的值为0		
		u16		endID;						//结束的记录,基址为1.当endID和startID相等时,表示之返回一条记录		
	}PACK_NO_PADDING ifly_search_desc_t;

Cmdcallback.h
远程命令结构
typedef struct _sRemoteCmd
{
	// ctrlpotocol handle
	CPHandle 	cph;

	// parameter
	union
	{
		u8						nAlarmInId;
		u8						nChn;
		u8						nAlarmUpload;
		u8						nHddIdx;
		SCmdPPPOE 				sCmdPoeIns;
		SCPRecSch				sCPRecSch;
		ifly_cp_dhcp_t 			cp_dhcp;
		ifly_loginpara_t 		loginpara;
		ifly_RecordParam_t		RecordParam;
		ifly_SubStreamParam_t 	SubStreamParam;
		ifly_ImgParam_t 		ImgParam;
		ifly_PicAdjust_t 		PicAdjust;
		ifly_AlarmInParam_t 	AlarmInParam;
		ifly_AlarmOutParam_t	AlarmOutParam;
		ifly_AlarmNoticeParam_t	AlarmNoticeParam;
		ifly_AlarmEmail_SMTP_t	AlarmEmail_SMTP;
		ifly_recsearch_param_t 	recsearch_param;
		ifly_VideoBlockParam_t	VideoBlockParam;

		ifly_reset_picadjust_t 	reset_picadjust;
		ifly_framerate_list_t 	framerate_list;
		ifly_videoresolu_list_t videoresolu_list;
		ifly_SysParam_t 		SysParam;
		ifly_RecordSCH_t 		RecordSCH;
		ifly_MDParam_t 			MDParam;
		ifly_VideoLostParam_t 	VideoLostParam;
		ifly_NetWork_t 			NetWork;
		ifly_PTZParam_t 		PTZParam;
		ifly_PtzPresetCtr_t 	PtzPresetCtr;
		ifly_PtzCruisePathParam_t PtzCruisePathParam;
		ifly_CruisePathCtr_t 	CruisePathCtr;
		ifly_TrackCtr_t		 	TrackCtr;
		ifly_userMgr_t 			userMgr;
		ifly_sysTime_t 			sysTime;
		ifly_PtzCtrl_t 			PtzCtrl;
		ifly_ManualRecord_t 	ManualRecord;
		ifly_search_log_t 		search_log;
		ifly_RecSchTime_t		RecSchTime;
		//xdc
		ifly_search_ipc_t		search_ipc;
		ifly_ipc_info_t			ipc_info;
	} PACK_NO_PADDING sReq;
	
} PACK_NO_PADDING SRemoteCmdReq, *PSRemoteCmdReq;

调用模块填充必要信息给网络模块
sBasicInfo - 基本信息
sExtInfo   - 补充信息

typedef struct _sRemoteCmdRslt
{
	// 是否使用补充信息
	BOOL bUseExt;
	
	// 获取/设置/控制的结果
	// CTRL_SUCCESS 成功，其他未成功相应的错误状态
	u32  nErrCode;

	// basicinfo length
	u32 nBasicInfoLen;
	union
	{
		u8						nChn;
		SCPRecFile				sRecFile;
		SCPLogInfo				sLogInfo;
		SMaxMaskNum				sMaxMskNum;
		ifly_sysparam_t			sysparam;
		// get login info
		SRemoteUserInfo			sUserInfo;
		ifly_DeviceInfo_t 		DeviceInfo;
		ifly_Video_Property_t 	Video_Property;
		ifly_Audio_Property_t 	Audio_Property;
		ifly_VOIP_Property_t 	VOIP_Property;
		ifly_MD_Property_t 		MD_Property;
		ifly_network_t			netInfo;
		ifly_VGA_Solution 		VGA_Solution;
		ifly_SysLangList_t 		SysLangList;
		ifly_SysParam_t 		SysParam;
		ifly_RecordParam_t 		RecordParam;
		ifly_bitRateList_t		bitRateList;
		ifly_SubStreamParam_t 	SubStreamParam;
		ifly_ImgParam_t 		ImgParam;
		ifly_PicAdjust_t 		PicAdjust;
		ifly_AlarmInParam_t 	AlarmInParam;		
		ifly_AlarmOutParam_t	AlarmOutParam;
		ifly_AlarmNoticeParam_t	AlarmNoticeParam;
		ifly_AlarmEmail_SMTP_t	AlarmEmail_SMTP;
		ifly_userNumber_t		userNumber;
		ifly_VideoBlockParam_t	VideoBlockParam;
		ifly_framerate_list_t 	framerate_list;
		ifly_videoresolu_list_t videoresolu_list;
		ifly_RecordSCH_t 		RecordSCH;
		ifly_MDParam_t 			MDParam;
		ifly_VideoLostParam_t 	VideoLostParam;
		ifly_PTZParam_t 		PTZParam;
		ifly_PtzCruisePathParam_t PtzCruisePathParam;
		ifly_hddInfo_t 			hddInfo;
		ifly_sysTime_t 			sysTime;
		ifly_ManualRecord_t 	ManualRecord;
		ifly_utctime_t 			utctime;
		ifly_sysinfo_t			sysinfo;
		ifly_MDSenselist_t 		MDSenselist;
		ifly_MDAlarmDelaylist_t MDAlarmDelaylist;
		ifly_BaudRateList_t 	BaudRateList;
		ifly_PTZProtocolList_t	PTZProtocolList;
		ifly_RecSchTime_t		RecSchTime;
		//xdc
		SCPIpcInfo				sIpcInfo;
	} sBasicInfo;
	
} PACK_NO_PADDING SRemoteCmdRslt, *PSRemoteCmdRslt;

//2、NVR处理流程
CheckConnTaskProc() 未运行

s32 NetCommInit( PSNetCommCfg pCfg )
{
	printf("NetCommInit......\n");
	pthread_t netThread;
	return pthread_create(&netThread, NULL, NetCommInitThxd, (void*)pCfg);
}

void* NetCommInitThxd( void* para )
{   ...
	SetMsgCallBack(DealCommand, NULL);
	...
	CPLibInit(nServerPort);
}

void SetMsgCallBack(pMESSAGE_CB pCB,void *pContext)
{
	pfuncMsgCB = pCB;
	pCallBackContext = pContext;
}

u16 CPLibInit(u16 wPort)
{	
	...
	hServerSock = socket(AF_INET,CTRL_PROTOCOL_TYPE,0);//供远程客户端连接
	...
	hCPTask = IFly_CreateThread(CPTaskProc,NULL,PRI_CP,STKSIZE_CP,0,0,NULL);//接收客户连接并响应需求
	...
}

void *CPTaskProc(void *pParam) 线程//ctrlprotocol.c
{
	...
	FD_ZERO(&set);
	if(hServerSock != INVALID_SOCKET) FD_SET(hServerSock,&set);
	for(i=0;i<CTRL_PROTOCOL_MAXLINKNUM;i++)
	{
		if(hCPLink[i].sockfd != INVALID_SOCKET)
		{
			FD_SET(hCPLink[i].sockfd,&set);
		}
	}
	if(hInterSock != INVALID_SOCKET) FD_SET(hInterSock,&set);
	...
	if(pfuncMsgCB != NULL)
	{
		g_dwAckLen = sizeof(g_byAckBuf)-sizeof(ifly_cp_header_t);
		
		wRet = pfuncMsgCB(&hCPLink[i],cprcvhead.event,abyBuf+sizeof(ifly_cp_header_t),\
								cprcvhead.length-sizeof(ifly_cp_header_t),\
								g_byAckBuf+sizeof(ifly_cp_header_t),&g_dwAckLen,pCallBackContext);	
	}
	
}
//CmdProc.c
u16 DealCommand(
	CPHandle 	cph,
	u16 		event,
	u8*			pbyMsgBuf,
	int 		msgLen,
	u8*			pbyAckBuf,
	int*		pAckLen,
	void* 		pContext
)
{
	......
	//通过event找到响应的处理函数，具体的响应函数在ExcuteCmd.c
	pCB = cmdProc_GetCmdCB(event);
	......
	switch (event)
	{
		......
		case CTRL_CMD_GETADDIPCLIST:
			......
			(*pCB)(&sReqIns, &sRslt);
			......
			break;
		......
	}
	
}

PNetCommCommandDeal cmdProc_GetCmdCB(u32 nCmdID)
{
	int i;

	SCmdCBPair* pCmdPair = sCmdCBStack;
			
	for(i=0;i<CMD_CB_MAX;i++)
	{
		if(pCmdPair[i].nCmdID==nCmdID)
		{
			return pCmdPair[i].pCB;
		}
	}

	return NULL;
}
sCmdCBStack 中记录的回调函数由 NetCommRegCmdCB()函数注册
s32 NetCommRegCmdCB( u32 nCmdID, PNetCommCommandDeal pCB )
{
	int i;

	SCmdCBPair* pCmdPair = sCmdCBStack;
	
	for(i=0;i<CMD_CB_MAX;i++)
	{
		if(pCmdPair[i].nCmdID==0)
		{
			//NETCOMM_DEBUG_STR("Register on callback, id", nCmdID);
			
			pCmdPair[i].nCmdID 	= nCmdID;
			pCmdPair[i].pCB		= pCB;

			break;
		}
	}
	......
}

void bizNet_ExcmdRegCB()//注册
{
	int i;
	for(i=0; i<sizeof(pNetCmdCB)/sizeof(pNetCmdCB[0]); i++)
	{
		if( pNetCmdCB[i].pCB )
			NetCommRegCmdCB( pNetCmdCB[i].nCmdID, pNetCmdCB[i].pCB );
	}
	......
}

网络命令处理回调函数指针
SCmdCBPair pNetCmdCB[] = {
	......
	{CTRL_CMD_GETSEACHIPCLIST,DealRemoteCmd_Ipcsearch},
	{CTRL_CMD_GETADDIPCLIST,DealRemoteCmd_GetAddIpcList},
	......
}

远程升级 -- 流程
CPTaskProc()
	else if(0x2 == Conntype)
		pAddStreamLinkCB()
		
AddStreamTCPLink()
	netComm_DealStreamCmd()
		remoteUpdate_Request()
			remoteUpdate_CheckCurStatus() -- pStopRecCB() -- sysComplexStopRecCB() 录像关闭
			remoteUpdateFxn() -- thread


		
远程请求码流  
外部设备连接登录 NVR/DEC 流程
app:
int CheckConnectServer(DevEquipments_s &DevEquipment, bool bCheckMessage)
	int NETDVR_createDVRbyDomain(int *p_handle, char *pDomain, unsigned short serverport)
	NETDVR_loginServer
	NETDVR_regCBAlarmState
	NETDVR_SetAlarmUpload
	
	
SDK:
int NETDVR_createDVR(int *p_handle,unsigned int serverip, unsigned short serverport)
	CPHandle CPConnect(u32 dwServerIp, u16 wServerPort, u32 dwTimeOut, u16 *pwErrorCode)
		CPHandle AddCPLink(SOCKHANDLE hSock,u8 conntype,u32 ip,u16 port,u16 *pwErrorCode)
		hCPLink[i].sockfd = hSock;
			void *CPTaskProc(void *pParam)
			FD_SET(hCPLink[i].sockfd,&set);

以预览为例：
客户端：
void CMonitorDlg::DeviceTreeMouseMsgCBFunc(enum TreeMouseMsg msg, unsigned int dwContent)
	case MOUSE_LDbClk:
		SelectDevicePlay(DevEquipment,dwItemData,dwContent);//yaogang start preview
			pThis->Preview(DevEquipment.DeviceHandle.nHandle, DevEquipment.strNodeName, chn,DevEquipment.DeviceHandle.byStreamType,false);
				PrewViewByPlayWnd(m_DlgPreview.GetCurrentActiveWnd(), handle, devicename, chn, streamtype,bLoopPlay,hItemGroup);
					NETDVR_StartRealPlay(handle, &rpCi, &m_PlayWndInfo[dwPlayWndIndex].hRealHandle);

SDK:					
int NETDVR_StartRealPlay( int Handle, const struct RealPlayClientInfo_t* pClientinfo, int* pRealPlayHandle )
	pMonitor->video_rcv.req.command = 0;//0：预览，1：文件回放，2：时间回放，3：文件下载，4：升级
	pMonitor->video_rcv.req.Monitor_t.chn = pClientinfo->rcv_chn;
	pMonitor->video_rcv.req.Monitor_t.type = 2;//0：主码流视频，1：主码流音频，2：子码流视频
	//请求主码流
	pMonitor->video_rcv.req.reserved[0] = pClientinfo->wnd_num;
	pMonitor->video_rcv.req.reserved[1] = pClientinfo->wnd_index;
	pMonitor->video_rcv.req.reserved[6] = 0x5A;
	//请求子码流
	pMonitor->video_rcv.req.reserved[0] = 0;
	pMonitor->video_rcv.req.reserved[1] = 0;
	pMonitor->video_rcv.req.reserved[6] = 0;

	SetRcvTcpFrame()
		AddStreamConnect()
			StartStreamConnect()
				SendTcpConnHead(prcv_t->sockfd, 0x2);//medialink
	
	*pRealPlayHandle = (int)pMonitor;
	
				
	码流接收线程
		RcvTcpFrameThread() 写入解码队列g_decmsgQ
		
	解码线程
		DecVideoFrameThread()

	
//码流接收线程(预览和回放的码流都在此)
DWORD WINAPI RcvTcpFrameThread(LPVOID lpParam) --》收到码流后写缓冲 GetMsgQWriteInfo()
	DecVideoFrameThread()线程读缓冲
		DealMediaFrame() 处理帧 解码后回调pDecFrameCBFunc(上层给出的解码后的回调处理函数)
		

数据结构
struct RealPlayClientInfo_t
{
	unsigned char	rcv_chn; //channel
	unsigned char	streamtype; //0 main stream, 1 substream
	pFrameCallBack	pEncFrameCBFunc; //Call back function to encode
	unsigned int	dwEncFrameContent; //Context for encoder callback function to identify play reciever
	pDecFrameCallBack	pDecFrameCBFunc; //Call back function to decode
	unsigned int	dwDecFrameContent; //Context for decoder callback function to identify play reciever
	//csp modify 20130423
	unsigned char	wnd_num;
	unsigned char	wnd_index;
	unsigned char	reserved[6];
};

struct ifly_monitor_t
{
	u8 channel;
	void* pDeviceHandle;
	struct IFLY_MediaRcvPara_t video_rcv;
	struct IFLY_MediaRcvPara_t audio_rcv;
	struct IFLY_RecordPara_t record_para;
	struct IFLY_RecordPara_t record_para2;
	struct IFLY_Snapshot_t snap_shot;
	struct ifly_monitor_t* pNext;
};
	
NVR端
1、初始化
s32 NetInit(void* pHddHdr, SNetSysPara* pPara)
{
	......
	sNCCfg.pReqKeyCB 			= NULL;
	sNCCfg.pReqStreamCB 		= bizNet_RequestPreviewCB;
	sNCCfg.pRpCB 				= bizNet_remoteplayCB;
	sNCCfg.pVOIPIn 				= NULL;
	sNCCfg.pVOIPOut 			= NULL;
	......
}

void* NetCommInitThxd( void* para )
{
	......
	PStreamRequestCB 	pCB 		= pCfg->pReqStreamCB;
	PRequestKeyFrameCB 	pReqKeyCB  	= pCfg->pReqKeyCB;
	PRemotePlayCB 		pRpCB 		= pCfg->pRpCB;
	PNetCommVOIPOut 	pVOIP 		= pCfg->pVOIPOut;
	PNetCommVOIPIn 		pVOIPIn  	= pCfg->pVOIPIn;
	......
	
	if( remotePreview_Init( pCfg->yFactor,
							pNCCIns->nChnTcpStreamNum, 
							nVidStreamNum, 
							nAudStreamNum,
							pCfg->nVoipMode,
							pCfg->nAudioMediaType,
							pCfg->nVideoMediaType,
							pCB,
							pReqKeyCB,
							pVOIP,
							pVOIPIn )
	)
}

s32 remotePreview_Init(
			u32 yFactor,
			u16 nStreamTcpNum,
			u16 nVidTcpNum,
			u16 nAudTcpNum,
			u8  nVoipModeIns,
			u8  nAudioMediaType,
			u8  nVideoMediaType,
			PStreamRequestCB pFxn,
			PRequestKeyFrameCB pReqKeyCB,
			PNetCommVOIPOut pVOIP,
			PNetCommVOIPIn pVOIPIn
)
{
	......
	pCtrl->pRmtPrvwCB = pFxn;
	pCtrl->pReqKeyCB	= pReqKeyCB; //NULL
	pCtrl->pVOIPCB		= pVOIP; //NULL
	pCtrl->pVOIPCBIn	= pVOIPIn; //NULL
	
	// allocate memory for ctrl blocks
	pCtrl->nStreamTcpNum = nStreamTcpNum;
	pCtrl->nAudTcpNum = nAudTcpNum;
	pCtrl->nVidTcpNum = nVidTcpNum;
	pCtrl->nVoipMode  = nVoipModeIns;
	pCtrl->nVideoMediaType = nVideoMediaType;
	pCtrl->nAudioMdType = nAudioMediaType;
	......
}

//debug printf
NetCommInitThxd:nAudStreamNum=16,nVidStreamNum=16,nTotalLinkNum=167,nChnMax=16
#############################initMsgQ bufnum 6 chnnum 16 framesizemax 520192 MsgQLen 16646144
nAudTcpNum 16 nVidTcpNum 16 nStreamTcpNum 16


2、接受远程数据连接
CPTaskProc()
	SetSockLinkOpt()  TCP_NODELAY & SO_LINGER
	else if(0x2 == Conntype) //accept medialink success
	
	pAddStreamLinkCB() -- AddStreamTCPLink()
		netComm_DealStreamCmd()
			remotePreview_Request()
				bSubStream = 1;
				sReq.nType = EM_PREQ_SUB;
				
				SRmtPrvwCtrl* pCtrl = &sRmtPrvwIns;
				PSNCSSCtrl pStmSndCtrl = &pCtrl->psVidTcpCtrl[chn];
				SNCSSCtrl1Link*	pLnkCtrl = &pStmSndCtrl->sLinkCtrl[j];
				
				netComm_Ack(0, sock, nId);
				remotePreview_InitLinkNode(pLnkCtrl, sock, bSubStream, nId, MonitorInfo))
					pLnkCtrl->streamtype = bSubStream?2:0;
					pLnkCtrl->m_dwFrameId		= 0;
					pLnkCtrl->m_dwsubFrameId	= 0;
					pLnkCtrl->bSub				= bSubStream;
					
					//csp modify 20130423
					pLnkCtrl->VMonitorInfo		= MonitorInfo;
					pLnkCtrl->m_dwThirdFrameId	= 0;
					
					pLnkCtrl->sockfd			= sock;
					pLnkCtrl->nLinkId			= nId;
					
					
//码流
IPC_RegisterCallback(DealRealStream, DealStreamState);注册回调
	DealRealStream()
		WriteFrameToVencMainQueue(stream) //主码流
			plib_gbl_info->pMainStreamCB(&out_stream);
				DealMainStream(venc_stream_s *stream)
					g_s_EncodeManager.sChnMainManage.psChnObj[chn].sChnInfo.pfnEncodeProc(&sEncodeHead, nContent);
			
		WriteFrameToVencSubQueue(stream) //子码流
			plib_gbl_info->pSubStreamCB(&out_stream);
				DealSubStream(venc_stream_s *stream)
					g_s_EncodeManager.sChnSubManage.psChnObj[chn].sChnInfo.pfnEncodeProc(&sEncodeHead, nContent);
				
			plib_gbl_info->pThirdStreamCB(&out_stream);
				DealThirdStream(venc_stream_s *stream)
					g_s_EncodeManager.sChnThirdManage.psChnObj[chn].sChnInfo.pfnEncodeProc(&sEncodeHead, nContent);

void EncodeDeal(SEncodeHead* psEncodeHead, u32 nContent)
{
	SBizEncodeData sBizEncData;
	sBizEncData.psEncodeHead = psEncodeHead;
	if(0 == ExtractDwContent(nContent, &sBizEncData.nChn, &sBizEncData.emChnType))//EM_CHN_VIDEO_SUB/EM_CHN_VIDEO_MAIN/EM_CHN_VIDEO_THIRD
	{
		//if(sBizEncData.nChn == 3 || sBizEncData.nChn == 19) printf("EncodeDeal:chn%d\n",sBizEncData.nChn);
		
		//SendBizInnerMsgCmd(EM_BIZMSG_ENCDATA, (void *)&sBizEncData);
		EncDataDispatch((SBizEncodeData*)&sBizEncData);
	}
}

//写入 帧缓冲
EncDataDispatch()
{
	EM_CHN_VIDEO_MAIN:
		sNetFrmHead.bSub = 0;
		sNetFrmHead.eFrameType = EM_VIDEO;
		
	EM_CHN_VIDEO_SUB:
		sNetFrmHead.bSub |= 0x2;
		sNetFrmHead.eFrameType = EM_VIDEO;
		
	EM_CHN_VIDEO_THIRD:
		sNetFrmHead.eFrameType = EM_THIRD;
				
		if(psBizManager->pnVideoThirdNetStatus[nChn])
		{			
			sNetFrmHead.bSub |= 0x2;
		}
		
		if(psBizManager->pnVideoThirdNetMbStatus[nChn])
		{
			sNetFrmHead.bSub |= 1;
		}
	......
	if(nStatusNet)
	{
		sNetFrmHead.byChnIndex 	= nChn;
		
		sNetFrmHead.dwlen 		= psEncHead->nLen;
		sNetFrmHead.timeStamp	= (u32)psEncHead->nTimeStamp;
		
		sNetFrmHead.byMediaType = psEncHead->emEncodeType; //EM_ENCODE_VIDEO_H264
		sNetFrmHead.byFrameType = (psEncHead->emVideoFrameType == EM_FRAME_TYPE_I?3:0);//key?1:0;
	}
		
}


//码流发送线程  读取帧缓冲  send client
RemotePreviewThread()
	GetMsgQReadInfo(pQue,&pBuf,&dwReadLen)//队列读取码流数据
	
	SRmtPrvwCtrl* pRmtPrvwCtrl = &sRmtPrvwIns;
	PSNCSSCtrl pVidSndCtrl = &pRmtPrvwCtrl->psVidTcpCtrl[chn];
	PSNCSSCtrl1Link	pLinkCtrl = &pVidSndCtrl->sLinkCtrl[j];
	
	wRet = SendMediaFrameByTcpFast(sFrameBuf, (SOCKHANDLE)pLinkCtrl->sockfd, &tVideoFRAMEHDR, 1);//发送
	
	skipReadMsgQ(pQue);//释放 队列读取码流数据




//g_s_EncodeManager.sChnMainManage.psChnObj[nChn]
psChnObj->sChnInfo.nContent = nContent;//(nChn << 16) | (emChnType & 0xffff);EM_CHN_VIDEO_MAIN, EM_CHN_VIDEO_SUB
psChnObj->sChnInfo.pfnEncodeProc = pfnEncodeCB;//EncodeDeal
psChnObj->sChnInfo.nStart = 1;
				




Playback File

struct NETDVR_recFileInfo_t
{
	unsigned char channel_no;				//the channel number of the record file
	unsigned char type;						//the record type of file
	unsigned int start_time;				//start time of the record file
	unsigned int end_time;					//end time of the record file
	unsigned char image_format;				//frame type:3(Pal-cif) ; 4(Pal-D1); 8(NTSC-cif); 9(NTSC-D1)
	unsigned char stream_flag;				//stream flag:0 for video flow ; 1 for audio flow
	unsigned int size;						//size of record file
	unsigned int offset;					//the file offset in dvr file pools
	char filename[64];						//name of record file
	struct NETDVR_recFileInfo_t *pnext;		//poiter reference to the next record file information
};

struct ifly_playback_t
{
	u8	playtype; //0 file 1 time
	void* pDeviceHandle;
	struct IFLY_Player_t player;
	MutexHandle player_lock;
	struct ifly_playback_t* pNext;
};



				