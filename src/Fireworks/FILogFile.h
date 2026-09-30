#pragma once

class FILogFile
{
public:
	virtual void Msg(const char* format, ...) = 0;

protected:
	FILogFile() {}
	virtual ~FILogFile() = 0;
};

class FILogFileMgr
{
public:
	virtual ~FILogFileMgr() = 0;
	static FILogFileMgr& GetInstance();
	static FILogFileMgr* PeekInstance();

	virtual void EnableLogging() = 0;
	virtual void DisableLogging() = 0;
	virtual void SetLogDirectory(const char* szDirectory) = 0;
	virtual FILogFile* GetLog(const wchar_t* wszFileName, unsigned int uiFlags, const char* szTitleString = 0) = 0;
	virtual FILogFile* GetLog(const char* szFileName, unsigned int uiFlags, const char* szTitleString = 0) = 0;
};

#define LOGFILEMGR FILogFileMgr::GetInstance()
