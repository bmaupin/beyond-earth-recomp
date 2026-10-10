#pragma once

namespace fastdelegate
{
	template<class Param1, class Param2, class RetType> class FastDelegate2
	{
		class GenericClass;
		typedef RetType (GenericClass::*MemberFunction)(Param1, Param2);
		GenericClass* m_pObject;
		MemberFunction m_pFunction;
	public:
		FastDelegate2() : m_pObject(0), m_pFunction(0) {}
		template<class T> FastDelegate2(T* object, RetType (T::*function)(Param1, Param2))
			: m_pObject(reinterpret_cast<GenericClass*>(object)), m_pFunction(reinterpret_cast<MemberFunction>(function)) {}
		RetType operator()(Param1 first, Param2 second) const
		{
			return (m_pObject->*m_pFunction)(first, second);
		}
	};
}