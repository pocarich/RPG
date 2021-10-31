#pragma once

#include"SynthesisInfo.h"

class SynthesisInfoList 
{
	static vector<SynthesisInfo> synthesisInfoList;
public:
	static void Load();
	static const vector<SynthesisInfo>& GetSynthesisInfoList() { return synthesisInfoList; }
};