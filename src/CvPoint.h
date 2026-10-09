#pragma once

// Beyond Earth replaces the SDK's fixed-float point with a template.
template<class T> class CvPoint3
{
	T m_x;
	T m_y;
	T m_z;
	// TODO: CvPoint3 (constructors and operators).
};
typedef CvPoint3<float> CvPoint3f;
