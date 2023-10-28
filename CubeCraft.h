#pragma once
#include "Renderer/Renderer.h"

namespace cubecraft {
	static void Init() {
		Renderer::Instance()->Init();
	}
	static void Loop() {
		Renderer::Instance()->Loop();
	}
	static void Quit() {
		Renderer::Instance()->Quit();
	}
}
