// Reconstructed from Beyond Earth's i386 DWARF. Only runtime structures needed
// by the inline Lua API are included; this is not an implementation of the VM.
#pragma once
#include <stddef.h>
#include <setjmp.h>

struct lua_State;
struct lua_Debug;
struct hksInstruction;
typedef int (*lua_CFunction)(lua_State*);
typedef void (*lua_Hook)(lua_State*, lua_Debug*);
typedef void* (*lua_Alloc)(void*, void*, size_t, size_t);
typedef ptrdiff_t lua_Integer;
typedef unsigned int hksSize;
typedef unsigned int hksUint32;
typedef int hksInt32;
typedef int hksBool;
typedef double HksNumber;
typedef unsigned long long HksNativeValueAsInt;

enum HksObjectType
{
	TANY = -2, TNONE, TNIL, TBOOLEAN, TLIGHTUSERDATA, TNUMBER, TSTRING,
	TTABLE, TFUNCTION, TUSERDATA, TTHREAD, TIFUNCTION, TCFUNCTION, TUI64,
	TSTRUCT, NUM_TYPE_OBJECTS = 14
};
enum HksError
{
	HKS_NO_ERROR = 0, LUA_ERRSYNTAX = -4, LUA_ERRFILE = -5,
	LUA_ERRRUN = -100, LUA_ERRMEM = -200, LUA_ERRERR = -300,
	HKS_THROWING_ERROR = -500, HKS_GC_YIELD = 1
};
enum HksBytecodeSharingMode
{
	HKS_BYTECODE_SHARING_OFF, HKS_BYTECODE_SHARING_ON, HKS_BYTECODE_SHARING_SECURE
};

namespace hks
{
	struct cclosure;
	struct HksClosure;
	struct UserData;
	struct HashTable;
	class StructInst;
	class InternString;
	class UpValue;
	struct CallSite;
	struct HksGlobal;
	typedef CallSite* ErrorHandler;

	class GenericChunkHeader
	{
	public:
		hksSize m_flags;
	};
	class ChunkHeader : public GenericChunkHeader
	{
	public:
		ChunkHeader* m_next;
	};
	class CallStack
	{
	public:
		struct ActivationRecord;
		ActivationRecord* m_records;
		ActivationRecord* m_lastrecord;
		ActivationRecord* m_current;
		const hksInstruction* m_current_lua_pc;
		const hksInstruction* m_hook_return_addr;
		hksInt32 m_hook_level;
		void growApiStack(lua_State* L, int numSlots);
		// TODO: CallStack (remaining runtime methods).
	};
}

union HksValue
{
	hks::cclosure* cClosure;
	hks::HksClosure* closure;
	hks::UserData* userData;
	hks::HashTable* table;
	hks::StructInst* tstruct;
	hks::InternString* str;
	lua_State* thread;
	void* ptr;
	HksNumber number;
	HksNativeValueAsInt native;
	hksInt32 boolean;
};
struct HksObject
{
	hksUint32 t;
	HksValue v;
};

namespace hks
{
	struct ApiStack
	{
		HksObject* top;
		HksObject* base;
		HksObject* alloc_top;
		HksObject* bottom;
	};
	struct DebugHook
	{
		lua_Hook m_callback;
		hksInt32 m_mask, m_count, m_counter;
		bool m_inuse;
		const hksInstruction* m_prevPC;
	};
	struct cclosure : public ChunkHeader
	{
		lua_CFunction m_function;
		HashTable* m_env;
		short m_numUpvalues, m_flags;
		InternString* m_name;
		HksObject m_upvalues[1];
	};
	class ChunkList
	{
	public:
		ChunkHeader m_head;
	};
	class MemoryManager
	{
	public:
		enum ChunkColor { WHITE, BLACK };
		lua_Alloc m_allocator;
		void* m_allocatorUd;
		ChunkColor m_chunkColor;
		hksSize m_used, m_highwatermark;
		ChunkList m_allocationList, m_sweepList;
		ChunkHeader* m_lastKeptChunk;
		lua_State* m_state;
	};
	typedef int HksGcCost;
	struct HksGcWeights
	{
		HksGcCost m_removeString, m_finalizeUserdataNoMM, m_finalizeUserdataGcMM;
		HksGcCost m_cleanCoroutine, m_removeWeak, m_markObject;
		HksGcCost m_traverseString, m_traverseUserdata, m_traverseCoroutine;
		HksGcCost m_traverseWeakTable, m_freeChunk, m_sweepTraverse;
	};
	union ResumeData_Entry;
	struct WeakStack_Entry;
	class GarbageCollector
	{
	public:
		HksGcCost m_target, m_stepsLeft, m_stepLimit;
		HksGcWeights m_costs;
		HksGcCost m_unit;
		jmp_buf* m_jumpPoint;
		lua_State* m_mainState;
		lua_State* m_finalizerState;
		MemoryManager* m_memory;
		hksInt32 m_phase;
		struct ResumeStack { ResumeData_Entry* m_storage; hksInt32 m_numEntries; hksUint32 m_numAllocated; } m_resumeStack;
		struct GreyStack { HksObject* m_storage; hksSize m_numEntries, m_numAllocated; } m_greyStack;
		struct RemarkStack { HashTable** m_storage; hksSize m_numAllocated, m_numEntries; } m_remarkStack;
		struct WeakStack { WeakStack_Entry* m_storage; hksInt32 m_numEntries; hksUint32 m_numAllocated; } m_weakStack;
		hksBool m_finalizing;
		HksObject m_safeTableValue;
		lua_State* m_startOfStateStackList;
		lua_State* m_endOfStateStackList;
		lua_State* m_currentState;
		HksObject m_safeValue;
		void* m_compiler;
		void* m_bytecodeReader;
		void* m_bytecodeWriter;
		hksInt32 m_pauseMultiplier;
		HksGcCost m_stepMultiplier;
		bool m_stopped;
		lua_CFunction m_gcPolicy;
		hksSize m_pauseTriggerMemoryUsage;
		hksInt32 m_stepTriggerCountdown;
		hksUint32 m_stringTableIndex, m_stringTableSize;
		UserData* m_lastBlackUD;
		UserData* m_activeUD;
	};
	class StringPinner;
	class StringTable
	{
	public:
		InternString** m_data;
		hksUint32 m_count, m_mask;
		StringPinner* m_pinnedStrings;
	};
	struct HksGlobal
	{
		MemoryManager m_memory;
		GarbageCollector m_collector;
		StringTable m_stringTable;
		HksBytecodeSharingMode m_bytecodeSharingMode;
		hksUint32 m_tableVersionInitializer;
		HksObject m_registry;
		// TODO: HksGlobal (remaining real members after m_registry).
	};
}

struct lua_State : public hks::ChunkHeader
{
	hks::HksGlobal* m_global;
	hks::CallStack m_callStack;
	hks::ApiStack m_apistack;
	hks::UpValue* pending;
	HksObject globals;
	HksObject m_cEnv;
	hks::ErrorHandler m_callsites;
	hksInt32 m_numberOfCCalls;
	void* m_context;
	hks::InternString* m_name;
	lua_State* m_next;
	lua_State* m_nextStateStack;
	enum Status { NEW = 1, RUNNING, YIELDED, DEAD_ERROR } m_status;
	HksError m_error;
	hks::DebugHook m_debugHook;
};

static_assert(sizeof(HksObject) == 12, "Beyond Earth i386 HksObject layout");
static_assert(sizeof(lua_State) == 136, "Beyond Earth i386 lua_State layout");
static_assert(sizeof(hks::MemoryManager) == 44, "HKS memory manager layout");
static_assert(sizeof(hks::GarbageCollector) == 224, "HKS collector layout");
static_assert(offsetof(hks::HksGlobal, m_registry) == 292, "HKS registry offset");