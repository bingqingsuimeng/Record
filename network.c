//初始化
DoBizInit()//第二次初始化
	NetInit(hddHdr, &sPara);
		NetCommInit(&sNCCfg)
			pthread_create(&netThread, NULL, NetCommInitThxd, (void*)pCfg);
				netcomm_ConfigNetwork(&pCfg->sParaIns);

//界面改变参数
PageNetworkConfig.cpp
	BizNetWriteCfg((SBizNetPara*)&sPIns);
		//重启webs 服务
		NetComm_WebRestart(pCfg->HttpPort)
		NetComm_WritePara((SNetPara*)&sPIns)
	bizData_SaveNetPara(&sPIns);
	
	