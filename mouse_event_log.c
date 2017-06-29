底层：
mouse.c:
	int MouseGetData(MOUSE_DATA *pData)
DevMouse.cpp:
	void CDevMouse::ThreadProc()
		OnMouseData(&data, sizeof(MOUSE_DATA));
			m_sigData(XM_LBUTTONDOWN, mousedata->key, postion);	
	
VD_BOOL CDevMouse::AttachInput(CObject * pObj, SIG_DEV_MOUSE_INPUT pProc)
{
	if(m_sigData.Attach(pObj, pProc) < 0)
	{
		return FALSE;
	}
	return TRUE;
}


//上层

VD_BOOL CGUI::Start()
{
	......
	m_pDevMouse->AttachInput(this, (SIG_DEV_MOUSE_INPUT)&CGUI::OnMouseInput);
	......
}

void CGUI::OnMouseInput(uint message, uint param0, uint param1)
{
	OnHumanInput(message, param0, param1, 0);
}

void CGUI::OnHumanInput(uint msg, uint wpa, uint lpa, int screen)
{
	......
	CItem::VD_DispatchMessage(screen, msg, wpa, lpa);
	......
}
//发送消息
VD_BOOL CItem::VD_DispatchMessage(int screen, uint msg, uint wpa, uint lpa)
{
	......
	pItem->VD_SendMessage(msg, wpa, lpa);
	......
}
//接收消息
void CItemThread::ThreadProc()
{
	......
	m_pItem->MsgProc(msg.msg, msg.wpa, msg.lpa);
	......
}