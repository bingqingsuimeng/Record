//删除IPC
void CPageIPCameraConfigFrameWork::OnClickSubPage()
{
	......
	switch(i)//找到的Button ID
	{
		case 15://删除通道
		{
			......
			BizGetPara(&bizTar, (void *)&ipcam);
					
			if(ipcam.enable)
			{
				ipcam.channel_no = chn;
				ipcam.enable = 0;
				
				BizSetPara(&bizTar, (void *)&ipcam);
			}
			......
		} break;
	}
	......
}

s32 ConfigSetIPCameraPara(SBizIPCameraPara *psPara, u8 nId)
{
	......
	int ret = ModConfigSetParam(EM_CONFIG_PARA_IPCAMERA, &sConfig, nId);//保存设置到文件
	
	ret |= tl_set_ipcamera(nId, &ipcam);//当前生效
	......
}

//设置指定通道对应的网络摄像机
//摄像机参数为空则清除该通道之前之前设置的网络摄像机
int tl_set_ipcamera(int channel, ipc_unit *ipcam)
{
	if(channel >= ARG_VI_NUM_MAX)
	{
		return -1;
	}
	
	if(ipcam == NULL)
	{
		return -1;
	}
	
	//return WriteMsgCmd(plib_gbl_info->sCmdHdr, ipcam);
	
	plib_gbl_info->ipcam[channel] = *ipcam;
	return IPC_Set(channel, ipcam);
}

int IPC_Set(int chn, ipc_unit *ipcam)
{
	......
	g_chn_info[chn].newcam = *ipcam;
	g_chn_info[chn].changed = 1;
	......
	if(ipcam->protocol_type == PRO_TYPE_KLW)
	{
		g_chn_info[chn].ops.Open = KLW_CMD_Open;
		g_chn_info[chn].ops.Close = KLW_CMD_Close;
		g_chn_info[chn].ops.SetImageParam = KLW_CMD_SetImageParam;
		g_chn_info[chn].ops.GetImageParam = KLW_CMD_GetImageParam;
		g_chn_info[chn].ops.PtzCtrl = KLW_CMD_PtzCtrl;
		g_chn_info[chn].ops.SetTime = KLW_CMD_SetTime;
		g_chn_info[chn].ops.SetMD = KLW_CMD_SetMD;//
		g_chn_info[chn].ops.SetOSD = KLW_CMD_SetOSD;//
		g_chn_info[chn].ops.SetVENC= KLW_CMD_SetVENC;//
		g_chn_info[chn].ops.GetVENC= KLW_CMD_GetVENC;//
		g_chn_info[chn].ops.Reboot = KLW_CMD_Reboot;
		g_chn_info[chn].ops.RequestIFrame = KLW_CMD_RequestIFrame;
		g_chn_info[chn].ops.GetAudioSwitchStatus = KLW_CMD_GetAudioSwitchStatus;
		g_chn_info[chn].ops.SetAudioSwitchStatus = KLW_CMD_SetAudioSwitchStatus;
	}
	......
	
}

void *videoConnFxn(void *arg)//处理线程
{
	......
		if(changed)
		{
			IPC_Stop(i);
			
			IPC_Stop(i+g_chn_count);
			
			reconn = 1;
		}
	......
}


//码流数据回调
tl_hslib_com.c
	IPC_RegisterCallback(DealRealStream, DealStreamState);
	int DealRealStream(real_stream_s *stream, unsigned int dwContext)
	int WriteFrameToVencMainQueue(real_stream_s *stream)
	{
		venc_stream_s out_stream;
		out_stream.chn = stream->chn;
		out_stream.data = stream->data;
		out_stream.len = stream->len;
		out_stream.pts = venc_get_sys_pts(stream->chn, stream->pts);
		out_stream.type = stream->frame_type;
		out_stream.rsv = 0;//stream->rsv;
		out_stream.width = stream->width;
		out_stream.height = stream->height;
		
		if(plib_gbl_info->pMainStreamCB != NULL)
		{
			plib_gbl_info->pMainStreamCB(&out_stream);//DealMainStream
		}
	}
	
	int DealMainStream(venc_stream_s *stream)
	{
		....
		PFNEncodeRequest pfnEncodeProc = psStreamChn->sChnInfo.pfnEncodeProc;
		pfnEncodeProc(&sEncodeHead, nContent);
		....
	}
	
	s32 ModEncodeRequestStart(u8 nChn, EMCHNTYPE emChnType, PFNEncodeRequest pfnEncodeCB, u32 nContent)
	{
		...
		psChnObj->sChnInfo.pfnEncodeProc = pfnEncodeCB;//EncodeDeal
		...
	}
	
	void EncodeDeal(SEncodeHead* psEncodeHead, u32 nContent)
	{
		SBizEncodeData sBizEncData;
		sBizEncData.psEncodeHead = psEncodeHead;
		if(0 == ExtractDwContent(nContent, &sBizEncData.nChn, &sBizEncData.emChnType))
		{
			//if(sBizEncData.nChn == 3 || sBizEncData.nChn == 19) printf("EncodeDeal:chn%d\n",sBizEncData.nChn);
			
			//SendBizInnerMsgCmd(EM_BIZMSG_ENCDATA, (void *)&sBizEncData);
			EncDataDispatch((SBizEncodeData*)&sBizEncData);
		}
	}
	
	s32 EncDataDispatch(SBizEncodeData* psBizEncData)
		RecordWriteOneFrame(nChn, &sRecHead);
			RecordWriteFrameToBuf(header)
			{
				sem_wait(&nSemForBuffer[header->nChn]);
				#endif
				
				ret = WriteDataToBuf(&g_RecBufInfo[header->nChn], (u8 *)header, sizeof(SModRecRecordHeader));
				if(EM_REC_SUCCESS != ret)
				{
					fprintf(stderr, "function: %s\n", __FUNCTION__);
					sem_post(&nSemForBuffer[header->nChn]);
					return ret;
				}
				ret = WriteDataToBuf(&g_RecBufInfo[header->nChn], header->nDate, header->nDataLength);
				if(EM_REC_SUCCESS != ret)
				{
					fprintf(stderr, "function: %s\n", __FUNCTION__);
					ResumeCircleBufToPast(&g_RecBufInfo[header->nChn], 1, 0);
					sem_post(&nSemForBuffer[header->nChn]);
					return ret;
				}
				
				sem_post(&nSemForBuffer[header->nChn]);
			}
	