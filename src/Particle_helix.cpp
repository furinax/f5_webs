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
	Vec3f pos1 = getPosition(mOrientation);

	addPosition(pos1);

	mAngle = 2.f * M_PI / 36.f;

	mRadius = 100.f;

	mOverlayColor = Color::white();

	mVel = Vec3f(0.f, -10.f, 0.f);
	mLifespan = 200;

}

void Particle_helix::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	mColor = ci::Color(0.3f, ci::lmap(mOrientation, 0.f, 3.1415f, 0.f, 1.f), 0.7f);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter; 
		currentPos = getPosition(mOrientation);
	}
}

Vec3f Particle_helix::getPosition(const float offset)
{
	Vec3f retVal;
	//cinder::Matrix44f mat = cinder::Matrix44f::createRotation(Vec3f(0, 1, 0), M_PI/4.f);

	retVal.x = 50 * cos(mAge / 15.f + offset + getElapsedSeconds()) + getWindowCenter().x;
	retVal.y = 100 + getWindowHeight() - mAge * 15;
	retVal.z = 50 * sin(mAge / 15.f + offset + getElapsedSeconds());

	retVal.rotateZ(M_PI / 4.f);
	return retVal;
}
