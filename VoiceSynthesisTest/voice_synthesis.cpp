/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "StdAfx.h"

int _tmain(int argc, _TCHAR* argv[]){
	MyVoiceSynthesis speaker;
	speaker.speak(L"Voice synthesis system start...");
	speaker.speak("Hello Brad");

//	speaker.g_session->Release();
    return 0;
}
