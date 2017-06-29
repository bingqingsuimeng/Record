流程：
Frontboard.c--ReadBoardDeviceFxn 线程读按键板设备文件
	DevFrontboard.cpp
		GUI.cpp
			Page.cpp--MsgProc()	
				BizData.cpp--FxnKeycodeShut()



m_pDevFrontboard->AttachInput(this, (SIG_DEV_FB_INPUT)&CGUI::onFrontboardIntput);
	onFrontboardIntput()
		OnHumanInput()
			
			BizData.cpp: s32 FxnKeycodeShut()
				
				
void CGUI::onFrontboardIntput(uint message, uint param0, uint param1)
{
	OnHumanInput(message, param0, param1, 0);
}

m_sigInput(XM_KEYDOWN, keys[0], FB_FLAG_NONE);
