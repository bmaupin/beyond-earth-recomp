#pragma once

// SDK declaration; notification and pointer operations are not yet reconstructed.
template<class PointingTo>
class FObjectHandle
{
public:
	FObjectHandle();
	~FObjectHandle();
	PointingTo* pointer() const;
private:
	PointingTo* m_target;
	bool m_ignoreDestruction;
};
