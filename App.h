#pragma once
#include "Window.h"
#include <vector>
#include "Vertex.h"
#include "MandelbrotSet.h"
#include "KochSnowflake.h"
#include "TriangleFractal.h"
class App
{
public:
	App(int width, int height);
	~App();
	int DoFrame();
private:
	void Logic();
	void Draw();
private:
	Window* wnd=nullptr;
	float scale;
	int iterationLimit = 16;
	Vertex Translation = { 0,0 };
	bool pause = false;
	MandelbrotSet* MS = nullptr;
	KochSnowflake* KS = nullptr;
	TriangleFractal* KF = nullptr;
};

