#include "CvGameCoreDLLPCH.h"
#include "CvFractal.h"
#include "CvRandom.h"

#include <algorithm>
#include <climits>

namespace
{
	const int kPrecision = 1000;

	// TODO: Phase1 Clamp: inlined helper; verify instructions at each caller, not a separately matched target export.
	int Clamp(int value, int low, int high)
	{
		return std::max(low, std::min(value, high));
	}

	// TODO: Phase1 HexDistance: reconstructed inline helper; caller equality and Civ5 changed/new count unverified.
	int HexDistance(int dx, int dy)
	{
		const int adx = abs(dx);
		const int ady = abs(dy);
		return (dx >= 0) == (dy >= 0) ? adx + ady : std::max(adx, ady);
	}

	// TODO: Phase1 HexX: reconstructed inline helper; verify coordinate conversion at each caller.
	int HexX(int x, int y)
	{
		return x - (y >= 0 ? y >> 1 : (y - 1) / 2);
	}

	struct RidgeSeed
	{
		int x;
		int y;
		int weakness;
		int direction;
		int directionStrength;
	};
}

// TODO: Phase1 CvFractal::CvFractal(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvFractal::CvFractal(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
CvFractal::CvFractal()
{
	m_iFracXExp = -1;
	m_iFracYExp = -1;
	m_iXs = -1;
	m_iYs = -1;
	m_iFlags = 0;
	m_iFracX = -1;
	m_iFracY = -1;
}

// TODO: Phase1 CvFractal::~CvFractal(): MISMATCH; Non-padding instruction count: BE 15, object 5; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvFractal::~CvFractal(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvFractal::~CvFractal(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
CvFractal::~CvFractal()
{
	uninit();
}

void CvFractal::uninit()
{
}

// TODO: Phase1 CvFractal::reset(): MISMATCH; Relocation-free operand/instruction difference; Civ5 changed/new instruction count unverified.
void CvFractal::reset()
{
	uninit();
	m_iXs = -1;
	m_iYs = -1;
	m_iFlags = 0;
	m_iFracX = -1;
	m_iFracY = -1;
	m_iFracXExp = -1;
	m_iFracYExp = -1;
}

// TODO: Phase1 CvFractal::fracInit(int, int, int, CvRandom&, int, CvFractal*, int, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvFractal::fracInit(int iNewXs, int iNewYs, int iGrain, CvRandom& random, int iFlags, CvFractal* pRifts, int iFracXExp, int iFracYExp)
{
	fracInitInternal(iNewXs, iNewYs, iGrain, random, NULL, -1, iFlags, pRifts, iFracXExp, iFracYExp);
}

// TODO: Phase1 CvFractal::fracInitHinted(int, int, int, CvRandom&, unsigned char*, int, int, CvFractal*, int, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvFractal::fracInitHinted(int iNewXs, int iNewYs, int iGrain, CvRandom& random, byte* pbyHints, int iHintsLength, int iFlags, CvFractal* pRifts, int iFracXExp, int iFracYExp)
{
	fracInitInternal(iNewXs, iNewYs, iGrain, random, pbyHints, iHintsLength, iFlags & ~FRAC_POLAR, pRifts, iFracXExp, iFracYExp);
}

// TODO: Phase1 CvFractal::fracInitInternal(int, int, int, CvRandom&, unsigned char*, int, int, CvFractal*, int, int): MISMATCH; Non-padding instruction count: BE 682, object 571; Civ5 changed/new instruction count unverified.
void CvFractal::fracInitInternal(int iNewXs, int iNewYs, int iGrain, CvRandom& random, byte* pbyHints, int iHintsLength, int iFlags, CvFractal* pRifts, int iFracXExp, int iFracYExp)
{
	CvAssert(iNewXs > 0 && iNewXs < FRACTAL_MAX_DIMS);
	CvAssert(iNewYs > 0 && iNewYs < FRACTAL_MAX_DIMS);

	reset();
	m_iFracXExp = iFracXExp < 0 ? DEFAULT_FRAC_X_EXP : iFracXExp;
	m_iFracYExp = iFracYExp < 0 ? DEFAULT_FRAC_Y_EXP : iFracYExp;
	m_iFracX = 1 << m_iFracXExp;
	m_iFracY = 1 << m_iFracYExp;
	m_iXs = iNewXs;
	m_iYs = iNewYs;
	m_iFlags = iFlags;
	m_iXInc = m_iFracX * kPrecision / m_iXs;
	m_iYInc = m_iFracY * kPrecision / m_iYs;

	for(int x = 0; x <= m_iFracX; ++x)
		for(int y = 0; y <= m_iFracY; ++y)
			m_aaiFrac[x][y] = 0;

	const int minExp = std::min(m_iFracXExp, m_iFracYExp);
	const int smooth = Clamp(minExp - iGrain, 0, minExp);
	const int hintWidth = (1 << (m_iFracXExp - smooth)) + ((m_iFlags & FRAC_WRAP_X) ? 0 : 1);
	const int hintHeight = (1 << (m_iFracYExp - smooth)) + ((m_iFlags & FRAC_WRAP_Y) ? 0 : 1);
	CvAssertMsg(!pbyHints || iHintsLength == hintWidth * hintHeight, "pbyHints is the wrong size!");

	for(int pass = smooth; pass >= 0; --pass)
	{
		const int step = 1 << pass;
		const int screen = (1 << (pass + 1)) - 1;

		if(m_iFlags & FRAC_WRAP_Y)
			for(int x = 0; x <= m_iFracX; ++x) m_aaiFrac[x][m_iFracY] = m_aaiFrac[x][0];
		else if(m_iFlags & FRAC_POLAR)
			for(int x = 0; x <= m_iFracX; ++x) m_aaiFrac[x][0] = m_aaiFrac[x][m_iFracY] = 0;

		if(m_iFlags & FRAC_WRAP_X)
			for(int y = 0; y <= m_iFracY; ++y) m_aaiFrac[m_iFracX][y] = m_aaiFrac[0][y];
		else if(m_iFlags & FRAC_POLAR)
			for(int y = 0; y <= m_iFracY; ++y) m_aaiFrac[0][y] = m_aaiFrac[m_iFracX][y] = 0;

		if(m_iFlags & FRAC_CENTER_RIFT)
		{
			if(m_iFlags & FRAC_WRAP_Y)
				for(int x = 0; x <= m_iFracX; ++x)
					for(int y = 0; y < m_iFracY / 6; ++y)
					{
						const int divisor = abs(m_iFracY / 12 - y) + 1;
						m_aaiFrac[x][y] /= divisor;
						m_aaiFrac[x][m_iFracY / 2 + y] /= divisor;
					}
			if(m_iFlags & FRAC_WRAP_X)
				for(int y = 0; y <= m_iFracY; ++y)
					for(int x = 0; x < m_iFracX / 6; ++x)
					{
						const int divisor = abs(m_iFracX / 12 - x) + 1;
						m_aaiFrac[x][y] /= divisor;
						m_aaiFrac[m_iFracX / 2 + x][y] /= divisor;
					}
		}

		const int xCount = (m_iFracX >> pass) + ((m_iFlags & FRAC_WRAP_X) ? 0 : 1);
		const int yCount = (m_iFracY >> pass) + ((m_iFlags & FRAC_WRAP_Y) ? 0 : 1);
		for(int x = 0; x < xCount; ++x)
			for(int y = 0; y < yCount; ++y)
			{
				const int px = x * step;
				const int py = y * step;
				if(pass == smooth)
				{
					m_aaiFrac[px][py] = pbyHints ? pbyHints[(y % hintHeight) * hintWidth + x % hintWidth] : random.get(256, "Fractal Gen");
					continue;
				}
				if((px & screen) == 0 && (py & screen) == 0)
					continue;

				int value;
				if((px & screen) && (py & screen))
				{
					value = (m_aaiFrac[px - step][py - step] + m_aaiFrac[px + step][py - step] + m_aaiFrac[px - step][py + step] + m_aaiFrac[px + step][py + step]) >> 2;
					value += random.get(1 << (8 - smooth + pass), "Fractal Gen 2") - (1 << (7 - smooth + pass));
				}
				else if(px & screen)
				{
					value = (m_aaiFrac[px - step][py] + m_aaiFrac[px + step][py]) >> 1;
					value += random.get(1 << (8 - smooth + pass), "Fractal Gen 3") - (1 << (7 - smooth + pass));
				}
				else
				{
					value = (m_aaiFrac[px][py - step] + m_aaiFrac[px][py + step]) >> 1;
					value += random.get(1 << (8 - smooth + pass), "Fractal Gen 4") - (1 << (7 - smooth + pass));
				}
				m_aaiFrac[px][py] = Clamp(value, 0, 255);
			}
	}

	if(pRifts) tectonicAction(pRifts);
	if(m_iFlags & FRAC_INVERT_HEIGHTS)
		for(int x = 0; x < m_iFracX; ++x)
			for(int y = 0; y < m_iFracY; ++y)
				m_aaiFrac[x][y] = 255 - m_aaiFrac[x][y];
}

// TODO: Phase1 CvFractal::getHeight(int, int): MISMATCH; Non-padding instruction count: BE 91, object 101; Civ5 changed/new instruction count unverified.
int CvFractal::getHeight(int x, int y)
{
	if(x < 0 || x >= m_iXs || y < 0 || y >= m_iYs) return 0;
	int lowX = std::min(m_iFracX - 1, m_iXInc * x / kPrecision);
	int lowY = std::min(m_iFracY - 1, m_iYInc * y / kPrecision);
	if(lowX < 0 || lowX > FRACTAL_MAX_DIMS || lowY < 0 || lowY > FRACTAL_MAX_DIMS) return 0;
	const int errX = m_iXInc * x - lowX * kPrecision;
	const int errY = m_iYInc * y - lowY * kPrecision;
	const int height = Clamp(((kPrecision - errX) * (kPrecision - errY) * m_aaiFrac[lowX][lowY] + errX * (kPrecision - errY) * m_aaiFrac[lowX + 1][lowY] + (kPrecision - errX) * errY * m_aaiFrac[lowX][lowY + 1] + errX * errY * m_aaiFrac[lowX + 1][lowY + 1]) / (kPrecision * kPrecision), 0, 255);
	return (m_iFlags & FRAC_PERCENT) ? height * 100 / 256 : height;
}

// TODO: Phase1 CvFractal::getHeightFromPercent(int): MISMATCH; Non-padding instruction count: BE 94, object 85; Civ5 changed/new instruction count unverified.
int CvFractal::getHeightFromPercent(int percent)
{
	percent = Clamp(percent, 0, 100);
	int low = 0;
	int high = 255;
	int estimate = 255 * percent / 100;
	while(estimate != low)
	{
		int below = 0;
		for(int x = 0; x < m_iFracX; ++x)
			for(int y = 0; y < m_iFracY; ++y)
				below += m_aaiFrac[x][y] < estimate;
		if(100 * below / (m_iFracX * m_iFracY) > percent) high = estimate;
		else low = estimate;
		estimate = (high + low) / 2;
	}
	return estimate;
}

// TODO: Phase1 CvFractal::tectonicAction(CvFractal*): MISMATCH; Mnemonic divergence at BE #10 mov, object #10 imul; Civ5 changed/new instruction count unverified.
void CvFractal::tectonicAction(CvFractal* pRifts)
{
	const int riftX = m_iFracX * 3 / 4;
	const int width = 16;
	for(int y = 0; y <= m_iFracY; ++y)
		for(int x = 0; x < width; ++x)
		{
			const int displacement = (pRifts->m_aaiFrac[riftX][y] - 128) * m_iFracX / 1024;
			const int right = yieldX(displacement + x);
			const int left = yieldX(displacement - x);
			m_aaiFrac[right][y] = m_aaiFrac[right][y] * x / width;
			m_aaiFrac[left][y] = m_aaiFrac[left][y] * x / width;
		}
	for(int y = 0; y <= m_iFracY; ++y) m_aaiFrac[m_iFracX][y] = m_aaiFrac[0][y];
}

int CvFractal::yieldX(int x)
{
	if(x < 0) return x + m_iFracX;
	if(x >= m_iFracX) return x - m_iFracX;
	return x;
}

// TODO: Phase1 CvFractal::ridgeBuilder(CvRandom&, int, int, int, int): MISMATCH; Non-padding instruction count: BE 306, object 272; Civ5 changed/new instruction count unverified.
void CvFractal::ridgeBuilder(CvRandom& random, int seedCount, int ridgeFlags, int ridgeBlend, int fractalBlend)
{
	seedCount = std::max(seedCount, 3);
	RidgeSeed seeds[256];
	for(int i = 0; i < seedCount; ++i)
	{
		RidgeSeed& seed = seeds[i];
		do
		{
			seed.y = random.get(m_iFracY, "Ridge Gen 1");
			seed.x = HexX(random.get(m_iFracX, "Ridge Gen 2"), seed.y);
			seed.weakness = std::max(0, static_cast<int>(random.get(7, "Ridge Gen 3")) - 3);
			seed.direction = random.get(6, "Ridge Gen 4");
			seed.directionStrength = std::max(0, static_cast<int>(random.get(8, "Ridge Gen 5")) - 4);
			bool tooClose = false;
			for(int j = 0; j < i; ++j)
				if(HexDistance(seed.x - seeds[j].x, seed.y - seeds[j].y) < 7) { tooClose = true; break; }
			if(!tooClose) break;
		} while(true);
	}

	for(int x = 0; x < m_iFracX; ++x)
		for(int y = 0; y < m_iFracY; ++y)
		{
			const int hexX = HexX(x, y);
			int nearest = INT_MAX;
			int next = INT_MAX;
			for(int i = 0; i < seedCount; ++i)
			{
				int distance = HexDistance(hexX - seeds[i].x, y - seeds[i].y);
				if(ridgeFlags)
				{
					distance += seeds[i].weakness + random.get(3, "Ridge Gen 8");
					const int dx = seeds[i].x - hexX;
					const int dy = seeds[i].y - y;
					static const double directions[6][2] =
					{
						{ 0.5, 0.866025 }, { 1.0, 0.0 }, { 0.5, -0.866025 },
						{ -0.5, -0.866025 }, { -1.0, 0.0 }, { -0.5, -0.866025 }
					};
					int direction = -1;
					double maximum = 0.0;
					for(int j = 0; j < 6; ++j)
					{
						const double dot = dx * directions[j][0] + dy * directions[j][1];
						if(dot > maximum) { maximum = dot; direction = j; }
					}
					if(direction == seeds[i].direction) distance -= seeds[i].directionStrength;
					else if(direction == (seeds[i].direction + 3) % 6) distance += seeds[i].directionStrength;
					distance = std::max(1, distance);
				}
				if(distance < nearest) { next = nearest; nearest = distance; }
				else if(distance < next) next = distance;
			}
			const int ridge = 255 * nearest / next;
			m_aaiFrac[x][y] = (ridge * ridgeBlend + m_aaiFrac[x][y] * fractalBlend) / std::max(1, ridgeBlend + fractalBlend);
		}
}
