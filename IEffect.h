#pragma once

template <typename T>
class IEffect
{
public:
	virtual ~IEffect() = default;

	void update(T data) = 0;
	void draw(T data)	= 0;
};