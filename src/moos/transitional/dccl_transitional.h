// copyright 2009 t. schneider tes@mit.edu
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

#ifndef DCCLTRANSITIONAL20091211H
#define DCCLTRANSITIONAL20091211H

#include <string>
#include <set>
#include <map>
#include <ostream>
#include <stdexcept>
#include <vector>

#include "goby/moos/transitional/xml/xml_parser.h"
#include "goby/util/time.h"
#include "goby/common/logger.h"

#include "message.h"
#include "message_val.h"
#include "goby/acomms/dccl/dccl_exception.h"
#include "goby/moos/protobuf/transitional.pb.h"
#include "goby/moos/protobuf/pAcommsHandler_config.pb.h"
#include "goby/acomms/protobuf/queue.pb.h"
#include "goby/acomms/protobuf/modem_message.pb.h"
#include "goby/acomms/acomms_helpers.h"
#include "goby/acomms/dccl.h"

#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>

/// The global namespace for the Goby project.
namespace goby
{
    namespace util
    { class FlexOstream; }


    /// Objects pertaining to transitioning from DCCLv1 to DCCLv2
    namespace transitional
    {
        /// use this for displaying a human readable version
        template<typename Value>
            std::ostream& operator<< (std::ostream& out, const std::map<std::string, Value>& m)
        {
            typedef std::pair<std::string, Value> P;
            BOOST_FOREACH(const P& p, m)
            {
                out << "\t" << "key: " << p.first << std::endl
                    << "\t" << "value: " << p.second << std::endl;
            }
            return out;
        }

        template<typename Value>
            std::ostream& operator<< (std::ostream& out, const std::multimap<std::string, Value>& m)
        {
            typedef std::pair<std::string, Value> P;
            BOOST_FOREACH(const P& p, m)
            {
                out << "\t" << "key: " << p.first << std::endl
                    << "\t" << "value: " << p.second << std::endl;
            }
            return out;
        }

    
        /// use this for displaying a human readable version of this STL object
        std::ostream& operator<< (std::ostream& out, const std::set<unsigned>& s);
        /// use this for displaying a human readable version of this STL object
        std::ostream& operator<< (std::ostream& out, const std::set<std::string>& s);

        /// \class DCCLTransitionalCodec dccl.h goby/acomms/dccl.h
        /// \brief provides an API to the Transitional Dynamic CCL Codec (looks like DCCLv1, but calls DCCLv2). Warning: this class is for legacy support only, new applications should use DCCLCodec directly.
        /// \ingroup acomms_api
        /// \sa transitional.proto and acomms_modem_message.proto for definition of Google Protocol Buffers messages (namespace goby::transitional::protobuf).

        class DCCLTransitionalCodec 
        {
          public:
            /// \name Constructors/Destructor
            //@{         
            /// \brief Instantiate optionally with a ostream logger (for human readable output)
            /// \param log std::ostream object or FlexOstream to capture all humanly readable runtime and debug information (optional).
            DCCLTransitionalCodec();

            /// destructor
            ~DCCLTransitionalCodec() {}
            //@}

            void convert_to_v2_representation(pAcommsHandlerConfig* cfg);
            
            
            /// \name Initialization Methods.
            ///
            /// These methods are intended to be called before doing any work with the class. However,
            /// they may be called at any time as desired.
            //@{

            /// \brief Set (and overwrite completely if present) the current configuration. (protobuf::DCCLTransitionalConfig defined in acomms_dccl.proto)
//            void set_cfg(const protobuf::DCCLTransitionalConfig& cfg);

            /// \brief Set (and merge "repeat" fields) the current configuration. (protobuf::DCCLTransitionalConfig defined in acomms_dccl.proto)
//            void merge_cfg(const protobuf::DCCLTransitionalConfig& cfg);
            

            
            /// \brief Add an algorithm callback for a MessageVal. The return value is stored back into the input parameter (MessageVal). See test.cpp for an example.
            ///
            /// \param name name of the algorithm (\xmltag{... algorithm="name"})
            /// \param func has the form void name(MessageVal& val_to_edit) (see AdvAlgFunction1). can be a function pointer (&name) or
            /// any function object supported by boost::function (http://www.boost.org/doc/libs/1_34_0/doc/html/function.html)
//            void add_algorithm(const std::string& name, AlgFunction1 func);
        
            /// \brief Add an advanced algorithm callback for any DCCL C++ type that may also require knowledge of all the other message variables
            /// and can optionally have additional parameters
            ///
            /// \param name name of the algorithm (\xmltag{... algorithm="name:param1:param2"})
            /// \param func has the form
            /// void name(MessageVal& val_to_edit,
            ///  const std::vector<std::string> params,
            ///  const std::map<std::string,MessageVal>& vals) (see AdvAlgFunction3). func can be a function pointer (&name) or
            /// any function object supported by boost::function (http://www.boost.org/doc/libs/1_34_0/doc/html/function.html).
            /// \param params (passed to func) a list of colon separated parameters passed by the user in the XML file. param[0] is the name.
            /// \param vals (passed to func) a map of \ref tag_name to current values for all message variables.
//            void add_adv_algorithm(const std::string& name, AlgFunction2 func);

            /// Registers the group names used for the FlexOstream logger
//            static void add_flex_groups(util::FlexOstream* tout);
            
            //@}
        
            /// \name Codec functions.
            ///
            /// This is where the real work happens.
            //@{         
            /// \brief Encode a message.
            ///
            /// \param k can either be std::string (the name of the message) or unsigned (the id of the message)
            /// \param bytes location for the encoded bytes to be stored. this is suitable for sending to the Micro-Modem
            /// \param m map of std::string (\ref tag_name) to a vector of MessageVal representing the values to encode. No fields can be arrays using this call. If fields are arrays, all values but the first in the array will be set to NaN or blank.
            /* template<typename Key> */
            /*     void encode(const Key& k, boost::shared_ptr<google::protobuf::Message>& msg, */
            /*                 const std::map<std::string, DCCLMessageVal>& m) */
            /* { */
            /*     std::map<std::string, std::vector<DCCLMessageVal> > vm; */

            /*     typedef std::pair<std::string,DCCLMessageVal> P; */
            /*     BOOST_FOREACH(const P& p, m) */
            /*         vm.insert(std::pair<std::string,std::vector<DCCLMessageVal> >(p.first, p.second)); */
                
            /*     encode_private(to_iterator(k), msg, vm); */
            /* } */

            /// \brief Encode a message.
            ///
            /// \param k can either be std::string (the name of the message) or unsigned (the id of the message)
            /// \param bytes location for the encoded bytes to be stored. this is suitable for sending to the Micro-Modem
            /// \param m map of std::string (\ref tag_name) to a vector of MessageVal representing the values to encode. Fields can be arrays.
            /* template<typename Key> */
            /*     void encode(const Key& k, boost::shared_ptr<google::protobuf::Message>& msg, */
            /*                 const std::map<std::string, std::vector<DCCLMessageVal> >& m) */
            /* { encode_private(to_iterator(k), msg, m); } */

        
            /// \brief Decode a message.
            ///
            /// \param k can either be std::string (the name of the message) or unsigned (the id of the message
            /// \param bytes the bytes to be decoded.
            /// \param m map of std::string (\ref tag_name) to MessageVal to store the values to be decoded. No fields can be arrays using this call. If fields are arrays, only the first value is returned.
            /* void decode(const google::protobuf::Message& msg, */
            /*             std::map<std::string, DCCLMessageVal>& m) */
            /* { */
            /*     std::map<std::string, std::vector<DCCLMessageVal> > vm; */
                
            /*     decode_private(msg, vm); */
            
            /*     typedef std::pair<std::string,std::vector<DCCLMessageVal> > P; */
            /*     BOOST_FOREACH(const P& p, vm) */
            /*         m.insert(std::pair<std::string,DCCLMessageVal>(p.first, DCCLMessageVal(p.second))); */
            /* } */
        
            /// \brief Decode a message.
            ///
            /// \param k can either be std::string (the name of the message) or unsigned (the id of the message
            /// \param bytes the bytes to be decoded.
            /// \param m map of std::string (\ref tag_name) to MessageVal to store the values to be decoded
            /* void decode(const google::protobuf::Message& msg, */
            /*             std::map<std::string, std::vector<DCCLMessageVal> >& m) */
            /* { decode_private(msg, m); } */
            
        
            //@}
        
            /// \name Informational Methods
            ///
            //@{         
            /// long summary of a message for a given Key (std::string name or unsigned id)
            /// \param k can either be std::string (the name of the message) or unsigned (the id of the message)
            template<typename Key>
                std::string summary(const Key& k) const
            { return to_iterator(k)->get_display(); }
            /// long summary of a message for all loaded messages
            std::string summary() const;

            /// brief summary of a message for a given Key (std::string name or unsigned id)
            template<typename Key>
                std::string brief_summary(const Key& k) const
            { return to_iterator(k)->get_short_display(); }

            /* template<typename Key> */
            /*     void write_schema_to_dccl2(const Key& k, std::ofstream* proto_file) */
            /* { */
            /*     to_iterator(k)->write_schema_to_dccl2(proto_file); */
                
            /* } */

            template<typename Key>
                const google::protobuf::Descriptor* descriptor(const Key& k)
            {  return to_iterator(k)->descriptor(); }            

                
            /// brief summary of a message for all loaded messages
            std::string brief_summary() const;

            /// how many message are loaded?
            /// \return number of messages loaded
            unsigned message_count() { return messages_.size(); }

            /// \return repeat value (number of copies of the message per encode)
            template<typename Key>
                unsigned get_repeat(const Key& k)
            { return to_iterator(k)->repeat(); }
        
            /// \return set of all message ids loaded
            std::set<unsigned> all_message_ids();
            /// \return set of all message names loaded
            std::set<std::string> all_message_names();
            /// \return map of names to DCCL types needed to encode a given message
            template<typename Key>
                std::map<std::string, std::string> message_var_names(const Key& k) const
            { return to_iterator(k)->message_var_names(); }
        
            /// \param id message id
            /// \return name of message
            std::string id2name(unsigned id) {return to_iterator(id)->name();}
            /// \param name message name
            /// \return id of message
            unsigned name2id(const std::string& name) {return to_iterator(name)->id();}
            
            
            //@}


            /// \name Publish/subscribe architecture related methods
            /// \brief Methods written largely to support DCCL in the context of a publish/subscribe architecture (e.g., see MOOS (http://www.robots.ox.ac.uk/~mobile/MOOS/wiki/pmwiki.php)). The other methods provide a complete interface for encoding and decoding DCCL messages. However, the methods listed here extend the functionality to allow for
            /// <ul>
            /// <li> message creation triggering (a message is encoded on a certain event, either time based or publish based) </li>
            /// <li> encoding that will parse strings of the form: "key1=value,key2=value,key3=value" </li>
            /// <li> decoding to an arbitrarily formatted string (similar concept to printf) </li>
            /// </ul>
            /// These methods will be useful if you are interested in any of the features mentioned above.
        
            //@{
            /// \brief Encode a message using src_var tags instead of name tags
            ///
            /// Values can be passed in on one or more maps of names to values, similar to DCCLTransitionalCodec::encode. 
            /// Casts are made and string parsing of key=value comma delimited fields is performed.
            /// This differs substantially from the behavior of encode above.
            /// For example, take this message variable:
            /*! \verbatim
              <int>
              <name>myint</name>
              <src_var>somevar</src_var>
              </int> \endverbatim
            */
            ///
            /// Using this method you can pass vals["somevar"] = "mystring=foo,blah=dog,myint=32"
            /// or vals["somevar"] = 32.0
            /// and both cases will properly parse out 32 as the value for this field.
            /// In comparison, using the normal encode you would pass vals["myint"] = 32
            ///
            /// \param k can either be std::string (the name of the message) or unsigned (the id of the message)
            /// \param msg location for the encoded message to be stored (goby::acomms::protobuf::ModemDataTransmission defined in acomms_modem_message.proto)
            /// \param vals map of source variable name to MessageVal values. 
            /* template<typename Key> */
            /*     void pubsub_encode(const Key& k, */
            /*                        boost::shared_ptr<google::protobuf::Message>& msg, */
            /*                        const std::map<std::string, std::vector<DCCLMessageVal> >& pubsub_vals) */
            /* { */
            /*     std::vector<DCCLMessage>::iterator it = to_iterator(k); */
                
            /*     if(log_) */
            /*     { */
            /*         *log_ << group("dccl_enc") << "starting publish/subscribe encode for " << it->name() << std::endl; */
            /*         *log_ << group("dccl_enc") << "publish/subscribe variables are: " << std::endl; */
                    
            /*         typedef std::pair<std::string, std::vector<DCCLMessageVal> > P; */
            /*         BOOST_FOREACH(const P& p, pubsub_vals)                     */
            /*         { */
            /*             if(!p.first.empty()) */
            /*             { */
            /*                 BOOST_FOREACH(const DCCLMessageVal& mv, p.second) */
            /*                     *log_ << group("dccl_enc") << "\t" << p.first << ": " <<  mv << std::endl; */
            /*             }    */
            /*         }                  */
            /*     } */

                
            /*     std::map<std::string, std::vector<DCCLMessageVal> > vals; */
            /*     // clean the pubsub vals into dccl vals */
            /*     // using <src_var/> tag, do casts from double, pull strings from key=value,key=value, etc. */
            /*     BOOST_FOREACH(boost::shared_ptr<DCCLMessageVar> mv, it->layout()) */
            /*         mv->read_pubsub_vars(vals, pubsub_vals); */
            /*     BOOST_FOREACH(boost::shared_ptr<DCCLMessageVar> mv, it->header()) */
            /*         mv->read_pubsub_vars(vals, pubsub_vals); */
            
            /*     encode_private(it, msg, vals); */

            /*     if(log_) *log_ << group("dccl_enc") << "message published to variable: " << */
            /*                 get_outgoing_hex_var(it->id()) << std::endl; */
            /* } */

            /// \brief Encode a message using \ref tag_src_var tags instead of \ref tag_name tags
            /// 
            /// Use this version if you do not have vectors of src_var values
            /* template<typename Key> */
            /*     void pubsub_encode(const Key& k, */
            /*                        boost::shared_ptr<google::protobuf::Message>& msg, */
            /*                        const std::map<std::string, DCCLMessageVal>& pubsub_vals) */
            /* { */
            /*     std::map<std::string, std::vector<DCCLMessageVal> > vm; */

            /*     typedef std::pair<std::string,DCCLMessageVal> P; */
            /*     BOOST_FOREACH(const P& p, pubsub_vals) */
            /*         vm.insert(std::pair<std::string,std::vector<DCCLMessageVal> >(p.first, p.second)); */
            
            /*     pubsub_encode(k, msg, vm); */
            /* } */

        
            /// \brief Decode a message using formatting specified in publish tags.
            ///
            /// Values will be received in two maps, one of strings and the other of doubles. The publish value will be placed
            /// either based on the "type" parameter of the publish_var tag (e.g. \<publish_var type="long"\>SOMEVAR\</publish_var\> will be placed as a long). If no type parameter is given and the variable is numeric (e.g. "23242.23") it will be considered a double. If not numeric, it will be considered a string.
            ///
            /// \param k can either be std::string (the name of the message) or unsigned (the id of the message)
            /// \param msg message to be decoded. (goby::acomms::protobuf::ModemDataTransmission defined in acomms_modem_message.proto)
            /// \param vals pointer to std::multimap of publish variable name to std::string values.
            /* void pubsub_decode(const google::protobuf::Message& msg, */
            /*                    std::multimap<std::string, DCCLMessageVal>* pubsub_vals) */
                               
            /* { */
            /*     std::map<std::string, std::vector<DCCLMessageVal> > vals; */
            /*     std::vector<DCCLMessage>::iterator it = decode_private(msg, vals); */
                
            /*     // go through all the publishes_ and fill in the format strings */
            /*     BOOST_FOREACH(DCCLPublish& p, it->publishes()) */
            /*         p.write_publish(vals, pubsub_vals); */

            /*     if(log_) */
            /*     { */
            /*         *log_ << group("dccl_dec") << "publish/subscribe variables are: " << std::endl; */
            /*         typedef std::pair<std::string, DCCLMessageVal> P; */
            /*         BOOST_FOREACH(const P& p, *pubsub_vals) */
            /*         { */
                        
            /*             *log_ << group("dccl_dec") << "\t" << p.first << ": " << p.second << std::endl; */
            /*         }                  */
            /*         *log_ << group("dccl_dec") << "finished publish/subscribe decode for " << it->name() << std::endl; */
            /*     } */
            /* } */
        
        
            /// what moos variables do i need to provide to create a message with a call to encode_using_src_vars
            template<typename Key>
                std::set<std::string> get_pubsub_src_vars(const Key& k)
            { return to_iterator(k)->get_pubsub_src_vars(); }

            /// for a given message name, all architecture variables (sources, input, destination, trigger)
            template<typename Key>
                std::set<std::string> get_pubsub_all_vars(const Key& k)
            { return to_iterator(k)->get_pubsub_all_vars(); }

            /// all architecture variables needed for encoding (includes trigger)
            template<typename Key>
                std::set<std::string> get_pubsub_encode_vars(const Key& k)
            { return to_iterator(k)->get_pubsub_encode_vars(); }

            /// for a given message, all architecture variables for decoding (input)
            template<typename Key>
                std::set<std::string> get_pubsub_decode_vars(const Key& k)
            { return to_iterator(k)->get_pubsub_decode_vars(); }
        
            /// returns outgoing architecture hexadecimal variable
            template<typename Key>
                std::string get_outgoing_hex_var(const Key& k)
            { return to_iterator(k)->out_var(); }

            /// returns incoming architecture hexadecimal variable
            template<typename Key>
                std::string get_incoming_hex_var(const Key& k)
            { return to_iterator(k)->in_var(); }

        
            /// \brief look if key / value are trigger for any loaded messages
            /// if so, store to id and return true
            bool is_publish_trigger(std::set<unsigned>& id, const std::string& key, const std::string& value);

            /// \brief look if the time is right for trigger for any loaded messages
            /// if so, store to id and return true
            bool is_time_trigger(std::set<unsigned>& id);

            /// \brief see if this key is for an incoming message
            /// if so, return id for decoding
            bool is_incoming(unsigned& id, const std::string& key);
            //@}

        
            // returns a reference to all DCCLMessage objects.

            // this is only used if one needs more control than DCCLTransitionalCodec
            // provides
            std::vector<DCCLMessage>& messages() {return messages_;}

            // grab a reference to the manipulator manager used by the loaded XML messages
            const ManipulatorManager& manip_manager() const { return manip_manager_; }
        
          private:
            void convert_xml_message_file(const std::string& xml_file,
                                          std::string* proto_file,
                                          google::protobuf::RepeatedPtrField<goby::moos::protobuf::TranslatorEntry>* translator_entries);

            void fill_create(boost::shared_ptr<DCCLMessageVar> var,
                             std::map<std::string, goby::moos::protobuf::TranslatorEntry::CreateParser*>* parser_map,
                             goby::moos::protobuf::TranslatorEntry* entry);

            
            std::vector<DCCLMessage>::const_iterator to_iterator(const std::string& message_name) const;
            std::vector<DCCLMessage>::iterator to_iterator(const std::string& message_name);
            std::vector<DCCLMessage>::const_iterator to_iterator(const unsigned& id) const;
            std::vector<DCCLMessage>::iterator to_iterator(const unsigned& id);        

            // in map not passed by reference because we want to be able to modify it
            void encode_private(std::vector<DCCLMessage>::iterator it,
                                boost::shared_ptr<google::protobuf::Message>& proto_msg,
                                std::map<std::string, std::vector<DCCLMessageVal> > in);

            // in string not passed by reference because we want to be able to modify it
            std::vector<DCCLMessage>::iterator decode_private(const google::protobuf::Message& proto_msg, std::map<std::string, std::vector<DCCLMessageVal> >& out);
        
            void check_duplicates();
            
            
            

            //      void process_cfg();
            
          private:
            std::ostream* log_;
            goby::acomms::DCCLCodec* dccl_;

            std::vector<DCCLMessage> messages_;

            std::map<std::string, size_t>  name2messages_;
            std::map<unsigned, size_t>     id2messages_;

            protobuf::DCCLTransitionalConfig cfg_;

            boost::posix_time::ptime start_time_;
            
            ManipulatorManager manip_manager_;
        };
        
        /// outputs information about all available messages (same as std::string summary())
        std::ostream& operator<< (std::ostream& out, const DCCLTransitionalCodec& d);

    }
}


#endif
