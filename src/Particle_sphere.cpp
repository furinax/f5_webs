#include "Particle_sphere.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

Particle_sphere::Particle_sphere(const Vec2f& pos){
	mAnchorPosition = Vec3f(getWindowWidth() * .5f, getWindowHeight() *.5f, 0);

	mRadiusAnchor = 200.f; //sphere radius
	int slices = 36;
	for (float heightIndex = 0; heightIndex < slices; heightIndex++)
	{
		for (float sliceIndex = 0; sliceIndex < slices; sliceIndex++)
		{
			 Vec3f temp = Vec3f(
				 mRadiusAnchor * sin(heightIndex / 36.f * M_PI) * cos(sliceIndex / 36.f * 2.f * M_PI),
				(heightIndex - slices/2.f ) * 5.f,
				mRadiusAnchor*sin(sliceIndex / 36.f * 2.f * M_PI)
				) ;
			 temp.rotateY(getElapsedSeconds());
			 temp += mAnchorPosition;
			 addPosition(temp);
		}
	}

	mRadius = 200.f;

	mColor = ci::Color(0.f, 1.f, 1.f);
	mOverlayColor = Color::white();

	//mVel = Vec3f(0, 30.f, 50 * sin(getElapsedSeconds())); //this is a base, we will rotate it based on mAnchorPosition
	mLifespan = 1;

}

void Particle_sphere::update(const ci::Vec2f pos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mAgeMap = 1.0f - (mAge / (float)mLifespan);

	mVel += mAcc;
	mVel *= mDrag;

	for (auto iter = mPositions.begin(); iter != mPositions.end(); iter++)
	{
		Vec3f &currentPos = *iter;
	}
}