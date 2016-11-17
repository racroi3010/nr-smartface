#ifndef AN_TYPE_15_RECORD_HPP_INCLUDED
#define AN_TYPE_15_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANFPImageAsciiBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType15Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_15_RECORD_FIELD_LEN
#undef AN_TYPE_15_RECORD_FIELD_IDC
#undef AN_TYPE_15_RECORD_FIELD_IMP
#undef AN_TYPE_15_RECORD_FIELD_SRC
#undef AN_TYPE_15_RECORD_FIELD_PCD
#undef AN_TYPE_15_RECORD_FIELD_HLL
#undef AN_TYPE_15_RECORD_FIELD_VLL
#undef AN_TYPE_15_RECORD_FIELD_SLC
#undef AN_TYPE_15_RECORD_FIELD_HPS
#undef AN_TYPE_15_RECORD_FIELD_VPS
#undef AN_TYPE_15_RECORD_FIELD_CGA
#undef AN_TYPE_15_RECORD_FIELD_BPX
#undef AN_TYPE_15_RECORD_FIELD_PLP
#undef AN_TYPE_15_RECORD_FIELD_SHPS
#undef AN_TYPE_15_RECORD_FIELD_SVPS
#undef AN_TYPE_15_RECORD_FIELD_COM
#undef AN_TYPE_15_RECORD_FIELD_PQM
#undef AN_TYPE_15_RECORD_FIELD_DMM

#undef AN_TYPE_15_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_15_RECORD_FIELD_UDF_TO

#undef AN_TYPE_15_RECORD_FIELD_DATA

#undef AN_TYPE_15_RECORD_MAX_QUALITY_METRIC_COUNT

const NInt AN_TYPE_15_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_15_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;
const NInt AN_TYPE_15_RECORD_FIELD_IMP = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_IMP;
const NInt AN_TYPE_15_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_15_RECORD_FIELD_PCD = AN_ASCII_BINARY_RECORD_FIELD_DAT;
const NInt AN_TYPE_15_RECORD_FIELD_HLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_15_RECORD_FIELD_VLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_15_RECORD_FIELD_SLC = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC;
const NInt AN_TYPE_15_RECORD_FIELD_HPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS;
const NInt AN_TYPE_15_RECORD_FIELD_VPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS;
const NInt AN_TYPE_15_RECORD_FIELD_CGA = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA;
const NInt AN_TYPE_15_RECORD_FIELD_BPX = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX;
const NInt AN_TYPE_15_RECORD_FIELD_PLP = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FGP;
const NInt AN_TYPE_15_RECORD_FIELD_SHPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS;
const NInt AN_TYPE_15_RECORD_FIELD_SVPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS;
const NInt AN_TYPE_15_RECORD_FIELD_COM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM;
const NInt AN_TYPE_15_RECORD_FIELD_PQM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM;
const NInt AN_TYPE_15_RECORD_FIELD_DMM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM;

const NInt AN_TYPE_15_RECORD_FIELD_UDF_FROM = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_15_RECORD_FIELD_UDF_TO = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO;

const NInt AN_TYPE_15_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_15_RECORD_MAX_QUALITY_METRIC_COUNT = 4;

class ANType15Record : public ANFPImageAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType15Record, ANFPImageAsciiBinaryRecord)

private:
	static HANType15Record Create(NVersion version, NInt idc, NUInt flags)
	{
		HANType15Record handle;
		NCheck(ANType15RecordCreate(version.GetValue(), idc, flags, &handle));
		return handle;
	}

	static HANType15Record Create(NVersion version, NInt idc, const NStringWrapper & src, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, const ::Neurotec::Images::NImage & image, NUInt flags)
	{

		HANType15Record handle;
		NCheck(ANType15RecordCreateFromNImageN(version.GetValue(), idc, src.GetHandle(), slc, cga, image.GetHandle(), flags, &handle));
		return handle;
	}

public:
	explicit ANType15Record(NVersion version, NInt idc, NUInt flags = 0)
		: ANFPImageAsciiBinaryRecord(Create(version, idc, flags), true)
	{
	}

	ANType15Record(NVersion version, NInt idc, const NStringWrapper & src, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, const ::Neurotec::Images::NImage & image, NUInt flags = 0)
		: ANFPImageAsciiBinaryRecord(Create(version, idc, src, slc, cga, image, flags), true)
	{
	}
};
}}}

#endif // !AN_TYPE_15_RECORD_HPP_INCLUDED
