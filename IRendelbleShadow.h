#pragma once

class IRendelbleShadow
{
public:
	virtual ~IRendelbleShadow() = default;
	virtual void draw()const	= 0;
};