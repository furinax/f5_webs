#include "Particle.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

Perlin Particle::mPerlin;
Listener& Particle::mListener = Listener::getInstance();

void Particle::addPosition(const Vec3f& pos)
{
	mPositions.push_front(pos);
}

float Particle::angle(const Vec2f &lhs)
{
	return math<float>::atan2(lhs.y, lhs.x) * 57.295779513082321f;
}

void Particle::drawPositions()
{
	gl::color(ci::Color::white());
	glBegin(GL_POINTS);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		gl::vertex(*iter);
	}
	glEnd();
}

void Particle::draw(const bool overlay, const ci::Vec2f pos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}
	
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		float distance = pos.distance(Vec2f(loc.x, loc.y));
		if (distance < mRadius)
		{
			adjustedColor.a = ci::lmap(distance, 0.f, mRadius, 1.f, 0.f);
			gl::color(adjustedColor);
			gl::lineWidth(ci::math<float>::clamp(ci::lmap(loc.z, -500.f, 500.f, 0.f, 3.f),0.f,3.f));
			glBegin(GL_LINES);
			gl::vertex(pos);
			gl::vertex(loc);
			glEnd();
		}
	}
	
	drawPositions();
}