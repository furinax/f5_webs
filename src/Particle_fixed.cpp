#include "Particle_fixed.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_fixed::Particle_fixed(const std::list< ci::Vec2f > &vpos){
	mOrientation = randInt(0, 3);
	Listener &listener = Listener::getInstance();
	
	mRadius = 50.f;
	mRadiusAnchor = 3*mRadius;
	mAnchorPosition = Vec3f(getWindowCenter(), 0.f);
	mAngle = 2 * M_PI / 6;
	mVel = Vec3f(mRadius, 0, 0);
	mVel.rotateZ(2 * M_PI / 3 * mOrientation );

	int alternate = (int)floor(vpos.front().y / mRadiusAnchor) % 2;
	addPosition(Vec3f(mRadiusAnchor * floor(vpos.front().x / mRadiusAnchor) - alternate * mRadius / 2, 130 * floor(vpos.front().y / 130), 0));
	if ( alternate == 1)
		mVel.rotateZ(M_PI);
	mColor = ci::Color(0.f, 1.f, 0.f);
	mOverlayColor = Color::white();
	
	mDrag = 1.f;
	mLifespan = 10;

}

void Particle_fixed::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);


	addPosition(Vec3f(mPositions.front() + mVel));

	/*
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		addPosition(Vec3f( loc + mVel ));
	}*/
	mVel.rotateZ(mAngle);
}

void Particle_fixed::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}
	glBegin(GL_LINE_STRIP);
	gl::color(adjustedColor);
	gl::lineWidth(3.f);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		gl::vertex(loc);

	}
	glEnd();
	
	//drawPositions();
}