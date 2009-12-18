// copyright 2008, 2009 t. schneider tes@mit.edu
// 
// this file is part of the Dynamic Compact Control Language (DCCL),
// the goby-acomms codec. goby-acomms is a collection of libraries 
// for acoustic underwater networking
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this software.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DCCLConstants20091211H
#define DCCLConstants20091211H

#include <string>
#include <bitset>
#include <limits>

#include "acomms/acomms_constants.h"

namespace dccl
{

/// Enumeration of DCCL types used for sending messages. dccl_enum and dccl_string primarily map to cpp_string, dccl_bool to cpp_bool, dccl_int to cpp_long, dccl_float to cpp_double
    enum DCCLType { dccl_static, /*!<  \verbatim <static/> \endverbatim */
                    dccl_bool, /*!< \verbatim <bool/> \endverbatim */
                    dccl_int, /*!< \verbatim <int/> \endverbatim */
                    dccl_float, /*!< \verbatim <float/> \endverbatim */
                    dccl_enum, /*!< \verbatim <enum/> \endverbatim */
                    dccl_string /*!< \verbatim <string/> \endverbatim */
    };
/// Enumeration of C++ types used in DCCL.
    enum DCCLCppType { cpp_notype,/*!< not one of the C++ types used in DCCL */
                       cpp_bool,/*!< C++ bool */
                       cpp_string,/*!< C++ std::string */
                       cpp_long,/*!< C++ long */
                       cpp_double/*!< C++ double */
    };

}

#endif
