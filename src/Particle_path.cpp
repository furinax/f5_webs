#include "Particle_path.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "CatmullRom.h"

Particle_path::Particle_path(const std::list< ci::Vec2f > &vpos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);

	addPosition(mAnchorPosition);
	Listener& listener = Listener::getInstance();

	mAngle = randInt(4) * 2.f * M_PI / 4.f;
	
	mOverlayColor = ci::Color(1.f, .5f * sin(getElapsedSeconds()) + 0.5f, 0.5f * cos(getElapsedSeconds() / 2) + 0.5f);

	mRadius = listener.getBinVolume(100) * 2.f;

	mVel = mRadius * Vec3f(1.f, 0.f, 0.f);
	mVel.rotateZ(mAngle);

	mLifespan = 25;

}

void Particle_path::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	mOverlayColor.a = .1f * mAgeMap;
	mVel += mAcc;
	mVel *= mDrag;
	
	addPosition(Vec3f( mPositions.front() + mVel ));

	mAngle = randInt(4) * 2.f * M_PI / 4.f;
	mVel.rotateZ(mAngle);
}

void Particle_path::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}

	gl::lineWidth(5.f * mAgeMap);

	glBegin(GL_LINE_STRIP);
	adjustedColor.a = mAgeMap;
	gl::color(adjustedColor);
	std::list<ci::Vec2f> mPositions2d;
	std::transform(mPositions.begin(), mPositions.end(),
		std::back_inserter(mPositions2d),
		[](Vec3f p) {return Vec2f(p.x, p.y); }
	);
	CatmullRom::draw(mPositions2d, mLineWidth, 1.f, adjustedColor);
	glEnd();
	
	//drawPositions();
}