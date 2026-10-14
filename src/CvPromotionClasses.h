#pragma once

#ifndef CIV5_PROMOTION_CLASSES_H
#define CIV5_PROMOTION_CLASSES_H

class CvPromotionEntry: public CvHotKeyInfo
{
public:
	CvPromotionEntry(void);
	~CvPromotionEntry(void);

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvPromotionEntry (remaining SDK methods and Beyond Earth members).
};

#endif // CIV5_PROMOTION_CLASSES_H
