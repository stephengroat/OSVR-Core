/** @file
    @brief Header

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>;
    <http://sensics.com>
*/

// Copyright 2014 Sensics, Inc.
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

#ifndef INCLUDED_PluginSpecificRegistrationContext_h_GUID_E8A348C1_28DC_4691_6214_32F75A6665F0
#define INCLUDED_PluginSpecificRegistrationContext_h_GUID_E8A348C1_28DC_4691_6214_32F75A6665F0

// Internal Includes
#include <ogvr/PluginKit/PluginInterfaceC.h>
#include <ogvr/Util/UniquePtr.h>

// Library/third-party includes
#include <libfunctionality/PluginHandle.h>
#include <boost/noncopyable.hpp>

// Standard includes
#include <string>
#include <vector>

namespace ogvr {
/// @brief Internal class backing the context of registrations performed by a
/// single plugin.
class PluginSpecificRegistrationContext : boost::noncopyable {
  public:
    /// @brief Constructor
    PluginSpecificRegistrationContext(std::string const &name);
    /// @brief Destructor responsible for destroying plugin data in reverse
    /// order.
    ~PluginSpecificRegistrationContext();

    /// @brief Assume ownership of the plugin handle keeping the plugin library
    /// loaded.
    void takePluginHandle(libfunc::PluginHandle &handle);

    /// @name Plugin API
    /// @brief Called by the C API wrappers in the plugin registration headers.
    /// @{

    /// @}

  private:
    std::string const m_name;
    /// @brief Pointer with ownership semantics for deletion of plugin data.
    typedef unique_ptr<void, OGVRPluginDataDeleteCallback> PluginDataPtr;
    /// @brief List of plugin data.
    typedef std::vector<PluginDataPtr> PluginDataList;

    PluginDataList m_dataList;
    libfunc::PluginHandle m_handle;
};
} // end of namespace ogvr

#endif // INCLUDED_PluginSpecificRegistrationContext_h_GUID_E8A348C1_28DC_4691_6214_32F75A6665F0
