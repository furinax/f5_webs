#include "Particle_horizon.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_horizon::Particle_horizon(const Vec2f& pos){
	mAnchorPosition = Vec3f(-getElapsedFrames() % 100, getWindowHeight() *.4f, 0);
	int offset = 10;
	Vec3f center = Vec3f(getWindowCenter().x, getWindowCenter().y, 0.f);
	//cinder::Matrix44f mat = cinder::Matrix44f::createRotation(Vec3f(0, 1, 0), M_PI);
	for (int i = 0; i < 20; i++)
	{
		Vec3f pos3f = Vec3f(mAnchorPosition);
		mAnchorPosition.z += offset;
		offset += 10;
		addPosition(pos3f);
		//Vec3f mirrPos = ( pos3f - center );
		//mirrPos = mat * mirrPos;
		//addPosition(mirrPos + center);
		Vec3f mirrPos = pos3f - center;
		mirrPos.rotateZ(M_PI);
		addPosition(mirrPos + center );
	}

	mAngle = 2 * M_PI / mPositions.size();
	
	mRadius = 75.f;

	mColor = ci::Color(1.f, 0.f, 0.f);
	mOverlayColor = Color::white();

	mVel = Vec3f(50.f, 0.f, 0.f);
	mAcc = Vec3f(-1.f, 0, 0.f);
	mLifespan = 130;

}

void Particle_horizon::update(const ci::Vec2f pos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	mVel += mAcc;
	mVel *= mDrag;

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
		if (currentPos.y < getWindowHeight() * .5)
			currentPos += mVel;
		else
			currentPos -= mVel;
	}
}
