#pragma once

template<typename T>
T CalculateDistance(VECTOR position1, VECTOR position2)
{
	VECTOR tempVector = VGet(position1.x, position1.y, position1.z);
	tempVector = VSub(tempVector, position2);
	tempVector = VGet(tempVector.x * tempVector.x, tempVector.y * tempVector.y, tempVector.z * tempVector.z);
	T value = tempVector.x + tempVector.y + tempVector.z;
	return sqrt(value);
}