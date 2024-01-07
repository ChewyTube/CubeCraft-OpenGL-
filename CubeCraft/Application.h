#pragma once

#include "CubeCraft.h"

CubeCraft* CubeCraft::instance = nullptr;

class Application {
public:
	void Run() {
		instance->Init();
		instance->RenderLoop();
		instance->Quit();
	}
private:
	int success = 0;
	CubeCraft* instance = CubeCraft::Instance();
};