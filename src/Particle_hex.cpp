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
	mRadiusAnchor = 50.f;
	Listener &listener = Listener::getInstance();
	mRadius = mRadiusAnchor * listener.getVolume();

	mAnchorPosition = Vec3f(getWindowCenter(), 0);
	drawHex(6, 0, 0, 100, 100);

	mColor = ci::Color(1.f, listener.getVolume() * .5f, 0.f);
	mOverlayColor = Color::white();

	mVel = Vec3f(10.f * cos(getElapsedSeconds()), 10.f * sin(getElapsedSeconds()),0);
	mDrag = 1.f;
	mLifespan = 100;

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
	
	Listener &listener = Listener::getInstance();

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		(*iter) += mVel;
		mVel.rotateZ(mAngle);
	}
	mColor.r = mAgeMap;
	mColor.g = mAgeMap * listener.getVolume() * .5f;
	mColor.b = 1 - mAgeMap;
	mVel *= 1.2f * listener.getVolume();
}

void Particle_hex::draw(const bool overlay, const std::list < ci::Vec2f> &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}
	adjustedColor.a = mAgeMap;

	gl::pushMatrices();
	gl::translate(mAnchorPosition);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;

		gl::color(adjustedColor);
		glBegin(GL_LINES);
		gl::vertex(Vec3f::zero() );
		gl::vertex(loc);
		glEnd();
	}

	gl::popMatrices();

	//drawPositions();
}