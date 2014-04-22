// Copyright 2009-2014 Toby Schneider (https://launchpad.net/~tes)
//                     GobySoft, LLC (2013-)
//                     Massachusetts Institute of Technology (2007-2014)
//                     DCCL Developers Team (https://launchpad.net/~dccl-dev)
//
// This file is part of the Dynamic Compact Control Language Library
// ("DCCL").
//
// DCCL is free software: you can redistribute them and/or modify
// them under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 2.1 of the License, or
// (at your option) any later version.
//
// DCCL is distributed in the hope that they will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DCCL.  If not, see <http://www.gnu.org/licenses/>.


#ifndef VERSION20110304H
#define VERSION20110304H

#include <string>

#define DCCL_VERSION_MAJOR @DCCL_VERSION_MAJOR@
#define DCCL_VERSION_MINOR @DCCL_VERSION_MINOR@
#define DCCL_VERSION_PATCH @DCCL_VERSION_PATCH@

namespace dccl
{
    const std::string VERSION_STRING = "@DCCL_VERSION@";
    const std::string VERSION_DATE = "@DCCL_VERSION_DATE@";
    const std::string COMPILE_DATE = "@DCCL_COMPILE_DATE@";
}

#endif
