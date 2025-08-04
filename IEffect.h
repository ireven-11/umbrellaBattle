#pragma once
#include<memory>

template <typename T>
class IEffect
{
public:
	virtual ~IEffect() = default;

	virtual void update(std::shared_ptr<T> data) = 0;
	virtual void draw()	= 0;
};