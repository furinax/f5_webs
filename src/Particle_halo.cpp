#include "Particle_halo.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_halo::Particle_halo(const std::list< ci::Vec2f > &vpos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);

	mAngle = 2.f * M_PI / 36.f;
	Vec3f temp = Vec3f(200.f,0.f,500.f);
	Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0.f, 0.f, 1.f), mAngle);
	for (int i = 0; i < 36; i++)
	{
		addPosition(temp + mAnchorPosition);
		temp = rotMatrix * temp;
	}

	mRadius = 200.f;

	mColor = ci::Color(0.f, 1.f, 1.f);
	mOverlayColor = Color::white();

	//mVel = Vec3f(0, 30.f, 50 * sin(getElapsedSeconds())); //this is a base, we will rotate it based on mAnchorPosition
	mLifespan = 1;

}

void Particle_halo::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
	mVel += mAcc;
	mVel *= mDrag;

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
	}
}