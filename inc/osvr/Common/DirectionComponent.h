/** @file
    @brief Header

    @date 2015

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>

*/

// Copyright 2015 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_DirectionComponent_h_GUID_DBB6E776_4381_4FB7_C855_B77A87F811BE
#define INCLUDED_DirectionComponent_h_GUID_DBB6E776_4381_4FB7_C855_B77A87F811BE

// Internal Includes
#include <osvr/Common/Export.h>
#include <osvr/Common/DeviceComponent.h>
#include <osvr/Common/SerializationTags.h>
#include <osvr/Util/ChannelCountC.h>
#include <osvr/Util/ClientReportTypesC.h>

// Library/third-party includes
#include <vrpn_BaseClass.h>

// Standard includes
// - none

namespace osvr {
namespace common {

    struct DirectionData {
        OSVR_ChannelCount sensor;
        OSVR_DirectionState direction;
    };

    namespace messages {
        class DirectionRecord : public MessageRegistration<DirectionRecord> {
          public:
            class MessageSerialization;

            static const char *identifier();
        };

    } // namespace messages

    /// @brief BaseDevice component
    class DirectionComponent : public DeviceComponent {
      public:
        /// @brief Factory method
        ///
        /// Required to ensure that allocation and deallocation stay on the same
        /// side of a DLL line.
        static OSVR_COMMON_EXPORT shared_ptr<DirectionComponent>
        create(OSVR_ChannelCount numSensor = 1);

        /// @brief Explicit virtual destructor
        ///
        /// Required to ensure that allocation and deallocation stay on the same
        /// side of a DLL line.
        virtual OSVR_COMMON_EXPORT ~DirectionComponent();

        /// @brief Message from server to client, containing 3D direction data.
        messages::DirectionRecord directionRecord;

        OSVR_COMMON_EXPORT void
        sendDirectionData(OSVR_DirectionState direction,
                          OSVR_ChannelCount sensor,
                          OSVR_TimeValue const &timestamp);

        typedef std::function<void(DirectionData const &,
                                   util::time::TimeValue const &)>
            DirectionHandler;
        OSVR_COMMON_EXPORT void registerDirectionHandler(DirectionHandler cb);

      private:
        DirectionComponent(OSVR_ChannelCount numChan);
        virtual void m_parentSet();

        static int VRPN_CALLBACK
        m_handleDirectionRecord(void *userdata, vrpn_HANDLERPARAM p);

        void m_checkFirst(OSVR_DirectionState const &direction);

        OSVR_ChannelCount m_numSensor;
        std::vector<DirectionHandler> m_cb;
        bool m_gotOne;
    };

} // namespace common
} // namespace osvr

#endif // INCLUDED_DirectionComponent_h_GUID_DBB6E776_4381_4FB7_C855_B77A87F811BE
