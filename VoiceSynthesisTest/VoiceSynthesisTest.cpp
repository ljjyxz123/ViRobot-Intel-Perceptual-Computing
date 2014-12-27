/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "StdAfx.h"

MyVoiceSynthesis::MyVoiceSynthesis(void)
{
	g_session = 0;
	synth = 0;

	g_session = PXCSession::CreateInstance();
	if (!g_session) {
        throw "Failed to create an SDK session";
    }
}

MyVoiceSynthesis::~MyVoiceSynthesis(void)
{
	g_session->Release();
}

std::wstring MyVoiceSynthesis::speak(wchar_t* sentence)
{
	//Fill the descriptor
	PXCSession::ImplDesc desc = {};

	/*int sIdx = 0;
	char tmpStr[100] = "Voice Synthesis (Nuance* Vocalizer Expressive*)\0";
	for(sIdx = 0; sIdx < 47; sIdx++)
	{
		desc.friendlyName[sIdx] = tmpStr[sIdx];
	}desc.friendlyName[sIdx] = '\0';*/

	// Create a PXCSpeechSynthesis instance
	sts = g_session->CreateImpl<PXCSpeechSynthesis>(&desc,&synth);
	if (sts < PXC_STATUS_NO_ERROR) throw "Failed to create the synthesis module";

	// Configure the module
	sts=synth->QueryProfile(&pinfo);

	//Set options
	pinfo.volume = 80;
	pinfo.pitch = 100;
	pinfo.rate = 100;

	sts=synth->SetProfile(&pinfo);
	if (sts<PXC_STATUS_NO_ERROR) {
		synth->Release();
		return L"Failed to set configuration";
	}

	// Synthesize the speech
	synth->BuildSentence(1, sentence);

    // Render the sentence or write it to vo's internal memory buffer
	VoiceOut vo(&pinfo);
	int nbuffers=synth->QueryBufferNum(1);
	for (int i=0;i<nbuffers;i++) {
		PXCAudio *sample=synth->QueryBuffer(1, i);
        vo.RenderAudio(sample);
	}
	synth->Release();
	return std::wstring(L"");
}

void MyVoiceSynthesis::speak(char* sentence)
{
	speak(ATL::CA2W(sentence));
}


void MyVoiceSynthesis::speak(std::string sentence)
{
	speak(ATL::CA2W(sentence.c_str()));
}
