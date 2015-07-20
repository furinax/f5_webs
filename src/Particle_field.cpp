#include "Particle_field.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

int Particle_field::mThrottle = Particle_field::mThrottleMax;

Particle_field::Particle_field(const Vec2f& pos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);

	mRadius = 400.f;
	mAngle = .1f;

	for (int i = 1; i <= 30; i++)
	{
		addPosition(Vec3f(0, getWindowHeight() / 30 * i, 0));
	}

	mColor = ci::Color(1.f, 1.f, 1.f);
	mOverlayColor = Color::white();

	mVel = Vec3f(10,0,-2);
	mAcc = Vec3f(0,0, 0);
	mLifespan = 250;

}

void Particle_field::update(const ci::Vec2f pos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	mVel += mAcc;
	mVel *= mDrag;

	Vec3f mVelRotated = Vec3f(mVel);
	//Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0, 0, 1), mAngle);

	for (auto i = mPositions.begin(); i != mPositions.end(); i++)
	{
		Vec3f &currentPos = *i;
		
		//currentPos += mVelRotated;
		currentPos += mVelRotated;
		//mVelRotated = rotMatrix * mVelRotated;
		//mVelRotated += mAcc;
	}
}