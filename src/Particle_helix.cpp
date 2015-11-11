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

	mRadius = 50.f;
	mDrag = .95f;

	mOverlayColor = Color::white();
	Listener& listener = Listener::getInstance();
	mAnchorPosition = Vec3f(getWindowWidth() * randFloat(), getWindowHeight() * randFloat() , 0);
	addPosition(mAnchorPosition);

	mVel = Vec3f::zero();
	mLifespan = 230;
	mSet = false;
}

void Particle_helix::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	Listener &listener = Listener::getInstance();

	mVel *= mDrag;
	float map = ci::lmap(
		abs(mPositions.front().y - getWindowHeight()), (float)getWindowHeight(), 0.f, 0.f, 1.f);
	mColor = ci::Color( map,
		.4f * map, //green value
		1.f - map); // blue value


	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter; 
		currentPos += mVel;
		for (auto pos : vpos)
		{
			float distance = pos.distance(Vec2f(currentPos.x, currentPos.y));
			if (!mSet && distance < mRadius)
			{
				mSet = true;
				mAnchorPosition = Vec3f(pos, 0);
			}
		}
	}
}

void Particle_helix::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

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
			if (mSet)
			{
				if (overlay)
					adjustedColor.a = mAgeMap/2.f;
				else
					adjustedColor.a = 1.f;
				gl::color(adjustedColor);
				gl::lineWidth(ci::math<float>::clamp(ci::lmap(loc.z, -500.f, 500.f, 0.f, 3.f), 0.f, 3.f));
				glBegin(GL_LINES);
				gl::vertex(mAnchorPosition);
				gl::vertex(loc);
				glEnd();
			}
			else if (distance < mRadius)
			{
				adjustedColor.a = ci::lmap(distance, 0.f, mRadius, 1.f, 0.f);
				gl::color(adjustedColor);
				gl::lineWidth(ci::math<float>::clamp(ci::lmap(loc.z, -500.f, 500.f, 0.f, 3.f), 0.f, 3.f));
				glBegin(GL_LINES);
				gl::vertex(pos);
				gl::vertex(loc);
				glEnd();
			}
		}
	}

	drawPositions();
}