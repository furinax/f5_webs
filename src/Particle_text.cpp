#include "Particle_text.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Channel32f Particle_text::mName = Channel32f();
Channel32f Particle_text::mProduction = Channel32f();
Channel32f Particle_text::mDate = Channel32f();

Particle_text::Particle_text(const std::list< ci::Vec2f > &vpos){

	if (!mName)
		mName = Channel32f(loadImage(loadResource(RES_NAME)));
	if (!mProduction)
		mProduction = Channel32f(loadImage(loadResource(RES_DOC)));
	if (!mDate)
		mDate = Channel32f(loadImage(loadResource(RES_DATE)));

	mAnchorName = Vec3f(160, 180, 0);
	mAnchorProduction = Vec3f(200, 300, 0);
	mAnchorDate = Vec3f(240, 420, 0);
	for (int i = 0; i < mName.getWidth(); i += 5)
	{
		for (int j = 0; j < mName.getHeight(); j += 5)
		{
			if (mName.getValue(Vec2f(i, j)) == 0.f)
				addPosition(Vec3f(i, j, 200) + mAnchorName);
			if (mProduction.getValue(Vec2f(i, j)) == 0.f)
				addPosition(Vec3f(i, j, 200) + mAnchorProduction);
			if (mDate.getValue(Vec2f(i, j)) == 0.f)
				addPosition(Vec3f(i, j, 200) + mAnchorDate);
		}
	}

	mRadius = 50.f;

	mColor = ci::Color(0.2f, 1.f, 0.2f);
	mOverlayColor = Color::white();

	mVel = Vec3f(2.f,0,0);
	mLifespan = 1000;

}

void Particle_text::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	mVel += mAcc;
	mVel *= mDrag;


	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
		currentPos += mVel * (currentPos.y <= mAnchorProduction.y + 5? 0.8f: currentPos.y <= mAnchorDate.y + 5 ? 1.0f: 1.2f);
	}
}

void Particle_text::draw(const bool overlay, const std::list< ci::Vec2f > &vpos)
{
	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}
	glBegin(GL_LINES);
	gl::color(adjustedColor);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		gl::vertex(Vec3f(loc.x, loc.y, loc.z * mAgeMap));
		gl::vertex(loc);
		/*
		for (auto pos : vpos)
		{
			float distance = pos.distance(Vec2f(loc.x, loc.y));
			if (distance < mRadius)
			{
				adjustedColor.a = ci::lmap(distance, 0.f, mRadius, 1.f, 0.f);
				gl::color(adjustedColor);
				gl::lineWidth(ci::math<float>::clamp(ci::lmap(loc.z, -500.f, 500.f, 0.f, 3.f), 0.f, 3.f));
				glBegin(GL_LINES);
				gl::vertex(pos);
				gl::vertex(loc);
				glEnd();
			}
		}*/
	}
	glEnd();
	drawPositions();
}