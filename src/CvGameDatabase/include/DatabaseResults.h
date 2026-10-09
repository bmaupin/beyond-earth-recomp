#pragma once

#include "Database.h"
#include "ASL/HashMap.h"

namespace Database
{
	// Partial SDK declaration with Beyond Earth's ASL column-position map.
	class Results
	{
	public:
		Results(const char* szColumns = NULL);
		virtual ~Results();
		virtual const char* GetColumns() const;
		bool Step();
		bool Reset();
		bool Bind(int idx, const char* szValue, bool bMakeCopy = true);
		int GetInt(int iColumn);
		void* operator new(size_t tSize);
		void operator delete(void* pMem);

	private:
		Command m_Command;
		const char* m_szColumns;
		bool m_bSingleQuery;
		ASL::StdLib::HashMap::hash_map<std::string, int> m_hshColumnPositions;
		// TODO: Results (remaining SDK methods).
	};
}
