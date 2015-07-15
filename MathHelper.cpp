#include "MathHelper.h"

MathHelper::MathHelper()
{

}

MathHelper::~MathHelper()
{

}

float MathHelper::normalize(float value, float min, float max)
{
	return (value - min) / (max - min);
}
