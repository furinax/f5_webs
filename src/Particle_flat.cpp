#include "Particle_flat.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "cinder/CinderMath.h"

Particle_flat::Particle_flat(const std::list< ci::Vec2f > &vpos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);
	for (auto pos: vpos)
		addPosition(Vec3f(floor(pos.x / 30) * 30, floor(pos.y / 30) * 30, 0));
	mRadius = 700.f;
	Listener &listener = Listener::getInstance();
//	mVel = Vec3f(-10.f, 0, 0);
	mColor = ci::Color(listener.getVolume(), randFloat(.5f), randFloat());
	mOverlayColor = Color::white();

	mLifespan = 15;

}

void Particle_flat::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
//		mVel = Vec3f(currentPos.x < getWindowCenter().x ? 3 : -3, (getWindowCenter().y - currentPos.y) * 0.2f, 0);
//		mVel *= mDrag;
		currentPos += mVel;
	}
	
}

void Particle_flat::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

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
		for (auto pos : vpos)
		{
			float distance = pos.distance(Vec2f(loc.x, loc.y));
			if (distance < mRadius)
			{
				adjustedColor.a = ci::lmap((float)mAge, 0.f, (float)mLifespan, 1.f, 0.f);
				gl::color(adjustedColor);
				gl::lineWidth(ci::math<float>::clamp(ci::lmap(loc.z, -500.f, 500.f, 0.f, 3.f), 0.f, 3.f));
				glBegin(GL_LINES);
				gl::vertex((randFloat()>.5?-1:1)* getWindowWidth() *randFloat() + loc.x, loc.y, loc.z);
				gl::vertex(loc);
				gl::vertex(loc.x, (randFloat()>.5 ? -1 : 1)* getWindowHeight() *randFloat() + loc.y, loc.z);
				gl::vertex(loc);
				glEnd();
			}
		}
	}

	drawPositions();
}