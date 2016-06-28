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
	mRadiusAnchor = 50.f;
	Listener &listener = Listener::getInstance();

	mAnchorPosition = Vec3f(getWindowCenter(), 0.f);
	int spokes = 44;
	mAngle = 2 * M_PI / spokes;
	Vec3f temp = Vec3f(1.f, 0, 0);
	temp.rotateZ(getElapsedSeconds()/3.f);
	Matrix44f rotMatrix = Matrix44f::createRotation(Vec3f(0, 0, 1), mAngle);

	
	for (int i = 0; i < spokes; i++ )
	{
		mRadius = 10.f * listener.getBinVolume(i) + mRadiusAnchor;
		temp = rotMatrix * temp;
		addPosition( temp * mRadius );
	}
	
	mRadius = 50.f;

	mColor = ci::ColorA(.9f, .7f, .2f, .1f);
	mOverlayColor.r = listener.getBinVolume(40)/200;
	mOverlayColor.g = 1.f - listener.getBinVolume(40)/200;
	mOverlayColor.b = 1.f - listener.getBinVolume(40)/200;

	mVel = Vec3f(0,0,-10.f);
	mDrag = 1.f;
	mLifespan = 0;

}

void Particle_fft::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

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
	
	int spoke = 0;
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		Listener &listener = Listener::getInstance();
		adjustedColor.a = listener.getBinVolume(spoke);
		gl::color(adjustedColor);
		gl::lineWidth(3.f);
		Vec3f v1 = Vec3f(loc);
		gl::pushMatrices();
		gl::translate(mAnchorPosition);
		glBegin(GL_TRIANGLE_STRIP);
		gl::vertex(v1);
		gl::vertex(v1 * 10);
		glEnd();
		gl::popMatrices();
		spoke++;
	}
	
	drawPositions();
}