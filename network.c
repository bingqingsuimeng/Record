//��ʼ��
DoBizInit()//�ڶ��γ�ʼ��
	NetInit(hddHdr, &sPara);
		NetCommInit(&sNCCfg)
			pthread_create(&netThread, NULL, NetCommInitThxd, (void*)pCfg);
				netcomm_ConfigNetwork(&pCfg->sParaIns);

//����ı����
PageNetworkConfig.cpp
	BizNetWriteCfg((SBizNetPara*)&sPIns);
		//����webs ����
		NetComm_WebRestart(pCfg->HttpPort)
		NetComm_WritePara((SNetPara*)&sPIns)
	bizData_SaveNetPara(&sPIns);
	
	