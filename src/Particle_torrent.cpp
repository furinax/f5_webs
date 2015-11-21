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
	mRadius = 50;// *randFloat();

	mColor = ci::Color(.4f, 0.2f, 0.f);
	mOverlayColor = ci::Color(.9, .5, .9);

	mVel = Vec3f(35 * randVec2f() , 0); //this is a base, we will rotate it based on mAnchorPosition
	mDrag = .9f;
	mLifespan = 100;

}

void Particle_torrent::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);
	
	Listener &listener = Listener::getInstance();
	mRadius = listener.getVolume()*mRadiusAnchor;

	float noise = mPerlin.fBm(Vec3f(mPositions.front() * (0.005f + (float)getElapsedSeconds())));
	float angle = noise * 15.f;
	Vec3f noiseVector(cos(angle), sin(angle), cos(angle)+0.5f);
	mVel *= mDrag;
	mVel += noiseVector * 10.f * mAgeMap;
	addPosition(mPositions.front() + mVel);

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		for (auto pos : vpos)
		{
			float distance = pos.distance(Vec2f(loc.x, loc.y));
			if (distance < mRadius)
			{
				mLineWidth = ci::lmap(distance, 0.f, mRadius, 5.f, 2.f);
				mOverlayColor = ci::Color(.8, .5, .8);
				return;
			}
			else
			{
				mLineWidth = 1.f;
				mOverlayColor = ci::Color(0.f, .2f, .7f);
			}
		}
	}
	
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
	gl::lineWidth(mLineWidth);
	gl::pushMatrices();
	gl::rotate(20*sin(getElapsedSeconds()/8.f));
	glBegin(GL_LINE_STRIP);

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		gl::vertex(loc);
	}
	glEnd();
	gl::popMatrices();
	//drawPositions();
}