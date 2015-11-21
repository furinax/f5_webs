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

	mRadiusAnchor = 25.f;
	mRadius = 150;// *randFloat();
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);
	for (mAnchorPosition.x = getWindowWidth() / 12.f; mAnchorPosition.x < getWindowWidth(); mAnchorPosition.x += getWindowWidth() / 6.f)
	{
		for (mAnchorPosition.y = getWindowHeight() / 6.f; mAnchorPosition.y < getWindowHeight(); mAnchorPosition.y += getWindowHeight() / 3.f)
		{
			addPosition(mAnchorPosition);
		}
	}
	Listener &listener = Listener::getInstance();

	

	mColor = ci::Color(0, abs(sin(getElapsedSeconds())), abs(cos(getElapsedSeconds())));
	mOverlayColor = Color::white();

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

	for (auto i = mPositions.begin(); i != mPositions.end(); i++)
	{
		*i += mVel;
	}
	mVel *= mDrag;
}