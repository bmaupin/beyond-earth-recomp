#pragma once
#ifndef ICvDLLUtility_h
#define ICvDLLUtility_h

#include "CvDllInterfaces.h"

//
// abstract interface for utility functions used by DLL
// Copyright 2010 Firaxis Games
//
class ICvEngineScriptSystem1;
class CvDLLInterfaceIFaceBase;

// Supporting SDK interface prefix only. GetScriptSystem is at vtable + 0xc
// in both Civ 5 and Beyond Earth; the unused trailing methods are not copied.
// TODO: ICvEngineUtility1 (remaining methods).
class ICvEngineUtility1 : public ICvUnknown
{
public:
	//This method has been deprecated due to the interface not being versioned.
	//You should use GC.GetEngineUserInterface() instead to obtain a pointer to ICvUserInterface.
	virtual CvDLLInterfaceIFaceBase* getInterfaceIFace() = 0;

	virtual ICvEngineScriptSystem1* GetScriptSystem() = 0;
};

// Retain the SDK inheritance chain for the getDLLIFace() return type.
// These are partial declarations, not complete engine interfaces.
// TODO: ICvEngineUtility2 (additional methods).
class ICvEngineUtility2 : public ICvEngineUtility1
{
};

// TODO: ICvEngineUtility3 (additional methods).
class ICvEngineUtility3 : public ICvEngineUtility2
{
};

// TODO: ICvEngineUtility4 (additional methods; verify Beyond Earth version).
class ICvEngineUtility4 : public ICvEngineUtility3
{
};

#endif // ICvDLLUtility_h