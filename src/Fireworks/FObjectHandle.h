#pragma once

// SDK declaration; notification and pointer operations are not yet reconstructed.
template<class PointingTo>
class FObjectHandle
{
public:
	FObjectHandle();
	~FObjectHandle();
private:
	PointingTo* m_target;
	bool m_ignoreDestruction;
};
