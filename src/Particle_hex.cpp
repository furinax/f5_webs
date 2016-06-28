#include "Particle_hex.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_hex::Particle_hex(const std::list< ci::Vec2f > &vpos){
	mRadiusAnchor = .6f;
	Listener &listener = Listener::getInstance();
	mRadius = mRadiusAnchor * listener.getBinVolume(24);
	mLineWidth = 2.f;
	mAnchorPosition = Vec3f(getWindowWidth()/2.f, getWindowHeight()/2.f, 0);
	drawHex(6, 0, 0, 200, 200);
	
	mColor = Color::black();
	mOverlayColor = ci::Color(.3f, 0.1f, listener.getVolume());

	mVel = Vec3f(mRadius * cos(getElapsedSeconds()), mRadius * sin(getElapsedSeconds()), 0);
	mDrag = listener.getVolume();
	mLifespan = 2 * listener.getBinVolume(40);

}

void Particle_hex::drawHex(const int args_steps, const int offsetX = 0, const int offsetY = 0, const int width = 100, const int height = 100)
{
	mAnchorPosition += Vec3f(offsetX, offsetY, 0);
	mAngle = 2 * M_PI / args_steps;

	float angle = 0.f;
	for (int steps = 0; steps < args_steps; steps++)
	{
		addPosition(Vec3f(width*cos(angle), height*sin(angle), 0));
		angle += mAngle;
	}
}

void Particle_hex::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	mColor.a = mAgeMap * mAgeMap;
	mOverlayColor.a = mAgeMap * mAgeMap;
	mVel *= mDrag * mDrag;

	Listener &listener = Listener::getInstance();

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		(*iter) += mVel;
		mVel.rotateZ(mAngle);
	}
}

void Particle_hex::draw(const bool overlay, const std::list < ci::Vec2f> &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}

	gl::pushMatrices();
	gl::translate(mAnchorPosition);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		Listener &listener = Listener::getInstance();
		adjustedColor.a = listener.getBinVolume(40) / 100.f;
		gl::color(adjustedColor);
		//gl::lineWidth(mLineWidth);
		glBegin(GL_LINES);
		gl::vertex(Vec2f::zero() );
		gl::vertex(loc);
		glEnd();
	}

	gl::popMatrices();

	//drawPositions();
}