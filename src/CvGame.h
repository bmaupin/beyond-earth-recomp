#pragma once

class CvRandom;
class CvGame
{
public:
	int getElapsedGameTurns() const;
	CvRandom& getMapRand();
	// TODO: CvGame (remaining members).
};