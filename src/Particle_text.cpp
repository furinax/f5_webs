#include "Particle_text.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Channel32f Particle_text::mChannel = Channel32f();

Particle_text::Particle_text(const Vec2f& pos){

	if (!mChannel)
		mChannel = Channel32f(loadImage(loadResource(RES_LOGO)));



	mAnchorPosition = Vec3f(160, 180, 0);
	for (int i = 0; i < mChannel.getWidth(); i += 5)
	{
		for (int j = 0; j < mChannel.getHeight(); j  += 5)
		{
			Vec3f pos3f = Vec3f(i, j, 200) + mAnchorPosition;
			if (mChannel.getValue(Vec2f(i,j))==0.f)
				addPosition(pos3f);
		}
	}

	mRadius = 50.f;

	mColor = ci::Color(0.2f, 1.f, 0.2f);
	mOverlayColor = Color::white();

	mVel = Vec3f(1.f,0,0);
	mLifespan = 1000;

}

void Particle_text::update(const ci::Vec2f pos){
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