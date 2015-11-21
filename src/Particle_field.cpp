#include "Particle_field.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

int Particle_field::mThrottle = Particle_field::mThrottleMax;

Particle_field::Particle_field(const std::list< ci::Vec2f > &vpos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);

	mRadius = 400.f;
	mAngle = .1f;

	for (int i = 1; i <= 30; i++)
	{
		addPosition(Vec3f(0, getWindowHeight() / 30 * i, 0));
	}

	mColor = ci::Color(pow(sin(getElapsedSeconds()),2), abs(cos(getElapsedSeconds())), .5f * sin(getElapsedSeconds()/2)+.5f);
	mOverlayColor = ci::Color(1.f, 1.f, 1.f);

	mVel = Vec3f(10,0,-2);
	mAcc = Vec3f(0,0, 0);
	mLifespan = 250;

}

void Particle_field::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	mVel += mAcc;
	mVel *= mDrag;

	Vec3f mVelRotated = Vec3f(mVel);

	for (auto i = mPositions.begin(); i != mPositions.end(); i++)
	{
		Vec3f &currentPos = *i;
		
		currentPos += mVelRotated;
	}
}

void Particle_field::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}

	Listener& listener = Listener::getInstance();

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		float distance = loc.distance( Vec3f( getWindowCenter(), 0));
		if ( distance < mRadius )
		{
			adjustedColor.a = listener.getVolume() > 1 - (loc.y / getWindowHeight()) ? 1.f : .05f;
			gl::color(adjustedColor);
			gl::lineWidth(ci::math<float>::clamp(ci::lmap(loc.z, -500.f, 500.f, 0.f, 3.f), 0.f, 3.f));
			glBegin(GL_LINES);
			gl::vertex(getWindowCenter());
			gl::vertex(loc);
			glEnd();
		}
	}

	drawPositions();
}