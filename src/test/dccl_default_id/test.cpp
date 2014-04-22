// Copyright 2009-2014 Toby Schneider (https://launchpad.net/~tes)
//                     GobySoft, LLC (2013-)
//                     Massachusetts Institute of Technology (2007-2014)
//                     DCCL Developers Team (https://launchpad.net/~dccl-dev)
//
// This file is part of the Dynamic Compact Control Language Applications
// ("DCCL").
//
// DCCL is free software: you can redistribute them and/or modify
// them under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DCCL is distributed in the hope that they will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DCCL.  If not, see <http://www.gnu.org/licenses/>.



// tests fixed id header

#include "dccl/codec.h"
#include "test.pb.h"

using dccl::operator<<;

int main(int argc, char* argv[])
{
    dccl::dlog.connect(dccl::logger::ALL, &std::cerr);
    
    dccl::Codec codec;

    ShortIDMsg short_id_msg;
    codec.load(short_id_msg.GetDescriptor());
    codec.info(short_id_msg.GetDescriptor(), &dccl::dlog);

    std::string encoded;
    assert(codec.size(short_id_msg) == 1);
    codec.encode(&encoded, short_id_msg);
    codec.decode(encoded, &short_id_msg);

    LongIDMsg long_id_msg;
    codec.load(long_id_msg.GetDescriptor());
    codec.info(long_id_msg.GetDescriptor(), &dccl::dlog);
    assert(codec.size(long_id_msg) == 2);
    codec.encode(&encoded, long_id_msg);
    codec.decode(encoded, &long_id_msg);
    

    ShortIDEdgeMsg short_id_edge_msg;
    codec.load(short_id_edge_msg.GetDescriptor());
    codec.info(short_id_edge_msg.GetDescriptor(), &dccl::dlog);
    assert(codec.size(short_id_edge_msg) == 1);
    codec.encode(&encoded, short_id_edge_msg);
    codec.decode(encoded, &short_id_edge_msg);

    LongIDEdgeMsg long_id_edge_msg;
    codec.load(long_id_edge_msg.GetDescriptor());
    codec.info(long_id_edge_msg.GetDescriptor(), &dccl::dlog);
    codec.encode(&encoded, long_id_edge_msg);
    codec.decode(encoded, &long_id_edge_msg);
    assert(codec.size(long_id_edge_msg) == 2);

    TooLongIDMsg too_long_id_msg;
    // should fail validation
    try
    {
        codec.load(too_long_id_msg.GetDescriptor());
        assert(false);
    }
    catch(dccl::Exception& e)
    { }
    

    ShortIDMsgWithData short_id_msg_with_data;
    codec.load(short_id_msg_with_data.GetDescriptor());
    codec.info(short_id_msg_with_data.GetDescriptor(), &dccl::dlog);

    short_id_msg_with_data.set_in_head(42);
    short_id_msg_with_data.set_in_body(37);
    codec.encode(&encoded, short_id_msg_with_data);
    codec.decode(encoded, &short_id_msg_with_data);

    
    std::cout << "all tests passed" << std::endl;
}

