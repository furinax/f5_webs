#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/AppNative.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"
#include "cinder/CinderMath.h"
#include <iterator>
#include <list>


class Particle{
public:

	virtual void update(const ci::Vec2f pos) = 0;
	void draw(const bool overlay, const ci::Vec2f pos);
	void addPosition(const ci::Vec3f & pos);
	float angle(const ci::Vec2f &lhs);
	void drawPositions();

	//position members
	int mId;
	std::list<ci::Vec3f> mPositions;
	ci::Vec3f mAnchorPosition;
	ci::Vec3f mVel, mAcc;
	float mDrag = 1.f;
	float mAngle = 0.f;

	//size members
	float mRadiusAnchor = 2.f, mRadius = 2.f;
	float mMaxRadius = 5.f, mMinRadius = 2.f;
	float mLineWidth = 1.f;

	//color members
	ci::ColorA mColor, mOverlayColor;

	//lifetime members
	int mAge = 0, mLifespan = 20;
	bool mIsDead = false;
	float mAgeMap = 1.f;

	//other members
	static ci::Perlin mPerlin;
	int mOrientation = 1; //used for rotation, angle, etc

};