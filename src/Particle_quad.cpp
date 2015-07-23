#include "Particle_quad.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_quad::Particle_quad(const std::list< ci::Vec2f > &vpos){
	
	mAngle = 2.f * M_PI / 4.f;
	mAnchorPosition = Vec3f(getWindowCenter(), 0);
	for (float i = 0; i < 4; i++)
	{
		Vec3f pos = getPosition(i);
		addPosition(pos);
	}
	
	mRadius = 100.f;

	mOverlayColor = Color::white();

	mVel = Vec3f(-20.f, -20.f, 0.f);
	mLifespan = 400;
	mDrag = .8f;
}

void Particle_quad::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	mAcc = Vec3f(mPositions.front() - Vec3f(getWindowCenter(), 0));
	mAcc.safeNormalize();
	mAcc *= -2.f;

	mVel += mAcc;
	mVel *= mDrag;

	Vec3f mVelRotated = Vec3f(mVel);
	Listener& listener = Listener::getInstance();
	
	Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0, 0, 1), mAngle);
	mColor = ci::Color(0.3f, 0.f, 0.7f);
	mVelRotated = rotMatrix * mVelRotated;

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter; 
		currentPos += mVelRotated;
		mVelRotated = rotMatrix * mVelRotated;
	}
}

Vec3f Particle_quad::getPosition(const float orientation)
{
	Vec3f retVal;
	Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0, 0, 1), mAngle * orientation + getElapsedSeconds());
	Listener &listener = Listener::getInstance();

	retVal.x = -40;
	retVal.y = -20;
	retVal.z = 0;
	retVal = rotMatrix * retVal + mAnchorPosition;

	return retVal;
}
