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
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);
	addPosition(mAnchorPosition);

	mRadius = 250;// *randFloat();

	mColor = ci::Color(1.f, 0.f, 0.f);
	mOverlayColor = Color::white();

	mVel = Vec3f(35 * randVec2f(), 0); //this is a base, we will rotate it based on mAnchorPosition
	mDrag = .80f;
	mLifespan = 100;

}

void Particle_spring::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

//	float noise = mPerlin.fBm(mPositions.front().x , mPositions.front().y, getElapsedSeconds() * 0.1f);
//	float angle = noise * 15.f;
//	Vec3f noiseVector(cos(angle), sin(angle), cos(angle));
//	mVel += noiseVector * 5.f * mAgeMap;
	mPositions.front() += mVel;
	mVel.x *= mDrag;
	mVel.y *= mDrag;
}