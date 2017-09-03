#pragma once
#include <WS2tcpip.h>

#include "defines.h"
#include "IUpdateDraw.h"




class TestNetwork :public IUpdateDraw
{
public:
	TestNetwork();
	~TestNetwork();

	
	void TestServer();
	
	

	virtual void Update() override;


	virtual void Draw() override;

};