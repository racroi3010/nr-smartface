#ifndef AN_TYPE_3_RECORD_HPP_INCLUDED
#define AN_TYPE_3_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANFImageBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType3Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_3_RECORD_FIELD_LEN
#undef AN_TYPE_3_RECORD_FIELD_IDC
#undef AN_TYPE_3_RECORD_FIELD_IMP
#undef AN_TYPE_3_RECORD_FIELD_FGP
#undef AN_TYPE_3_RECORD_FIELD_ISR
#undef AN_TYPE_3_RECORD_FIELD_HLL
#undef AN_TYPE_3_RECORD_FIELD_VLL
#undef AN_TYPE_3_RECORD_FIELD_GCA
#undef AN_TYPE_3_RECORD_FIELD_DATA

const NInt AN_TYPE_3_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_3_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;
const NInt AN_TYPE_3_RECORD_FIELD_IMP = AN_F_IMAGE_BINARY_RECORD_FIELD_IMP;
const NInt AN_TYPE_3_RECORD_FIELD_FGP = AN_F_IMAGE_BINARY_RECORD_FIELD_FGP;
const NInt AN_TYPE_3_RECORD_FIELD_ISR = AN_IMAGE_BINARY_RECORD_FIELD_ISR;
const NInt AN_TYPE_3_RECORD_FIELD_HLL = AN_IMAGE_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_3_RECORD_FIELD_VLL = AN_IMAGE_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_3_RECORD_FIELD_GCA = AN_F_IMAGE_BINARY_RECORD_FIELD_CA;
const NInt AN_TYPE_3_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

class ANType3Record : public ANFImageBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType3Record, ANFImageBinaryRecord)

private:
	static HANType3Record Create(NVersion version, NInt idc, NUInt flags)
	{
		HANType3Record handle;
		NCheck(ANType3RecordCreate(version.GetValue(), idc, flags, &handle));
		return handle;
	}

	static HANType3Record Create(NVersion version, NInt idc, bool isr, ANImageCompressionAlgorithm ca, const ::Neurotec::Images::NImage & image, NUInt flags)
	{
		HANType3Record handle;
		NCheck(ANType3RecordCreateFromNImage(version.GetValue(), idc, isr, ca, image.GetHandle(), flags, &handle));
		return handle;
	}

public:
	explicit ANType3Record(NVersion version, NInt idc, NUInt flags = 0)
		: ANFImageBinaryRecord(Create(version, idc, flags), true)
	{
	}

	ANType3Record(NVersion version, NInt idc, bool isr, ANImageCompressionAlgorithm ca, const ::Neurotec::Images::NImage & image, NUInt flags = 0)
		: ANFImageBinaryRecord(Create(version, idc, isr, ca, image, flags), true)
	{
	}

	ANImageCompressionAlgorithm GetCompressionAlgorithm() const
	{
		ANImageCompressionAlgorithm value;
		NCheck(ANType3RecordGetCompressionAlgorithm(GetHandle(), &value));
		return value;
	}

	NByte GetVendorCompressionAlgorithm() const
	{
		NByte value;
		NCheck(ANType3RecordGetVendorCompressionAlgorithm(GetHandle(), &value));
		return value;
	}

	void SetCompressionAlgorithm(ANImageCompressionAlgorithm value, NByte vendorValue)
	{
		NCheck(ANType3RecordSetCompressionAlgorithm(GetHandle(), value, vendorValue));
	}
};

}}}

#endif // !AN_TYPE_3_RECORD_HPP_INCLUDED
