#include "Particle_circle.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_circle::Particle_circle(const std::list< ci::Vec2f > &vpos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);

	for (int i = 0; i < 36; i++)
	{
		Vec3f pos3f = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);
		addPosition(pos3f);
	}

	mAngle = 2 * M_PI / mPositions.size();

	mRadius = 100.f;

	mColor = ci::Color(1.f, 0.f, 0.f);
	mOverlayColor = Color::white();
	Listener& listener = Listener::getInstance();

	mVel = Vec3f(0, 30.f, 3 * listener.getBinVolume(24)); //this is a base, we will rotate it based on mAnchorPosition
	mVel.rotateZ(getElapsedSeconds());

	mLifespan = 20;

}

void Particle_circle::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
	mVel += mAcc;
	mVel *= mDrag;
	mColor = Color(mAgeMap, 0, 1 - mAgeMap);
	Vec3f mVelRotated = Vec3f(mVel);
	Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0, 0, 1), mAngle);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
		currentPos += mVelRotated;
		mVelRotated = rotMatrix * mVelRotated;
	}
}