/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "stdafx.h"

class MyVoiceSynthesis
{
public:
	MyVoiceSynthesis(void);
	~MyVoiceSynthesis(void);

	std::wstring speak(wchar_t* sentence);
	void speak(char* sentence);
	void speak(std::string sentence);

public:
	PXCSession  *g_session;
	PXCSpeechSynthesis *synth;
	pxcStatus sts;
	PXCSpeechSynthesis::ProfileInfo pinfo;
	PXCSession *session;
	VoiceOut *vo;
};
