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
		addPosition(Vec3f(pos.x, floor(pos.y / 30) * 30, 0));
	
	Listener &listener = Listener::getInstance();
	mRadius = 20 * listener.getBinVolume(50);
	mLineWidth = 5.f * listener.getVolume();
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

	Listener &listener = Listener::getInstance();
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		for (auto pos : vpos)
		{
			adjustedColor.a = ci::lmap((float)mAge, 0.f, (float)mLifespan, 1.f, 0.f);
			gl::color(adjustedColor);
			gl::lineWidth(1);
			glBegin(GL_LINES);
			convexLine((randFloat() > .5 ? -1 : 1)* getWindowWidth() *randFloat(), loc);
			glEnd();
			gl::lineWidth(mLineWidth);
			glBegin(GL_LINES);
			gl::vertex(loc.x, (randFloat() > .5 ? -1 : 1)* getWindowHeight() *randFloat() + loc.y, loc.z);
			gl::vertex(loc);
			glEnd();
			
		}
	}

	drawPositions();
}

void Particle_flat::convexLine(const float offset, const Vec3f loc )
{
	int steps = 20;
	int stepWidth = getWindowWidth() / steps;
	float convexity = 200;
	std::function<int(int)> zCalc = [=](int aStep) ->int{ return convexity * sin( M_PI * aStep / steps  ) ; };
	for (int x = 0; x < steps; x++)
	{
		gl::vertex(stepWidth*x, loc.y, zCalc(x));
		gl::vertex(stepWidth*(x+1), loc.y, zCalc(x+1));
	}

}