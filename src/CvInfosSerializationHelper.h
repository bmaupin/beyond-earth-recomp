#pragma once

namespace CvInfosSerializationHelper
{
int ReadHashed(FDataStream& kStream, bool* bValid = NULL);
bool WriteHashed(FDataStream& kStream, const CvBaseInfo* pkInfo);
bool WriteHashed(FDataStream& kStream, PolicyTypes ePolicy);

template<typename TData>
bool ReadAndRemapDataArray(FDataStream& kStream, int iSavedSize, TData* paArray, int iArraySize, const int* paIDs);

template<typename TData>
void ReadHashedDataArray(FDataStream& kStream, TData* paArray, int iArraySize);

template<typename TType, typename TData>
void WriteHashedDataArray(FDataStream& kStream, TData* paArray, unsigned int uiArraySize);
}
