#include "Particle_fft.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_fft::Particle_fft(const std::list< ci::Vec2f > &vpos){
	mRadiusAnchor = 10.f;
	Listener &listener = Listener::getInstance();
	

	mAnchorPosition = Vec3f(getWindowCenter(), 0.f);
	int spokes = 44;
	mAngle = 2 * M_PI / spokes;
	Vec3f temp = Vec3f(1.f, 0, 0);
	Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0, 0, 1), mAngle);

	for (int i = 0; i < spokes; i++ )
	{
		mRadius = mRadiusAnchor * listener.getBinVolume(i);
		temp = rotMatrix * temp;
		addPosition( temp * mRadius + mAnchorPosition);
	}
	
	mRadius = 400.f;

	mColor = ci::Color(0.f, 0.f, 1.f);
	mOverlayColor = Color::white();

	mVel = Vec3f(0,0,-10.f);
	mDrag = 1.f;
	mLifespan = 0;

}

void Particle_fft::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
	Listener &listener = Listener::getInstance();

	for (auto pos : mPositions)
	{
		pos += mVel;
	}
}

void Particle_fft::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;

		gl::color(adjustedColor);
		gl::lineWidth(ci::math<float>::clamp(ci::lmap(loc.z, -500.f, 500.f, 0.f, 3.f), 0.f, 3.f));
		glBegin(GL_LINES);
		gl::vertex(mAnchorPosition);
		gl::vertex(loc);
		glEnd();

	}

	//drawPositions();
}