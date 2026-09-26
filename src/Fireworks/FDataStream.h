// Minimal interface required by CvGameCoreEnumSerialization.cpp.
// Expand this declaration only when a compiled source file needs more of the
// original FireWorks API.
#pragma once

class FDataStream
{
public:
	template <typename T>
	FDataStream& operator<<(const T& value)
	{
		Write(value);
		return *this;
	}

	template <typename T>
	FDataStream& operator>>(T& value)
	{
		Read(value);
		return *this;
	}

protected:
	void Write(const int& value);
	void Read(int& value);
};
