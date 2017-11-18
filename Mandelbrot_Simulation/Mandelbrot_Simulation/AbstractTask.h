#pragma once
#include "stdafx.h" 

class AbstractTask
{
public:
	virtual ~AbstractTask() {}

	virtual void run() = 0;
private:
};