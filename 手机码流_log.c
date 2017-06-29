惠州项目NH-916，手机码流处理逻辑

void* ThirdStreamThrFxn(void* arg)
{
	int ret = tl_venc_third_read(pEncBuf, sizeof(pEncBuf), &venc_stream);
	lib_gbl_info.pThirdStreamCB(&venc_stream);
}

int DealThirdStream(venc_stream_s *stream)
{
	if(pfnEncodeProc != NULL)
	{
		pfnEncodeProc(&sEncodeHead, nContent);
	}
}

void EncodeDeal(SEncodeHead* psEncodeHead, u32 nContent)
{
	SBizEncodeData sBizEncData;
	sBizEncData.psEncodeHead = psEncodeHead;
	if(0 == ExtractDwContent(nContent, &sBizEncData.nChn, &sBizEncData.emChnType))
	{
		//if(sBizEncData.nChn == 3 || sBizEncData.nChn == 19) printf("EncodeDeal:chn%d\n",sBizEncData.nChn);
		
		//SendBizInnerMsgCmd(EM_BIZMSG_ENCDATA, (void *)&sBizEncData);
		//printf("EncDataDispatch EncDataDispatch\n");
		EncDataDispatch((SBizEncodeData*)&sBizEncData);
	}
}

s32 EncDataDispatch(SBizEncodeData* psBizEncData)
{
	case EM_CHN_VIDEO_THIRD://csp modify 20130423
	if(nChn < psBizManager->nVideoMainNum)
	{
	#if 1//csp modify 20140525
		nStatusNet = 0;
		sNetFrmHead.bSub = 0;
		sNetFrmHead.eFrameType = EM_THIRD;
		
		if(psBizManager->pnVideoThirdNetStatus[nChn])
		{
			nStatusNet |= 1;
			
			sNetFrmHead.bSub |= 0x2;
		}
		
		if(psBizManager->pnVideoThirdNetMbStatus[nChn])
		{
			nStatusNet |= 1;
			
			sNetFrmHead.bSub |= 1;
		}
	#else
		nStatusNet = 1;
		sNetFrmHead.bSub = 2;//0;//csp modify 20140318
		sNetFrmHead.eFrameType = EM_THIRD;
	#endif
	}
	break;
	
	NetCommSendPreviewFrame(&sNetFrmHead, (u8 *)psEncHead->pData);
}

s32 NetCommSendPreviewFrame(PSNetComStmHead pHead, u8* pBuf)
{
	if(pHead->bSub & 0x1)
	{
		//printf("chn%d mobile stream eFrameType=%d\n",pHead->byChnIndex,pHead->eFrameType);
		
		//csp modify 20140525
		//fill msg buf
		nDataLen = pHead->dwlen+sizeof(SNetComStmHead);
		
		//send to mobile monitor
		if(GetMsgQWriteInfo(&pNCCIns->netsndMbMsgQ, &pQBuf, &nDataLen))
		{
			memcpy(pQBuf, pHead, sizeof(SNetComStmHead));
			memcpy(pQBuf+sizeof(SNetComStmHead), pBuf, nDataLen);
			
			//post msg queue
			skipWriteMsgQ(&pNCCIns->netsndMbMsgQ);
			//NETCOMM_DEBUG_STR("GetMsgQWriteInfo success!!!", 0);
		}
		else
		{
			//usleep(5000);
			NETCOMM_DEBUG_STR("GetMsgQWriteInfo failed!!!", -1);
			
			return -1;
		}
	}
}

void* mb_StreamThread( void* param )
{
	GetMsgQReadInfo(&pNCCtrl->netsndMbMsgQ,&pBuf,&dwReadLen)
	
	mb_SendStream(&tVideoFRAMEHDR, chn);
}

