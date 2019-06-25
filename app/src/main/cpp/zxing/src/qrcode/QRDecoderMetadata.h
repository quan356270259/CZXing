#pragma once
/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "CustomData.h"
#include <algorithm>

namespace ZXing {

class ResultPoint;

namespace QRCode {

/**
* Meta-data container for QR Code decoding. Instances of this class may be used to convey information back to the
* decoding caller. Callers are expected to process this.
*
* @see com.google.zxing.common.DecoderResult#getOther()
*/

class DecoderMetadata : public CustomData
{
	bool _mirrored;

public:
	explicit DecoderMetadata(bool mirrored) : _mirrored(mirrored) {}

	/**
	* @return true if the QR Code was mirrored.
	*/
	bool isMirrored() const {
		return _mirrored;
	}

	/**
	* Apply the result points' order correction due to mirroring.
	*
	* @param points Array of points to apply mirror correction to.
	*/
	template <typename Iter>
	void applyMirroredCorrection(Iter first, Iter end) const
	{
		if (!_mirrored)
			return;
		if (std::distance(first, end) < 3)
			return;

		using std::swap;
		swap(*first, *(first + 2));
		// No need to 'fix' top-left and alignment pattern.
	}
};

} // QRCode
} // ZXing
