#include "Particle_trail.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_trail::Particle_trail(const std::list< ci::Vec2f > &vpos){
	mRadiusAnchor = 50.f;
	Listener &listener = Listener::getInstance();
	mRadius = mRadiusAnchor * listener.getVolume();

	for (auto pos : vpos)
	{
		mAnchorPosition = Vec3f(pos, 0.f);
		addPosition(mAnchorPosition);
	}
	
	mRadiusAnchor = 200.f;

	mColor = ci::Color(1.f, 1.f, 0.f);
	mOverlayColor = Color::white();

	mVel = Vec3f(0,0,-10.f);
	mDrag = 1.f;
	mLifespan = 20;

}

void Particle_trail::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
	Listener &listener = Listener::getInstance();
	mRadius = mRadiusAnchor * listener.getVolume();

	for (auto pos : mPositions)
	{
		pos += mVel;
	}
}