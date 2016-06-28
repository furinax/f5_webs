#include "Particle_ripple.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_ripple::Particle_ripple(const std::list< ci::Vec2f > &vpos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);

	for (int i = 0; i < 360; i++)
	{
		Vec3f pos3f = Vec3f(0, 0 ,0);
		addPosition(pos3f);
	}

	mAngle = 2 * M_PI / mPositions.size();
	
	Listener& listener = Listener::getInstance();


	//mColor = ci::Color(1.f, .5f * sin( getElapsedSeconds() )+0.5f, 0.5f * cos( getElapsedSeconds() / 2) + 0.5f );
	mOverlayColor = ci::Color(1.f, .5f * sin(getElapsedSeconds()) + 0.5f, 0.5f * cos(getElapsedSeconds() / 2) + 0.5f);

	mRadius = listener.getBinVolume(100)*.1f;

	mVel = Vec3f(0, listener.getBinVolume(24), 0);
	mVel.rotateZ(getElapsedSeconds()* 2);

	mLifespan = 25;
	mDrag = .98f;

}

void Particle_ripple::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	mOverlayColor.a = .5f * mAgeMap;
	mColor.a = .5f * mAgeMap;
	mVel += mAcc;
	mVel *= mDrag;

	Vec3f velocityRotated = Vec3f(mVel);
	
	Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0, 0, 1), mAngle);
	int i = 0;
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
		Vec3f unitVectorRotated = Vec3f(velocityRotated); unitVectorRotated.normalize();
		currentPos += velocityRotated + unitVectorRotated * mRadius * sin(i++);
		velocityRotated = rotMatrix * velocityRotated;
	}
}

void Particle_ripple::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}
	gl::pushMatrices();
	gl::translate(mAnchorPosition);

	gl::lineWidth(5.f * mAgeMap);

	glBegin(GL_LINE_LOOP);
	gl::color(adjustedColor);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		gl::vertex(loc);

	}
	glEnd();

	gl::popMatrices();
	
	//drawPositions();
}