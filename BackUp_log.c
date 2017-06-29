PageSnapPlayBack.cpp
	EMBIZFILETYPE emFileType = EM_BIZFILE_SNAP;

	sBackTgtAtt.fmt = EM_BIZFORMAT_JPEG;
	sBackTgtAtt.devt = EM_BIZBACKUP_USB;
	
	sSearchCondition.emSearchWay = EM_BIZSEARCH_BY_FILE;
	sSearchCondition.sSearchResult.nFileNum = nCount;
	sSearchCondition.sSearchResult.psRecSnapInfo = sFileList;
	
	m_pPageBackupInfo->SetBackupInfo(emFileType, &sBackTgtAtt, &sSearchCondition);
	
PageBackupInfo.cpp
	void CPageBackupInfo::SetBackupInfo(EMBIZFILETYPE fileType, SBizBackTgtAtt* attribute, SBizSearchCondition* condition)
	{
		m_fileType = fileType;
		m_backupAttr = attribute;
		m_backupCondition = condition;
	}

	BizSysComplexBackup(m_fileType, m_backupAttr, m_backupCondition);
		SysComplexBackup(&sPara);
			ModSysComplexBackup(emFileType, psBackTgtAtt, psSearchCondition);
				sCmdDataIns.cmd = EM_MODSYS_CMD_BACKUP;
				rtn = WriteMsgCmd( pCmd, (void*)&sCmdDataIns );
