#include "Particle_queue.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "cinder/CinderMath.h"

Particle_queue::Particle_queue(const std::list< ci::Vec2f > &vpos){
	mAnchorPosition = Vec3f(getWindowCenter().x, getWindowCenter().y, 500);
	for each (auto pos in vpos)
	{
		addPosition(Vec3f(pos - getWindowCenter(), 200));
	}
	
	mRadius = 100.f;
	mVel = Vec3f(0,0,-20.f);
	Listener &listener = Listener::getInstance();
	mColor = ci::Color(.5f, 0, 0.5f);
	mOverlayColor = Color(1.f, .65f, 0.f);
	mLineWidth = 10.f;
	mDrag = .95f;
	mLifespan = 60;// abs(mAnchorPosition.z / mVel.z);

}

void Particle_queue::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	mOverlayColor = Color(1 - mAgeMap / 2.f, .65f * mAgeMap, -.5f * mAgeMap + .5f);
	mLineWidth *= mDrag;
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
		currentPos += mVel;
	}
	
}

void Particle_queue::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}

	gl::lineWidth(mLineWidth);
	gl::pushMatrices();
	gl::translate(getWindowCenter());
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		for (auto pos : vpos)
		{
			//float distance = pos.distance(Vec2f(loc.x, loc.y) + getWindowCenter());
			//if (distance < mRadius)
			{
				//adjustedColor.r = ci::lmap((float)mAge, 0.f, (float)mLifespan, 1.f, 0.f);
				gl::color(adjustedColor);
				glBegin(GL_LINES);
				gl::vertex(loc );
				gl::vertex(loc *1.5);
				glEnd();
				
			}
		}
	}
	drawPositions();
	gl::popMatrices();
}