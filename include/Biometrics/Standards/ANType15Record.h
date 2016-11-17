#ifndef AN_TYPE_15_RECORD_H_INCLUDED
#define AN_TYPE_15_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANFPImageAsciiBinaryRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType15Record, ANFPImageAsciiBinaryRecord)

#define AN_TYPE_15_RECORD_FIELD_LEN  AN_RECORD_FIELD_LEN
#define AN_TYPE_15_RECORD_FIELD_IDC  AN_RECORD_FIELD_IDC
#define AN_TYPE_15_RECORD_FIELD_IMP  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_IMP
#define AN_TYPE_15_RECORD_FIELD_SRC  AN_ASCII_BINARY_RECORD_FIELD_SRC
#define AN_TYPE_15_RECORD_FIELD_PCD  AN_ASCII_BINARY_RECORD_FIELD_DAT
#define AN_TYPE_15_RECORD_FIELD_HLL  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL
#define AN_TYPE_15_RECORD_FIELD_VLL  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL
#define AN_TYPE_15_RECORD_FIELD_SLC  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC
#define AN_TYPE_15_RECORD_FIELD_HPS  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS
#define AN_TYPE_15_RECORD_FIELD_VPS  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS
#define AN_TYPE_15_RECORD_FIELD_CGA  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA
#define AN_TYPE_15_RECORD_FIELD_BPX  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX
#define AN_TYPE_15_RECORD_FIELD_PLP  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FGP
#define AN_TYPE_15_RECORD_FIELD_SHPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS
#define AN_TYPE_15_RECORD_FIELD_SVPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS
#define AN_TYPE_15_RECORD_FIELD_COM  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM
#define AN_TYPE_15_RECORD_FIELD_PQM  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM
#define AN_TYPE_15_RECORD_FIELD_DMM  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM

#define AN_TYPE_15_RECORD_FIELD_UDF_FROM AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM
#define AN_TYPE_15_RECORD_FIELD_UDF_TO   AN_ASCII_BINARY_RECORD_FIELD_UDF_TO

#define AN_TYPE_15_RECORD_FIELD_DATA AN_RECORD_FIELD_DATA

#define AN_TYPE_15_RECORD_MAX_QUALITY_METRIC_COUNT 4

NResult N_API ANType15RecordCreate(NVersion_ version, NInt idc, NUInt flags, HANType15Record * phRecord);

NResult N_API ANType15RecordCreateFromNImageN(NVersion_ version, NInt idc, HNString hSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, NUInt flags, HANType15Record * phRecord);
#ifndef N_NO_ANSI_FUNC
NResult ANType15RecordCreateFromNImageA(NVersion_ version, NInt idc, const NAChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, NUInt flags, HANType15Record * phRecord);
#endif
#ifndef N_NO_UNICODE
NResult ANType15RecordCreateFromNImageW(NVersion_ version, NInt idc, const NWChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, NUInt flags, HANType15Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
NResult ANType15RecordCreateFromNImage(NVersion_ version, NInt idc, const NChar * szSrc, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, HNImage hImage, NUInt flags, HANType15Record * phRecord);
#endif
#define ANType15RecordCreateFromNImage N_FUNC_AW(ANType15RecordCreateFromNImage)

#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_15_RECORD_H_INCLUDED
