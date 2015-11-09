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
	
	

	mRadius = 100.f;
	mDrag = .95f;

	mOverlayColor = Color::white();
	Listener& listener = Listener::getInstance();
	mAnchorPosition = Vec3f(getWindowCenter().x + 100.f * sin(getElapsedFrames()), getWindowHeight(), 0);
	addPosition(mAnchorPosition);

	mVel = Vec3f(listener.getVolume() * 100.f, -10.f, randFloat() * 10.f);
	mLifespan = 230;

}

void Particle_helix::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	mAcc.x = mPositions.front().x - getWindowCenter().x < 0 ? 4 : -4;
	mVel += mAcc;
	mVel.x *= mDrag;
	float map = ci::lmap(
		abs(mPositions.front().y - getWindowHeight()), (float)getWindowHeight(), 0.f, 0.f, 1.f);
	mColor = ci::Color( map,
		.4f * map, //green value
		1.f - map); // blue value

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter; 
		currentPos += mVel;
	}
}
