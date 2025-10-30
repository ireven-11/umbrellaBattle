#pragma once

class IRendelbleShadow
{
public:
	virtual ~IRendelbleShadow() = default;
	virtual void draw()			= 0;
	virtual bool isDrawing()	= 0;
};