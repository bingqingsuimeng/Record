���߳���Ѳ������Դ��״̬
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
	//IPC �������������
	psAlarmEvent = &psAlarmManager->sIPCExtSensors;
	CheckAlarmIPCExtSensors(psAlarmEvent, psAlarmManager->pfnAlarmCb);//pfnAlarmCb = AlarmDeal
	......
}

//IPC�ⲿ�������
void CheckAlarmIPCExtSensors(SAlarmEvent *psAlarmEvent, FNALARMCB pfnAlarmCb)
{
    int i;
    u32 nEventSatus = 0;
    u8 nEnable, nDelay;
	
	//ÿ��ͨ��ռһ��������λ
    nEventSatus = tl_get_alarm_IPCExt();
    
	if (nEventSatus)
		printf("IPCExt alarmin = 0x%04x\n", nEventSatus);
    //printf("%s:%d nChannels:%d\n", __FUNCTION__, __LINE__, psAlarmEvent->nChannels);
    for (i = 0;i < psAlarmEvent->nChannels; i++)
    {
		SAlarmChn *psAlarmChn = &psAlarmEvent->psAlarmChn[i];
		nEnable = psAlarmChn->sAlarmPara.sAlaIPCExtSensorPara.nEnable;//��AlarmParaInit()�г�ʼ��AlarmSetPara()
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
		&& psAlarmChn->sEvent.nStatus)//ֻ�ڱ�������ʱ����
	{
		sendto_485ext_board(emAlarmEvent, chn, fd485);
	}
	
}
//pfnAlarmCb == AlarmDeal
//biz_alarm.c
void AlarmDeal(SAlarmCbData* psAlarmCbData)//�ص�����  ���������ϱ�
{
	......
		case EM_ALARM_EVENT_SENSOR:  //�����������¼�
		{
			sBizEventPara.emType = EM_BIZ_EVENT_ALARM_SENSOR;
			BizSetUploadAlarmPara(0, sBizEventPara.sBizAlaStatus.nChn, GetAlarmCheckStaue());
		}
	......
	psBizManager->sBizPara.pfnBizEventCb(&sBizEventPara);//BizEventCB ���Ǳ��б����/ɾ����Ŀ���ʼ�����
}

void BizSetUploadAlarmPara(u8 type, u8 id, u8 state)
netcomm.c �� ����Ӧ��typeֵ
//u32 alarmupload[AUTYPENUM];
/*	old
	0		//�ź�������
	1		//Ӳ��������
	2		//��Ƶ��ʧ����
	3		//�ƶ���ⱨ��
	4		//Ӳ��δ��ʽ������
	5		//Ӳ�̶�д������
	6		//IPC�ڸǱ���
	7		//��ʽ��ƥ�䱨��
	8		//�Ƿ����ʱ���
*/
/* new
	0		//Ӳ��δ��ʽ������
	1		//Ӳ�̶�ʧ����
	2		//Ӳ�̶�д������
	3		//Ӳ��������
	4		//���������Ӳ��
	5		//�ź�������
	6		//��Ƶ��ʧ����
	7		//�ƶ���ⱨ��
	8		//IPC�ڸǱ���
	9		//��ʽ��ƥ�䱨��
	10		//�Ƿ����ʱ���
	11		//IPC�ⲿ����
	12		//485��չ����
*/
int BizEventCB(SBizEventPara* pSBizEventPara)
{
	......
	case EM_BIZ_EVENT_ALARM_VMOTION:
			//printf("VMOTION\n");
			//yaogang modify 20141020
			if(pSBizEventPara->sBizAlaStatus.nCurStatus)//�ƶ���������Ϣ��ʾ
			{
				AlarmListAdd(pSBizEventPara->sBizAlaStatus.nChn, EM_ALRM_MOTION_DETECTION, 1);
			}
			else
			{
				AlarmListDelete(pSBizEventPara->sBizAlaStatus.nChn, EM_ALRM_MOTION_DETECTION, 0);
			}
			
			bizData_SendMail(pSBizEventPara);
			EventMDDeal(&pSBizEventPara->sBizAlaStatus);//����Ӧ��Ԥ��ͨ������ʾ����ͼ�꣬Ȼ��д��־
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
			BizGUiWriteLog(BIZ_LOG_MASTER_SYSCONTROL, BIZ_LOG_SLAVE_START_MD);//д��־
		}
		else
		{
			pDeskTop->ShowChnState(i, EM_STATE_MD , x2, y2, EM_CHNSTATE_HIDE);
			BizGUiWriteLog(BIZ_LOG_MASTER_SYSCONTROL, BIZ_LOG_SLAVE_STOP_MD);
		}
	}
	......
}

//�����ַ��߳�
void* AlarmCmdDealFxn(void *arg)
{
	......
	//������������
	AlarmDispatch(psAlarmManager);
	......
}

void AlarmDispatch(SAlarmManager *psAlarmManager)
{
	//����������
	BuzzDispatch(psAlarmManager);
	
	//�����������
	AlarmOutDispatch(psAlarmManager);
	
	//����¼��
	RecordDispatch(psAlarmManager);
	
	//������̨����
	PtzDispatch(psAlarmManager);
	
	//������ͨ���Ŵ�
	ZoomDispatch(psAlarmManager);
}


//�����ϱ�
BizNetUploadAlarm()
upload_alarm()
net_write_upload_alarm()
