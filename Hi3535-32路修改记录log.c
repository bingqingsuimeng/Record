
解码帧模式需要改动的地方
lib_vdec.h
	#define DDR4G
	
lib_vdec.c
	SAMPLE_VDEC_CreateVdecChn() -- stAttr.stVdecVideoAttr.enMode
	#define VDEC_FRAME_MODE

tl_hslib_com.c
	#ifdef	UsePreviewQueue
	
文件系统
rootfs_uclibc/home/root/all/ko/load3535
	insmod mmz.ko mmz=anonymous,0,0x94000000,702M:jpeg,0,0xbfe00000,2M anony=1 || report_error
		
		
TL_BOARD_TYPE_NR3532
if(ARG_VO_NUM_MAX > 16)
EM_BIZPREVIEW_36SPLITS

Hi3535 -- 32路修改记录
tl_hslib_init()
	vio_enable_vo_all(VO_MODE_36MUX);
		SAMPLE_COMM_VO_StartDevLayer()
			#ifdef HI3535
			if(VoDev == VO_DEVICE_HD)
			{
				if(ARG_VO_NUM_MAX > 16)
				{
					HI_MPI_VO_SetVideoLayerPartitionMode(SAMPLE_VO_LAYER_VPIP, VO_PART_MODE_SINGLE);
					
					s32Ret = HI_MPI_VO_BindVideoLayer(SAMPLE_VO_LAYER_VPIP, VO_DEVICE_HD);
					if(HI_SUCCESS != s32Ret)
					{
						LIB_PRT("HI_MPI_VO_PipLayerBindDev failed with %#x!\n", s32Ret);
						return HI_FAILURE;
					}
					
					s32Ret = HI_MPI_VO_SetVideoLayerAttr(SAMPLE_VO_LAYER_VPIP, &stLayerAttr);
					if (s32Ret != HI_SUCCESS)
					{
					   LIB_PRT("failed with %#x!\n", s32Ret);
					   return HI_FAILURE;
					}
					
					s32Ret = HI_MPI_VO_EnableVideoLayer(SAMPLE_VO_LAYER_VPIP);
					if (s32Ret != HI_SUCCESS)
					{
					   LIB_PRT("failed with %#x!\n", s32Ret);
					   return HI_FAILURE;
					}
					
					HI_MPI_VO_SetVideoLayerPriority(SAMPLE_VO_LAYER_VPIP, 0);
					
					//yaogang modify 20150922
					s32Ret = HI_MPI_VO_SetPlayToleration(SAMPLE_VO_LAYER_VPIP, 300);//300ms
					if(HI_SUCCESS != s32Ret)
					{
						LIB_PRT("%s HI_MPI_VO_SetPlayToleration() failed!\n", __func__);
						return HI_FAILURE;
					}
					
				}
			}
			#endif

		SAMPLE_COMM_VO_StartChn()
			for (i=0; i<u32WndNum; i++)
			{
				HI_S32 VoLayer = VoDev;
				HI_S32 u32Priority = 0;
				
				#ifdef HI3535
				if(VoDev == VO_DEVICE_HD)
				{
					if(i >= 16)
					{
						VoLayer = SAMPLE_VO_LAYER_VPIP;
						u32Priority = 0;
					}
					else
					{
						VoLayer = SAMPLE_VO_LAYER_VHD0;
						u32Priority = 0;
					}
				}
				#endif
				
				stChnAttr.stRect.s32X       = ALIGN_BACK(u32Width/u32Square, 2) * (i%u32Square);//ALIGN_BACK((u32Width/u32Square) * (i%u32Square), 2);
				stChnAttr.stRect.s32Y       = ALIGN_BACK(u32Height/u32Square, 2) * (i/u32Square);//ALIGN_BACK((u32Height/u32Square) * (i/u32Square), 2);
				stChnAttr.stRect.u32Width   = ALIGN_BACK(u32Width/u32Square, 2);
				stChnAttr.stRect.u32Height  = ALIGN_BACK(u32Height/u32Square, 2);
				stChnAttr.u32Priority       = u32Priority;
				stChnAttr.bDeflicker        = HI_TRUE;
				
				s32Ret = HI_MPI_VO_SetChnAttr(VoLayer, i, &stChnAttr);
				if (s32Ret != HI_SUCCESS)
				{
					printf("%s(%d):failed with %#x!\n", __FUNCTION__, __LINE__,  s32Ret);
					return HI_FAILURE;
				}
				
				s32Ret = HI_MPI_VO_EnableChn(VoLayer, i);
				if (s32Ret != HI_SUCCESS)
				{
					LIB_PRT("failed with %#x!\n", s32Ret);
					return HI_FAILURE;
				}
				
				printf("######HI_MPI_VO_EnableChn%d success######!!!\n",i);
			}
			
	vio_bind_vi2vo_all(0, ARG_VI_NUM_MAX, 0, 0, 0);
		SAMPLE_COMM_VO_BindVpss(VO_DEV VoDev,VO_CHN VoChn,VPSS_GRP VpssGrp,VPSS_CHN VpssChn)
		{
			HI_S32 s32Ret = HI_SUCCESS;
			MPP_CHN_S stSrcChn;
			MPP_CHN_S stDestChn;
			
			stSrcChn.enModId = HI_ID_VPSS;
			stSrcChn.s32DevId = VpssGrp;
			stSrcChn.s32ChnId = VpssChn;
			
			stDestChn.enModId = HI_ID_VOU;
			stDestChn.s32DevId = VoDev;
			stDestChn.s32ChnId = VoChn;
			
		#ifdef HI3535
			if(VoDev == VO_DEVICE_HD)
			{
				if(VoChn >= 16 && VoChn < ARG_VO_NUM_MAX)
				{
					stSrcChn.enModId = HI_ID_VDEC;
					stSrcChn.s32DevId = 0;
					stSrcChn.s32ChnId = VpssGrp;
					
					stDestChn.enModId = HI_ID_VOU;
					stDestChn.s32DevId = SAMPLE_VO_LAYER_VPIP;
					stDestChn.s32ChnId = VoChn;
				}
			}
		#endif
		
			s32Ret = HI_MPI_SYS_Bind(&stSrcChn, &stDestChn);
			if (s32Ret != HI_SUCCESS)
			{
				LIB_PRT("HI_MPI_SYS_Bind failed with %#x!\n", s32Ret);
				return HI_FAILURE;
			}
		
			return s32Ret;
		}
	
	nvr_preview_vdec_open(0, ARG_VI_NUM_MAX);//32
		SAMPLE_COMM_VPSS_Start()	// 16 chn0~15
		for(i = nvr_first_chn; i < (nvr_first_chn + open_chn_num); i++)
			SAMPLE_VDEC_CreateVdecChn(VdChn, &stSize, PT_H264);	 // 32 chn0~31
			
			SAMLE_COMM_VDEC_BindVpss(VdChn, VpssGrp);	// 16 chn0~15

32路修改记录
1、通道增加了，解码暂时不做缓冲
2、界面要对解码板做精简，先不动文件系统，改程序界面部分
//yaogang modify 20150324
	SBizDvrInfo DvrInfo;
	u8 nNVROrDecoder = 1; //跃天: 1 nvr, 2 解码器
	if (BizGetDvrInfo(&DvrInfo) == 0)
	{
		nNVROrDecoder = DvrInfo.nNVROrDecoder;
	}
3、先做32路
mod_config.c 后期要精简对解码板的内存开销，配置参数精简

biz_manager.c
	DoBizInit
		tl_hslib_init_c() -- tl_hslib_com.c
		......
		tl_vga_resolution() -- lib_misc.c


HI_MPI_VO_SetDevFrameRate：设置设备用户时序下设备帧率。

HI_MPI_VO_SetVideoLayerAttr：设置视频层属性。
	HI_U32 u32DispFrmRt;                /* 显示帧率 */ 60 30

HI_MPI_VO_SetChnFrameRate：设置指定视频输出通道的显示帧率。

4、BUG:
添加22路IPC时 程序段错误退出
已作的措施
	1、mod_config.c : 	WriteFileToFlash() line:873
	2、mod_alarm.c : 	AlarmCheckEventFxn() line:970
	3、ipcamera.cpp : 	videoConnFxn() line: 482 498
						IPC_Init() line:638  KLW_Init(g_chn_count*2);
							
							New LWP


DEC-test
common.h
	#define ARG_CHN_MAX					32	//support max channel number

tl_hslib_com.c
	int DealRealStream(real_stream_s *stream, unsigned int dwContext)
	if (stream->chn >= 16)
		{
			return 0;
		}
		
	int tl_set_ipcamera(int channel, ipc_unit *ipcam)
		if(channel >= 32)//ARG_VI_NUM_MAX)
	
	IPC_Init(ARG_VI_NUM_MAX * 2);
	
	
mod_alram.c
//CheckAlarmEvent(psAlarmManager);

testUI.cpp
	void CChallenger::Initialize(int argc, char * argv[])
		case 32:
	            //sBPP.emBizPreviewMode = EM_BIZPREVIEW_36SPLITS;
				sBPP.emBizPreviewMode = EM_BIZPREVIEW_16SPLITS;
				
bizdata.cpp
	int StreamKbps = Get_StreamKbps(i)+Get_StreamKbps(i+16);

未做修改的地方：
tl_hslib_com.c
	SAMPLE_COMM_VPSS_Start()
	
#ifdef HI3535	
if (stStat_vdec.bStartRecvStream)
{
	s32Ret = HI_MPI_VO_ShowChn(VoDev, i);
}
//yaogang modify 20150609 end
#else
s32Ret = HI_MPI_VO_ChnShow(VoDev, i);
#endif
if (s32Ret != HI_SUCCESS)
{
	//pthread_mutex_unlock(&plib_gbl_info->preview_chn_lock[i]);
	LIB_PRT("failed with %#x!\n", s32Ret);
	return HI_FAILURE;
}
