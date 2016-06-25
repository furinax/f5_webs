#include "Particle_torrent.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_torrent::Particle_torrent(const std::list< ci::Vec2f > &vpos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);
	addPosition(mAnchorPosition);

	mRadiusAnchor = 50.f;
	mRadius = 50;

	mOverlayColor = ci::Color(.9, .5, .9);
	mColor = ci::Color(.4f, 0.2f, 0);

	mDrag = .9f;
	mLifespan = 5;

	mVel = Vec3f(35 * randVec2f(), 0);
	for (int i = 0; i < 100; i++)
	{
		mVel.rotateZ(mPerlin.fBm(Vec3f(mPositions.front())));
		addPosition(mPositions.front() + mVel);
	}

}

void Particle_torrent::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
}

void Particle_torrent::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}
	gl::color(adjustedColor);
	Listener &listener = Listener::getInstance();
	if (mLineWidth != 0)
	{
		gl::lineWidth(mLineWidth);
		//gl::pushMatrices();
		//gl::rotate(20 * sin(getElapsedSeconds() / 8.f));
		glBegin(GL_LINE_STRIP);

		for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
		{
			Vec3f &loc = *iter;
			gl::vertex(loc);
		}
		glEnd();
		//gl::popMatrices();
	}
	//drawPositions();
}