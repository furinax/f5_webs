#include "Particle.h"

using namespace ci;
using namespace ci::app;

Perlin Particle::mPerlin;

void Particle::addPosition(const Vec3f& pos)
{
	if (mPositions.size() > mMaxPositions)
	{
		mPositions.pop_back();
	}
	mPositions.push_front(pos);
}

float Particle::angle(const Vec2f &lhs)
{
	return math<float>::atan2(lhs.y, lhs.x) * 57.295779513082321f;
}