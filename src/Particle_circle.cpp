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
	mId = 0;
	Vec3f pos3f = Vec3f(pos.x, pos.y, 0);
	addPosition(pos3f);
	mAnchorPosition = pos3f;
	mAngle = 0;

	mMinRadius = 5.f; mMaxRadius = 10.f;
	mRadius = 10.f;// randFloat(mMaxRadius - mMinRadius) + mMinRadius;
	mRadiusAnchor = mRadius;

	mColor = Color::white();
	mOverlayColor = Color::white();
	mDrag = 1.0f;

	//mVel = Vec3f(0, -randFloat(20) - 20.f, 0);
	mLifespan = 0;

	mColor = ColorA(1,1,1,1);
}

void Particle_circle::update(const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	Vec3f newPos = Vec3f(mPositions.front());
	mVel += mAcc;
	mVel *= mDrag;
	newPos += mVel;
	addPosition(newPos);

	Vec2f temp(mVel.x, mVel.y);
	temp.safeNormalize();
	mAngle = 180 + angle(temp);
}

void Particle_circle::draw(const bool overlay, const ci::Vec2f pos){
	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = Color::white();
	}

	Vec3f &loc = mPositions.front();
	gl::lineWidth(2.f);
	glBegin(GL_LINES);
	gl::vertex(pos);
	gl::vertex(loc);
	glEnd();

}