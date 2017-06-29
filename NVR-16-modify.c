modify:
	diskmanage.h
typedef struct
{
	u8 is_disk_exist;
	u8 is_partition_exist[MAX_PARTITION_NUM];
	partition_index ptn_index[MAX_PARTITION_NUM];
	u32 total;	---- long modify to u32
	u32 free;	---- long modify to u32
	u8 storage_type;//'s'->sata, 'u'->'usb'
	u8 disk_physical_idx;//主板上硬盘的物理编号
	u8 disk_logic_idx;//主板上硬盘的逻辑编号
	u8 disk_system_idx;//系统检测到的硬盘编号sda->0, sdb->1...
	char disk_name[32];//硬盘设备名/dev/sda, /dev/sdb...
	char disk_sn[64];//硬盘序列号、唯一
}HddInfo;
	
BUG:
	CmdProc.c -- DealCommand() -- upload_alarm() type值
	metcomm.c -- Alarm_CheckDisk() -- net_write_upload_alarm() key
	
PageAlarmDeal.cpp
851: 触发报警 2out or 4out
	
	
extern int DoStreamStateCallBack(int chn, real_stream_state_e msg, u32 nvrIP, u32 alarm_key);

//yaogang modify 20160201
//nvr.cpp 中远程NVR 报警
	
#if 1
	struct in_addr in;
	in.s_addr = nvrIP;
	
	printf("%s nvr alarm, IP: %s, type: %u, id: %u, state: %u\n", 
		__func__, inet_ntoa(in), type, id, state);
#endif

GetParsedString	
	
xxx.xxx.xxx.xxx

//yaogang modify 20160201
		//nvr.cpp 中远程NVR 报警
		u8 NVR_vlostflag = 0;
		SAlarmListItem NVR_vlostitem;
		u8 NVR_diskerrflag = 0;
		SAlarmListItem NVR_diskerritem;
		struct in_addr in;
		char ipstr[32] = {0};		
		
		for (j=0; j<MAX_REMOTE_NVR; j++)
		{
			pnvr = &g_cAlarmListObj.m_byNVR[j];
			
			if (pnvr->nvrIP != 0)
			{
				in.s_addr = pnvr->nvrIP;
				sprintf(ipstr, "%s NVR", inet_ntoa(in));
				
				#if 1
				printf("%s ipstr: %s\n", __func__, ipstr);
				#endif

				//视频丢失
				NVR_vlostflag = 0;
				NVR_vlostitem.type = ipstr;
				NVR_vlostitem.type += GetParsedString("&CfgPtn.VideoLoss");
				NVR_vlostitem.detail = "";
				
				for (i=0; i<32; i++)//在此限定远程NVR最大支持32路IPC的
				{					
					if(pnvr->m_byVLoss[i].still_stamp)
					{
						char achStr[4] = {0};
						if(NVR_vlostflag)
						{
							sprintf(achStr, " %d", i+1);
						}
						else
						{
							sprintf(achStr, "%d", i+1);
						}
						NVR_vlostitem.detail += achStr;
						NVR_vlostflag = 1;
					}
				}
				if(NVR_vlostflag)
				{
					m_vCurrItems.push_back(NVR_vlostitem);
				}

				//硬盘错误
				NVR_diskerrflag = 0;
				NVR_diskerritem.type = ipstr;
				NVR_diskerritem.type += GetParsedString("&CfgPtn.DiskErr");
				NVR_diskerritem.detail = "";
				
				for (i=0; i<MAX_HDD_NUM; i++)//在此限定远程NVR最大支持32路IPC的
				{		
					if(pnvr->m_byDiskErr[i].still_stamp)
					{
						char achStr[4] = {0};
						if(NVR_diskerrflag)
						{
							sprintf(achStr, " %d", i+1);
						}
						else
						{
							sprintf(achStr, "%d", i+1);
						}
						NVR_diskerritem.detail += achStr;
						NVR_diskerrflag = 1;
					}
				}
				if(NVR_diskerrflag)
				{
					m_vCurrItems.push_back(NVR_diskerritem);
				}
			}
		}
		//
	
if(m_byVLoss[i].still_stamp)
		{
			if (m_byVLoss[i].current == 0)
			{
				m_bChanged = TRUE;
				m_byVLoss[i].still_stamp = 0;
			}
			else
			{
				bAlarmIconShow = TRUE;
			}
		}	
	
	CPageAlarmList* pAlarmList = (CPageAlarmList *)g_pPages[EM_PAGE_ALARMLIST];
	if(pAlarmList != NULL)
	{
		pAlarmList->Open();
	}
	

g_pBizPreviewData.emBizPreviewMode == EM_BIZPREVIEW_HideItem  EM_BIZPREVIEW_CLOSE
	
	
	
	
	
	
	
	
	
	
	