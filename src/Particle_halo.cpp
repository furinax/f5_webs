#include "Particle_halo.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "CatmullRom.h"

Particle_halo::Particle_halo(const std::list< ci::Vec2f > &vpos){
	mMinRadius = 50;
	Listener &listener = Listener::getInstance();
	mAnchorPosition = Vec3f(getWindowCenter(), 0);
	mRadiusAnchor = 500.f;
	mRadius = 50 * listener.getVolume() + mMinRadius;
	mAngle = .25f*listener.getBinVolume(32);
	mLineWidth = 5;

	float s = getElapsedSeconds();

	for (auto pos : vpos )
	{
		Vec2f temp = (pos - getWindowCenter());
		temp.safeNormalize();
		temp *= getWindowHeight();
		temp.rotate(-mAngle);
		addPosition(Vec3f(temp));
		addPosition(.5f*Vec3f(pos - getWindowCenter()));
		temp.rotate(2 * mAngle);
		addPosition(Vec3f(temp));
	}

	
	mColor = ci::Color(randInt(5) * .25f, randInt(5) * .25f, randInt(5) * .25f);
	mOverlayColor = 1.5 * mColor;

	mLifespan = 5;

}

void Particle_halo::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	mColor.a = mAgeMap;
	mOverlayColor.a = mAgeMap;
	
	Listener &listener = Listener::getInstance();
	//mRadius = 50 * listener.getVolume() + mMinRadius;
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
	glBegin(GL_LINE_STRIP);
	
	for (auto iterator = mPositions.begin(), end = mPositions.end(); iterator != end; std::advance(iterator, 3))
	{
		std::list<ci::Vec2f> mPositions2d;

		auto end_iter = iterator;
		std::advance(end_iter, 3);

		std::transform(iterator, end_iter,
			std::back_inserter(mPositions2d),
			[](Vec3f p) {return Vec2f(p.x, p.y); });
		CatmullRom::draw(mPositions2d, mLineWidth, 1.f, adjustedColor);
	}
	glEnd();

	//drawPositions();

	gl::popMatrices();
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