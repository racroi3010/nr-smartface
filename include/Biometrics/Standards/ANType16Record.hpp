#ifndef AN_TYPE_16_RECORD_HPP_INCLUDED
#define AN_TYPE_16_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANImageAsciiBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType16Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_16_RECORD_FIELD_LEN
#undef AN_TYPE_16_RECORD_FIELD_IDC

#undef AN_TYPE_16_RECORD_FIELD_UDI

#undef AN_TYPE_16_RECORD_FIELD_SRC
#undef AN_TYPE_16_RECORD_FIELD_UTD
#undef AN_TYPE_16_RECORD_FIELD_HLL
#undef AN_TYPE_16_RECORD_FIELD_VLL
#undef AN_TYPE_16_RECORD_FIELD_SLC
#undef AN_TYPE_16_RECORD_FIELD_HPS
#undef AN_TYPE_16_RECORD_FIELD_VPS
#undef AN_TYPE_16_RECORD_FIELD_CGA
#undef AN_TYPE_16_RECORD_FIELD_BPX
#undef AN_TYPE_16_RECORD_FIELD_CSP
#undef AN_TYPE_16_RECORD_FIELD_SHPS
#undef AN_TYPE_16_RECORD_FIELD_SVPS
#undef AN_TYPE_16_RECORD_FIELD_COM
#undef AN_TYPE_16_RECORD_FIELD_UQS
#undef AN_TYPE_16_RECORD_FIELD_DMM

#undef AN_TYPE_16_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_16_RECORD_FIELD_UDF_TO

#undef AN_TYPE_16_RECORD_FIELD_DATA

#undef AN_TYPE_16_RECORD_MAX_USER_DEFINED_IMAGE_LENGTH

const NInt AN_TYPE_16_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_16_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_16_RECORD_FIELD_UDI = 3;

const NInt AN_TYPE_16_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_16_RECORD_FIELD_UTD = AN_ASCII_BINARY_RECORD_FIELD_DAT;
const NInt AN_TYPE_16_RECORD_FIELD_HLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_16_RECORD_FIELD_VLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_16_RECORD_FIELD_SLC = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC;
const NInt AN_TYPE_16_RECORD_FIELD_HPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS;
const NInt AN_TYPE_16_RECORD_FIELD_VPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS;
const NInt AN_TYPE_16_RECORD_FIELD_CGA = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA;
const NInt AN_TYPE_16_RECORD_FIELD_BPX = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX;
const NInt AN_TYPE_16_RECORD_FIELD_CSP = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CSP;
const NInt AN_TYPE_16_RECORD_FIELD_SHPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS;
const NInt AN_TYPE_16_RECORD_FIELD_SVPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS;
const NInt AN_TYPE_16_RECORD_FIELD_COM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM;
const NInt AN_TYPE_16_RECORD_FIELD_UQS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM;
const NInt AN_TYPE_16_RECORD_FIELD_DMM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM;

const NInt AN_TYPE_16_RECORD_FIELD_UDF_FROM = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_16_RECORD_FIELD_UDF_TO = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO;

const NInt AN_TYPE_16_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_16_RECORD_MAX_USER_DEFINED_IMAGE_LENGTH = 35;

class ANType16Record : public ANImageAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType16Record, ANImageAsciiBinaryRecord)

private:
	static HANType16Record Create(NVersion version, NInt idc, NUInt flags)
	{

		HANType16Record handle;
		NCheck(ANType16RecordCreate(version.GetValue(), idc, flags, &handle));
		return handle;
	}

	static HANType16Record Create(NVersion version, NInt idc, const NStringWrapper & udi, const NStringWrapper & src, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, const ::Neurotec::Images::NImage & image, NUInt flags)
	{

		HANType16Record handle;
		NCheck(ANType16RecordCreateFromNImageN(version.GetValue(), idc, udi.GetHandle(), src.GetHandle(), slc, cga, image.GetHandle(), flags, &handle));
		return handle;
	}
public:
	explicit ANType16Record(NVersion version, NInt idc, NUInt flags = 0)
		: ANImageAsciiBinaryRecord(Create(version, idc, flags), true)
	{
	}

	ANType16Record(NVersion version, NInt idc, const NStringWrapper & udi, const NStringWrapper & src, BdifScaleUnits slc,
	ANImageCompressionAlgorithm cga, const ::Neurotec::Images::NImage & image, NUInt flags = 0)
		: ANImageAsciiBinaryRecord(Create(version, idc, udi, src, slc, cga, image, flags), true)
	{
	}

	NString GetUserDefinedImage() const
	{
		return GetString(ANType16RecordGetUserDefinedImageN);
	}

	void SetUserDefinedImage(const NStringWrapper & value)
	{
		return SetString(ANType16RecordSetUserDefinedImageN, value);
	}

	bool GetUserDefinedQualityScore(ANQualityMetric * pValue) const
	{
		NBool hasValue;
		NCheck(ANType16RecordGetUserDefinedQualityScore(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetUserDefinedQualityScore(const ANQualityMetric * pValue)
	{
		NCheck(ANType16RecordSetUserDefinedQualityScore(GetHandle(), pValue));
	}
};

}}}

#endif // !AN_TYPE_16_RECORD_HPP_INCLUDED
