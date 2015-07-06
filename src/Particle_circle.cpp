#include "Particle_circle.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_circle::Particle_circle(const Vec2f& pos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);

	for (int i = 0; i < 36; i++)
	{
		Vec3f pos3f = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);
		addPosition(pos3f);
	}

	mAngle = 2 * M_PI / mPositions.size();

	mRadius = 100.f;
	mRadiusAnchor = mRadius;

	mColor = ci::Color(0.f, 0.f, 1.f);
	mOverlayColor = Color::white();
	mDrag = 1.0f;

	mVel = Vec3f(0, 30.f, 50 * sin(getElapsedSeconds())); //this is a base, we will rotate it based on mAnchorPosition
	mLifespan = 100;

}

void Particle_circle::update(const ci::Vec2f pos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
	mVel += mAcc;
	mVel *= mDrag;

	Vec3f mVelRotated = Vec3f(mVel);
	Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0, 0, 1), mAngle);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
		currentPos += mVelRotated;
		mVelRotated = rotMatrix * mVelRotated;
	}
}