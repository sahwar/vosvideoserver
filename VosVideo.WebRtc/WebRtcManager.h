#pragma once
#include <webrtc/base/scoped_ref_ptr.h>
#include <talk/app/webrtc/peerconnectioninterface.h>
#include <webrtc/base/physicalsocketserver.h>
#include "VosVideo.Communication/CommunicationManager.h"
#include "VosVideo.Communication/InterprocessComm.h"
#include "VosVideo.Communication.InterprocessQueue/InterprocessQueueEngine.h"
#include "VosVideo.Camera/CameraDeviceManager.h"
#include "VosVideo.CameraPlayer/CameraPlayerBase.h"
#include "VosVideo.Data/DtoFactory.h"
#include "WebRtcPeerConnection.h"


namespace vosvideo
{
	namespace vvwebrtc
	{
		class WebRtcManager : public vosvideo::communication::MessageReceiver
		{
		public:
			WebRtcManager(std::shared_ptr<vosvideo::communication::PubSubService> pubsubService, 
				std::shared_ptr<vosvideo::communication::InterprocessQueueEngine> queueEng);
			virtual ~WebRtcManager();

			virtual void OnMessageReceived(const std::shared_ptr<vosvideo::data::ReceivedData> receivedMessage);

		private:
			typedef std::map<std::wstring, rtc::scoped_refptr<WebRtcPeerConnection> > WebRtcPeerConnectionMap;
			typedef std::vector<rtc::scoped_refptr<WebRtcPeerConnection>> WebRtcPeerConnectionVector;
			typedef std::unordered_map<std::wstring, std::vector<std::shared_ptr<vosvideo::data::ReceivedData> >> WebRtcDeferredIceMap;
			void CreatePeerConnectionFactory();
			void DeleteAllPeerConnections();
			void DeletePeerConnection(const std::wstring& fromPeer);
			int CheckFinishingPeerConnections();
			void Shutdown();

			std::shared_ptr<vosvideo::communication::PubSubService> pubSubService_;
			int activeDeviseId_;
			std::wstring deviceName_;
			rtc::AutoThread* mainThread_;
			rtc::PhysicalSocketServer* physicalSocketServer_;
			WebRtcPeerConnectionMap peer_connections_;
			WebRtcPeerConnectionVector finishing_peer_connections_;
			WebRtcDeferredIceMap deferredIce_;
			rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
			std::shared_ptr<vosvideo::communication::InterprocessQueueEngine> queueEng_;
			vosvideo::cameraplayer::CameraPlayerBase* player_;
			std::mutex mutex_;
			bool inShutdown_;
			Concurrency::timer<WebRtcManager*>* isaliveTimer_; 
			const static int isaliveTimeout_ = 60000; // 1 min
		};
	}
}
