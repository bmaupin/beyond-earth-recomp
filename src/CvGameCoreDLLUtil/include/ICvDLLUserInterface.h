#pragma once

#include "CvDllInterfaces.h"

class CvDLLInterfaceIFaceBase;

// The target calls setDirty through vtable slot 67 (byte offset 0x10c), after
// ICvUnknown's two slots. The preceding entries preserve that native ABI.
class ICvUserInterface1 : public ICvUnknown
{
public:
	virtual void Reserved0() = 0;
	virtual void Reserved1() = 0;
	virtual void Reserved2() = 0;
	virtual void Reserved3() = 0;
	virtual void Reserved4() = 0;
	virtual void Reserved5() = 0;
	virtual void Reserved6() = 0;
	virtual void Reserved7() = 0;
	virtual void Reserved8() = 0;
	virtual void Reserved9() = 0;
	virtual void Reserved10() = 0;
	virtual void Reserved11() = 0;
	virtual void Reserved12() = 0;
	virtual void Reserved13() = 0;
	virtual void Reserved14() = 0;
	virtual void Reserved15() = 0;
	virtual void Reserved16() = 0;
	virtual void Reserved17() = 0;
	virtual void Reserved18() = 0;
	virtual void Reserved19() = 0;
	virtual void Reserved20() = 0;
	virtual void Reserved21() = 0;
	virtual void Reserved22() = 0;
	virtual void Reserved23() = 0;
	virtual void Reserved24() = 0;
	virtual void Reserved25() = 0;
	virtual void Reserved26() = 0;
	virtual void Reserved27() = 0;
	virtual void Reserved28() = 0;
	virtual void Reserved29() = 0;
	virtual void Reserved30() = 0;
	virtual void Reserved31() = 0;
	virtual void Reserved32() = 0;
	virtual void Reserved33() = 0;
	virtual void Reserved34() = 0;
	virtual void Reserved35() = 0;
	virtual void Reserved36() = 0;
	virtual void Reserved37() = 0;
	virtual void Reserved38() = 0;
	virtual void Reserved39() = 0;
	virtual void Reserved40() = 0;
	virtual void Reserved41() = 0;
	virtual void Reserved42() = 0;
	virtual void Reserved43() = 0;
	virtual void Reserved44() = 0;
	virtual void Reserved45() = 0;
	virtual void Reserved46() = 0;
	virtual void Reserved47() = 0;
	virtual void Reserved48() = 0;
	virtual void Reserved49() = 0;
	virtual void Reserved50() = 0;
	virtual void Reserved51() = 0;
	virtual void Reserved52() = 0;
	virtual void Reserved53() = 0;
	virtual void Reserved54() = 0;
	virtual void Reserved55() = 0;
	virtual void Reserved56() = 0;
	virtual void Reserved57() = 0;
	virtual void Reserved58() = 0;
	virtual void Reserved59() = 0;
	virtual void Reserved60() = 0;
	virtual void Reserved61() = 0;
	virtual void Reserved62() = 0;
	virtual void Reserved63() = 0;
	virtual void Reserved64() = 0;
	virtual void setDirty(InterfaceDirtyBits eDirtyItem, bool bNewValue) = 0;
};
