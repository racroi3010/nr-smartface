#ifndef N_PROCESSOR_INFO_H_INCLUDED
#define N_PROCESSOR_INFO_H_INCLUDED

#include <Core/NObject.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum NProcessorVendor_
{
	npvUnknown = 0,
	npvAmd = 1,
	npvCentaur = 2,
	npvCyrix = 3,
	npvIntel = 4,
	npvNationalSemiconductor = 5,
	npvNexGen = 6,
	npvRiseTechnology = 7,
	npvSiS = 8,
	npvTransmeta = 9,
	npvUmc = 10,
	npvVia = 11
} NProcessorVendor;

N_DECLARE_TYPE(NProcessorVendor)

N_DECLARE_STATIC_OBJECT_TYPE(NProcessorInfo)

NResult N_API NProcessorInfoGetCount(NInt * pValue);

NResult N_API NProcessorInfoGetVendorNameN(HNString * phValue);
NResult N_API NProcessorInfoGetVendor(NProcessorVendor * pValue);
NResult N_API NProcessorInfoGetModelInfo(NInt * pFamily, NInt * pModel, NInt * pStepping);
NResult N_API NProcessorInfoGetModelNameN(HNString * phValue);

NResult N_API NProcessorInfoIsMmxSupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIs3DNowSupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsSseSupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsSse2SupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsSse3SupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsSsse3SupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsLZCntSupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsPopCntSupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsSse41SupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsSse42SupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsSse4aSupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsSse5SupportedEx(NBool * pValue);
NResult N_API NProcessorInfoIsNeonSupported(NBool * pValue);

#ifdef N_CPP
}
#endif

#endif // !N_PROCESSOR_INFO_H_INCLUDED
