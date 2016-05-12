#include "Particle_sphere.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "cinder/CinderMath.h"

Particle_sphere::Particle_sphere(const std::list< ci::Vec2f > &vpos){
	mRadius = 150.f;
	
	Listener &listener = Listener::getInstance();
	const Vec2f &pos = vpos.size() == 0 ? getWindowCenter() : 
		vpos.size() >= 2 ? ( randFloat() >= .5f ? vpos.front() : vpos.back() )
		: vpos.front();
	mAnchorPosition = Vec3f(pos,0);
	addPosition(mAnchorPosition);

	mColor = ci::Color(0.f, 0.f, 1.f);
	mOverlayColor = Color::white();
	mLineWidth = listener.getVolume() * 5.f + 1.f;
	mAcc = 10.f * randVec3f();
	mVel = 7.f * mAcc;
	mDrag = .8f;
	mAngle = .25f * sin(getElapsedSeconds());
	mLifespan = 50;
}

void Particle_sphere::update(const std::list< ci::Vec2f > &vpos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);


	Listener &listener = Listener::getInstance();
	mLineWidth *= .95f;
	mColor = Color(sin(getElapsedSeconds()), .6 * sin(getElapsedSeconds() / 2.f), tan(getElapsedSeconds()));

	if (mPositions.size() >= 2 && vpos.size() > 0 )
	{
		float distanceF = Vec3f(vpos.front(), 0).distance(mAnchorPosition);
		float distanceL = Vec3f(vpos.back(), 0).distance(mAnchorPosition);
		mAnchorPosition = distanceL > distanceF ? Vec3f(vpos.front(), 0):  Vec3f(vpos.back(), 0);
		mAcc = (distanceL > distanceF ? -1 : 1) * .025f * (Vec3f(vpos.front(), 0) - Vec3f(vpos.back(), 0));
		reAnchor();
	}

	mVel.rotateZ(rand());
	mVel += mAcc;
	mVel *= mDrag;

	Vec3f &loc = mPositions.front();
	addPosition(Vec3f(loc + mVel));
}

void Particle_sphere::draw(const bool overlay, const std::list< ci::Vec2f > &vpos){

	ColorA adjustedColor;
	if (!overlay)
		adjustedColor = ColorA(mColor);
	else
	{
		adjustedColor = ColorA(mOverlayColor);
	}

	Listener &listener = Listener::getInstance();
	gl::lineWidth(mLineWidth);
	adjustedColor.a = listener.getVolume();
	gl::color(adjustedColor);
	glBegin(GL_LINE_STRIP);
	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &loc = *iter;
		gl::vertex(loc);
	}
	glEnd();
	//drawPositions();
}

bool Particle_sphere::isActive(const ci::Vec2f &lpos, const ci::Vec3f &rpos)
{
	float distance = lpos.distance(Vec2f(rpos.x, rpos.y));
	//float distMap = ci::lmap(distance, 0.f, mRadius, 0.f, 1.f);
	//gl::color( distMap, pow(sin(getElapsedSeconds()), 2), 1-distMap);
	return distance > .8f * mRadius && distance < mRadius;
}

void Particle_sphere::reAnchor()
//realign positions in reverse order to anchorposition
{
	float rindex = mPositions.size() - 1.f;
	for (std::list<Vec3f>::reverse_iterator rit = mPositions.rbegin(); 
		rit != mPositions.rend(); rit++, rindex--)
	{
		Vec3f& loc = *rit;

		loc += rindex / mPositions.size() * (mAnchorPosition - loc );
	}
}