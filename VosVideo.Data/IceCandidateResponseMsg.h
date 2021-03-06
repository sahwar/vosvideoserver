#pragma once
#include "ReceivedData.h"

namespace vosvideo
{
	namespace data
	{
		class IceCandidateResponseMsg final : public ReceivedData
		{
		public:
			IceCandidateResponseMsg();
			IceCandidateResponseMsg(const std::wstring& srvPeer, 
				const std::wstring& clientPeer, 
				const std::wstring& sdp, int devId);
			virtual ~IceCandidateResponseMsg();

			virtual void FromJsonValue(const web::json::value& obj) override;
			virtual std::wstring ToString() const;
			web::json::value jObj_;
		};
	}
}
