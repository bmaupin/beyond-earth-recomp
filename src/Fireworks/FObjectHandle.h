#pragma once

// TODO(Phase1): remaining SDK notification and handle operations.
// Native pointer access is inline; destruction retains its external ABI entry.
template<class PointingTo>
class FObjectHandle
{
public:
	FObjectHandle();
	~FObjectHandle();
	PointingTo* pointer() { return m_target; }
	PointingTo* pointer() const { return m_target; }
private:
	PointingTo* m_target;
	bool m_ignoreDestruction;
};
