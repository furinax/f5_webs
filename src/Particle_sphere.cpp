#include "Particle_sphere.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "cinder/CinderMath.h"

Particle_sphere::Particle_sphere(const std::list< ci::Vec2f > &vpos){
	mRadius = 200.f;

	Listener &listener = Listener::getInstance();
	mRadiusAnchor = getWindowWidth();// *listener.getVolume();

	mAnchorPosition = Vec3f(0, getWindowHeight() + mRadius, 0);//100 * sin(getElapsedSeconds()));
	for (; mAnchorPosition.x < getWindowWidth(); mAnchorPosition.x += mRadius / 10.f)
		addPosition(mAnchorPosition);
	Vec3f temp = Vec3f(1.f, 0, 0);

	//mOverlayColor = ci::Color(listener.getVolume(), .2f, 1.f);
	mColor = ci::Color(0.f, 0.f, 1.f);
	mOverlayColor = Color::white();

	mVel = Vec3f(0.f, -20.f, 0.f);
	mDrag = 1.f;
	//mDrag = 2.f * randFloat() + 1.f;
	mLifespan = 200;
}

void Particle_sphere::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	mVel += mAcc;
	Listener &listener = Listener::getInstance();
	mRadius = 200.f * listener.getVolume();
	mAngle = 90.f * listener.getVolume();

	addPosition(Vec3f(mRadiusAnchor * cos(mAge), getWindowHeight() + mRadius, 0));

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
		currentPos += mVel;
	}
}

void Particle_sphere::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}

	Listener &listener = Listener::getInstance();
	//adjustedColor.a = overlay ? listener.getVolume() : 1.f;
	gl::color(adjustedColor);

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		ci::Vec3f &loc = *iter;
		for (auto pos : vpos)
		{
			if (isActive(pos, loc))
			{
				gl::lineWidth(listener.getVolume() * 2.f + 1.f);
				glBegin(GL_LINES);
				gl::vertex(loc);
				Vec3f sister(loc - Vec3f(pos));
				sister.rotateZ(mAngle);
				sister *= mDrag;
				sister += Vec3f(pos);
				gl::vertex(sister);
				glEnd();
			}
		}
	}

	drawPositions();
}

bool Particle_sphere::isActive(const ci::Vec2f &lpos, const ci::Vec3f &rpos)
{
	float distance = lpos.distance(Vec2f(rpos.x, rpos.y));
	return distance > .8f * mRadius && distance < mRadius;
}