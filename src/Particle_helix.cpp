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
	mRadiusAnchor = getWindowWidth();
	Listener &listener = Listener::getInstance();
	mRadius = mRadiusAnchor;// *listener.getVolume();

	mAnchorPosition = Vec3f::zero();
	mAnchorPosition.x += getWindowWidth() / 2.f;
	mAnchorPosition.y = getWindowHeight() + 100;
	drawHelix( 6 );

	mColor = ci::Color(1.f, listener.getVolume() * .5f, 0.f);
	mOverlayColor = Color::white();

	mVel = Vec3f(0.f, -40.f, 0.f);
	mDrag = 10.f * listener.getVolume();
	mLifespan = 100;

}

void Particle_helix::drawHelix(const int args_steps)
{
	
	mAngle = 2 * M_PI / args_steps;
	Vec3f temp = Vec3f(1.f, 0.f, 0.f) * mRadius;
	temp.rotateY(getElapsedSeconds());
	for (int steps = 0; steps < args_steps; steps++)
	{
		addPosition(Vec3f(temp) + mAnchorPosition);
		temp.rotateY(mAngle);
	}
}

void Particle_helix::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	Listener &listener = Listener::getInstance();

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		(*iter) += mVel;
		//mVel.rotateZ(mAngle);
	}
}

void Particle_helix::draw(const bool overlay, const std::list < ci::Vec2f> &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}
	adjustedColor.a = mAgeMap;
	gl::color(adjustedColor);
	Listener &listener = Listener::getInstance();
	gl::lineWidth(mDrag);
	glBegin(GL_LINE_STRIP);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		gl::vertex(loc);
	}
	if (mPositions.size() > 2 )
		gl::vertex(mPositions.front());
	glEnd();

	//drawPositions();
}