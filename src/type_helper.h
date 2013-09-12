// Copyright 2009-2013 Toby Schneider (https://launchpad.net/~tes)
//                     Massachusetts Institute of Technology (2007-)
//                     Woods Hole Oceanographic Institution (2007-)
//                     DCCL Developers Team (https://launchpad.net/~dccl-dev)
// 
//
// This file is part of the Dynamic Compact Control Language Library
// ("DCCL").
//
// DCCL is free software: you can redistribute them and/or modify
// them under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DCCL is distributed in the hope that they will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DCCL.  If not, see <http://www.gnu.org/licenses/>.



#ifndef TypeHelper20110405H
#define TypeHelper20110405H

#include <map>

#include <boost/shared_ptr.hpp>

#include "protobuf_cpp_type_helpers.h"

namespace dccl
{

    /// \brief Provides FromProtoTypeBase and FromProtoCppTypeBase type identification helper classes for various representations of the underlying field.
    class TypeHelper
    {
      public:
        static boost::shared_ptr<FromProtoTypeBase> find(google::protobuf::FieldDescriptor::Type type);
        static boost::shared_ptr<FromProtoCppTypeBase> find(const google::protobuf::FieldDescriptor* field)
        {
            if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE)
                return find(field->message_type());
            else
                return find(field->cpp_type());
        }
                
        static boost::shared_ptr<FromProtoCppTypeBase> find(const google::protobuf::Descriptor* desc)
        {
            return find(google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE,
                        desc->full_name());
        }
                
        static boost::shared_ptr<dccl::FromProtoCppTypeBase> find(google::protobuf::FieldDescriptor::CppType cpptype, const std::string& type_name = "");


      private:
        friend class FieldCodecManager;            
        template<typename ProtobufMessage>
            static void add()
        {
            custom_message_map_.insert(std::make_pair(ProtobufMessage::descriptor()->full_name(), boost::shared_ptr<FromProtoCppTypeBase>(new FromProtoCustomMessage<ProtobufMessage>)));
        }

      private:
        TypeHelper() { initialize(); }            
        ~TypeHelper() { }
        TypeHelper(const TypeHelper&);
        TypeHelper& operator= (const TypeHelper&);
        void initialize();    
            
      public:
        // so we can use shared_ptr to hold the singleton
        template<typename T>
            friend void boost::checked_delete(T*);
        static boost::shared_ptr<TypeHelper> inst_;
            
        typedef std::map<google::protobuf::FieldDescriptor::Type,
            boost::shared_ptr<FromProtoTypeBase> > TypeMap;
        static TypeMap type_map_;

        typedef std::map<google::protobuf::FieldDescriptor::CppType,
            boost::shared_ptr<FromProtoCppTypeBase> > CppTypeMap;
        static CppTypeMap cpptype_map_;

        typedef std::map<std::string,
            boost::shared_ptr<FromProtoCppTypeBase> > CustomMessageMap;
        static CustomMessageMap custom_message_map_;
    };
}
#endif
