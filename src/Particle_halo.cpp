#include "Particle_halo.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_halo::Particle_halo(const std::list< ci::Vec2f > &vpos){
	mMinRadius = 50;
	mAnchorPosition = Vec3f(getWindowCenter(), 0);
	Listener &listener = Listener::getInstance();
	mRadiusAnchor = 500.f;
	mRadius = 50 * listener.getVolume() + mMinRadius;
	mLineWidth = 5.f * listener.getVolume();

	float s = getElapsedSeconds();

	for (auto pos : vpos )
	{
		Vec3f temp = Vec3f(pos - getWindowCenter());
		temp.safeNormalize();
		roundAngle(temp, 2.f * M_PI / 100.f);
		addPosition(temp);
	}

	
	mColor = ci::Color(randInt(5) * .25f, randInt(5) * .25f, randInt(5) * .25f);
	mOverlayColor = ci::Color::white();

	mLifespan = 40;

}

void Particle_halo::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
	Listener &listener = Listener::getInstance();
	mRadius = 50 * listener.getVolume() + mMinRadius;
}

void Particle_halo::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){
	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}

	Listener &listener = Listener::getInstance();
	gl::pushMatrices();
	gl::translate(mAnchorPosition);
	gl::lineWidth(mLineWidth);
	glBegin(GL_LINES);
	
	float step = (mRadiusAnchor - mMinRadius) / 10.f;
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		for (float tempRadius = mRadius; tempRadius < mRadiusAnchor; tempRadius += step)
		{
			Vec3f &loc = *iter;
			mAngle = sin(loc.y / loc.x);
			gl::color(adjustedColor);
			gl::vertex((tempRadius + step) * loc);
		}
	}
	glEnd();
	gl::popMatrices();
	drawPositions();
}

void Particle_halo::roundAngle(ci::Vec3f& pos, const float denomination)
{
	float angle = asin((pos.x > 0 ? -1 : 1) * pos.y);
	float iPart;
	float fPart = modf(angle / denomination, &iPart);
	if (fPart > 0.5f)
		fPart -= 1.f;
	pos.rotateZ(fPart * denomination);
}