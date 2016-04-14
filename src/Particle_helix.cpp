#include "Particle_helix.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_helix::Particle_helix(const std::list< ci::Vec2f > &vpos){

	Listener &listener = Listener::getInstance();
	mRadius = listener.getBinVolume(80);
	mRadiusAnchor = 20;

	mColor = ci::Color(randInt(5) * .25f, randInt(5) * .25f, randInt(5) * .25f);
	mOverlayColor = Color::white();

	mVel = Vec3f(0,-10.f, 0);
	mDrag = 1.f;
	mLifespan = 110;

	for (int i = 0; i < mRadiusAnchor; i++)
	{
		addPosition(Vec3f(i * getWindowWidth() / mRadiusAnchor, getWindowHeight(), 0));
	}

}



void Particle_helix::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	Listener &listener = Listener::getInstance();
	mRadius = 10 * listener.getBinVolume(80);
	mVel += mAcc;
	mVel *= mDrag;
	for (auto &pos : mPositions)
	{
		pos += mVel;
	}

}

void Particle_helix::draw(const bool overlay, const std::list < ci::Vec2f> &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}
	gl::color(adjustedColor);
	Listener &listener = Listener::getInstance();
	
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;

		for (auto pos : vpos)
		{
			float distance = pos.distance(Vec2f(loc.x, loc.y));
			if (distance < mRadius)
			{
				mLineWidth = 5.f;
				break;
			}
			else
			{
				mLineWidth = 1.f;
			}
		}

		gl::lineWidth(mLineWidth);
		glBegin(GL_LINES);
		gl::vertex(loc);
		gl::vertex(Vec3f(loc.x + (getWindowWidth() / mRadiusAnchor), loc.y, 0));
		glEnd();
	}
	drawPositions();
}