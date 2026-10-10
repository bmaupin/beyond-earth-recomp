#ifndef FCRC_H
#define FCRC_H
#pragma once

#define CRC_INIT ((unsigned int) ~0)

class FCRC
{
public:
	FCRC(unsigned int polynomial = 0xEDB88320);
	~FCRC();
	unsigned int Calc(const void* pBuf, int nLen, unsigned int crc = CRC_INIT) const;
	// TODO: FCRC (remaining SDK methods).

private:
	unsigned int m_table[256];
	unsigned int m_polynomial;
	unsigned int m_magic;

	void InitTable(unsigned int polynomial);
	FCRC(const FCRC& obj);
	FCRC& operator=(const FCRC& obj);
};

extern FCRC g_CRC32;

#endif // FCRC_H
