#pragma once
#include "Singleton.h"

class ProjectGlobals : public Singleton<ProjectGlobals> {
public:
	std::wstring loadingBar = L"[                   ]";
};