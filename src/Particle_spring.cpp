#include "Particle_spring.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_spring::Particle_spring(const std::list< ci::Vec2f > &vpos){
	Listener &listener = Listener::getInstance();
	mRadiusAnchor = 25.f;
	mRadius = 10 * listener.getBinVolume(24);
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);
	for (mAnchorPosition.x = getWindowWidth() / 12.f; mAnchorPosition.x < getWindowWidth(); mAnchorPosition.x += getWindowWidth() / 6.f)
	{
		for (mAnchorPosition.y = getWindowHeight() / 6.f; mAnchorPosition.y < getWindowHeight(); mAnchorPosition.y += getWindowHeight() / 3.f)
		{
			addPosition(mAnchorPosition);
		}
	}
	

	

	mColor = ci::Color(0, abs(sin(getElapsedSeconds())), abs(cos(getElapsedSeconds())));
	mOverlayColor = Color::white();
	mOverlayColor.a = 0.f;

	mVel = Vec3f(mRadiusAnchor * randVec2f(), 0); //this is a base, we will rotate it based on mAnchorPosition
	mDrag = .60f;
	mLifespan = 100;

}

void Particle_spring::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	Listener &listener = Listener::getInstance();
	mRadius = 10 * listener.getBinVolume(24);
	for (auto i = mPositions.begin(); i != mPositions.end(); i++)
	{
		*i += mVel;
	}
	mVel *= mDrag;
}

void Particle_spring::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

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
				adjustedColor.a = ci::lmap(distance, 0.f, mRadius, 1.f, 0.f);
				gl::color(adjustedColor);
				gl::lineWidth(ci::math<float>::clamp(ci::lmap(loc.z, -500.f, 500.f, 0.f, 3.f), 0.f, 3.f));
				glBegin(GL_LINES);
				gl::vertex(Vec2f(loc.x, pos.y));
				gl::vertex(loc);
				glEnd();
			}
		}
	}

	//drawPositions();
}