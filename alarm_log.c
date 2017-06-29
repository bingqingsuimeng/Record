该线程轮巡各报警源的状态
void* AlarmCheckEventFxn(void *arg)
{
	......
	while (1)
	{
		CheckAlarmEvent(psAlarmManager);
	}
	......
}

void CheckAlarmEvent(SAlarmManager *psAlarmManager)
{
	......
	//IPC 传感器报警检测
	psAlarmEvent = &psAlarmManager->sIPCExtSensors;
	CheckAlarmIPCExtSensors(psAlarmEvent, psAlarmManager->pfnAlarmCb);//pfnAlarmCb = AlarmDeal
	......
}

//IPC外部报警检测
void CheckAlarmIPCExtSensors(SAlarmEvent *psAlarmEvent, FNALARMCB pfnAlarmCb)
{
    int i;
    u32 nEventSatus = 0;
    u8 nEnable, nDelay;
	
	//每个通道占一个二进制位
    nEventSatus = tl_get_alarm_IPCExt();
    
	if (nEventSatus)
		printf("IPCExt alarmin = 0x%04x\n", nEventSatus);
    //printf("%s:%d nChannels:%d\n", __FUNCTION__, __LINE__, psAlarmEvent->nChannels);
    for (i = 0;i < psAlarmEvent->nChannels; i++)
    {
		SAlarmChn *psAlarmChn = &psAlarmEvent->psAlarmChn[i];
		nEnable = psAlarmChn->sAlarmPara.sAlaIPCExtSensorPara.nEnable;//在AlarmParaInit()中初始化AlarmSetPara()
		//EMALARMSENSORTYPE emType = psAlarmChn->sAlarmPara.sAlaSensorPara.emType;
		nDelay = psAlarmChn->sAlarmPara.sAlaIPCExtSensorPara.nDelay;
		psAlarmChn->nSetChangeTimesLast = psAlarmChn->nSetChangeTimes;
		//printf("chn[%d], emType = %d\n", i, emType);
		if ((nEventSatus >> i) & 1)
		{
			printf("yg IPCExt alarmin chn%d nEnable: %d, nDelay: %d\n", i, nEnable, nDelay);
		}
		RefreshStatus(nEnable, 1, nDelay, (nEventSatus >> i) & 1, psAlarmChn);
        
        AlarmEventCallback(psAlarmChn, pfnAlarmCb, EM_ALARM_EVENT_485EXT, i, fd485);
    }
    //printf("%s:%d\n", __FUNCTION__, __LINE__);
}

void AlarmEventCallback(SAlarmChn *psAlarmChn, FNALARMCB pfnAlarmCb, EMALARMEVENT emAlarmEvent, u8 chn, int fd485)
{
	//printf("%s:%d nStatusLast:%d nStatus:%d\n", __FUNCTION__, __LINE__, psAlarmChn->sEvent.nStatusLast, psAlarmChn->sEvent.nStatus);
	if(pfnAlarmCb && psAlarmChn->sEvent.nStatusLast != psAlarmChn->sEvent.nStatus)
	{
		SAlarmCbData sAlarmCbData;
		sAlarmCbData.emAlarmEvent = emAlarmEvent;
		sAlarmCbData.nChn = chn;
		sAlarmCbData.nData = psAlarmChn->sEvent.nStatus;
		sAlarmCbData.nTime = psAlarmChn->sEvent.nTime;
		pfnAlarmCb(&sAlarmCbData);
		
		//if(emAlarmEvent == EM_ALARM_EVENT_VMOTION && chn == 0)
		//{
			//printf("######chn%d motion notify status[%d]######\n",chn,psAlarmChn->sEvent.nStatus);
		//}
	}
	//yaogang modify 20141203 to YueTian 485Ext Board
	if ( (psAlarmChn->sEvent.nStatusLast != psAlarmChn->sEvent.nStatus) 
		&& psAlarmChn->sEvent.nStatus)//只在报警触发时发送
	{
		sendto_485ext_board(emAlarmEvent, chn, fd485);
	}
	
}
//pfnAlarmCb == AlarmDeal
//biz_alarm.c
void AlarmDeal(SAlarmCbData* psAlarmCbData)//回调处理  就是网络上报
{
	......
		case EM_ALARM_EVENT_SENSOR:  //传感器报警事件
		{
			sBizEventPara.emType = EM_BIZ_EVENT_ALARM_SENSOR;
			BizSetUploadAlarmPara(0, sBizEventPara.sBizAlaStatus.nChn, GetAlarmCheckStaue());
		}
	......
	psBizManager->sBizPara.pfnBizEventCb(&sBizEventPara);//BizEventCB 三角标列表添加/删除条目；邮件报警
}

void BizSetUploadAlarmPara(u8 type, u8 id, u8 state)
netcomm.c 中 有响应的type值
//u32 alarmupload[AUTYPENUM];
/*	old
	0		//信号量报警
	1		//硬盘满报警
	2		//视频丢失报警
	3		//移动侦测报警
	4		//硬盘未格式化报警
	5		//硬盘读写出错报警
	6		//IPC遮盖报警
	7		//制式不匹配报警
	8		//非法访问报警
*/
/* new
	0		//硬盘未格式化报警
	1		//硬盘丢失报警
	2		//硬盘读写出错报警
	3		//硬盘满报警
	4		//开机检测无硬盘
	5		//信号量报警
	6		//视频丢失报警
	7		//移动侦测报警
	8		//IPC遮盖报警
	9		//制式不匹配报警
	10		//非法访问报警
	11		//IPC外部报警
	12		//485扩展报警
*/
int BizEventCB(SBizEventPara* pSBizEventPara)
{
	......
	case EM_BIZ_EVENT_ALARM_VMOTION:
			//printf("VMOTION\n");
			//yaogang modify 20141020
			if(pSBizEventPara->sBizAlaStatus.nCurStatus)//移动侦测添加信息显示
			{
				AlarmListAdd(pSBizEventPara->sBizAlaStatus.nChn, EM_ALRM_MOTION_DETECTION, 1);
			}
			else
			{
				AlarmListDelete(pSBizEventPara->sBizAlaStatus.nChn, EM_ALRM_MOTION_DETECTION, 0);
			}
			
			bizData_SendMail(pSBizEventPara);
			EventMDDeal(&pSBizEventPara->sBizAlaStatus);//在相应的预览通道中显示报警图标，然后写日志
		break;
	......
}
int EventMDDeal(SBizAlarmStatus* mdStatus)
{
	......
	if(i == mdStatus->nChn)
	{
		if(mdStatus->nCurStatus != 0)
		{
			pDeskTop->ShowChnState(i, EM_STATE_MD, x2, y2, EM_CHNSTATE_1);
			BizGUiWriteLog(BIZ_LOG_MASTER_SYSCONTROL, BIZ_LOG_SLAVE_START_MD);//写日志
		}
		else
		{
			pDeskTop->ShowChnState(i, EM_STATE_MD , x2, y2, EM_CHNSTATE_HIDE);
			BizGUiWriteLog(BIZ_LOG_MASTER_SYSCONTROL, BIZ_LOG_SLAVE_STOP_MD);
		}
	}
	......
}

//报警分发线程
void* AlarmCmdDealFxn(void *arg)
{
	......
	//报警触发处理
	AlarmDispatch(psAlarmManager);
	......
}

void AlarmDispatch(SAlarmManager *psAlarmManager)
{
	//触发蜂鸣器
	BuzzDispatch(psAlarmManager);
	
	//触发报警输出
	AlarmOutDispatch(psAlarmManager);
	
	//触发录像
	RecordDispatch(psAlarmManager);
	
	//触发云台联动
	PtzDispatch(psAlarmManager);
	
	//触发单通道放大
	ZoomDispatch(psAlarmManager);
}


//网络上报
BizNetUploadAlarm()
upload_alarm()
net_write_upload_alarm()
