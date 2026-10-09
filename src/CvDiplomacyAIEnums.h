#pragma once

enum PeaceTreatyTypes
{
    NO_PEACE_TREATY_TYPE = -1,

    // WARNING: the order of these values is very important, do not change unless you know what you're doing!
    PEACE_TREATY_WHITE_PEACE,
    PEACE_TREATY_ARMISTICE,
	PEACE_TREATY_SETTLEMENT,
	PEACE_TREATY_BACKDOWN,
	PEACE_TREATY_SUBMISSION,
    PEACE_TREATY_SURRENDER,
	PEACE_TREATY_CESSION,
    PEACE_TREATY_CAPITULATION,
    PEACE_TREATY_UNCONDITIONAL_SURRENDER,
    // WARNING: the order of these values is very important, do not change unless you know what you're doing!

    NUM_PEACE_TREATY_TYPES,
};

// TODO: Remaining diplomacy AI enums.
