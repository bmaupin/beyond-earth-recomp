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
	void Read(unsigned int& value);
};

//----------------------------------------------------------------------
// Support a bunch of legacy code that passes raw pointer data, arrays with magic number counts
// and dynamically allocated arrays. These should probably be encapsulated in containers
// for safety and manageability (std::vector, for example)
//----------------------------------------------------------------------
template<typename ValueType>
class ArrayWrapper
{
public:
	ArrayWrapper(int count, ValueType * values)
		: m_values(values), m_count(count) {}

	ValueType * getArray()
	{
		return m_values;
	}
	const ValueType * getArray() const
	{
		return m_values;
	}

	int getCount() const
	{
		return m_count;
	}

private:
	// disabled, this wrapper does not belong in containers
	// or allow copy construction
	ArrayWrapper();
	ArrayWrapper(const ArrayWrapper &);
	ArrayWrapper & operator=(const ArrayWrapper &);

	ValueType * m_values;
	int         m_count;
};

//----------------------------------------------------------------------
// Stream operators for array wrapper classes
//----------------------------------------------------------------------
template<typename ValueType>
FDataStream & operator<<(FDataStream & saveTo, const ArrayWrapper<ValueType> & v)
{
	int i = 0;
	int count = v.getCount();
	const ValueType * values = v.getArray();
	for(i = 0; i < count; ++i)
	{
		saveTo << values[i];
	}
	return saveTo;
}

template<typename ValueType>
FDataStream & operator>>(FDataStream & loadFrom, ArrayWrapper<ValueType> & v)
{
	int i = 0;
	int count = v.getCount();
	ValueType * values = v.getArray();
	for(i = 0; i < count; ++i)
	{
		loadFrom >> values[i];
	}
	return loadFrom;
}

template<typename ValueType>
FDataStream & operator>>(FDataStream & loadFrom, const ArrayWrapper<ValueType> & v)
{
	int i = 0;
	int count = v.getCount();
	ValueType * values = const_cast<ValueType *>(v.getArray());
	for(i = 0; i < count; ++i)
	{
		loadFrom >> values[i];
	}
	return loadFrom;
}
