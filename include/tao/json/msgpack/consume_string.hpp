// Copyright (c) 2018 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAO_JSON_MSGPACK_CONSUME_STRING_HPP
#define TAO_JSON_MSGPACK_CONSUME_STRING_HPP

#include "../external/pegtl/string_input.hpp"

#include "../consume.hpp"
#include "../forward.hpp"

#include "parts_parser.hpp"

namespace tao
{
   namespace json
   {
      namespace msgpack
      {
         template< typename T, template< typename... > class Traits = traits, typename F >
         T consume_string( F&& string )
         {
            msgpack::basic_parts_parser< utf8_mode::CHECK, json_pegtl::memory_input< json_pegtl::tracking_mode::LAZY, json_pegtl::eol::lf_crlf, const char* > > pp( string, __FUNCTION__ );
            return json::consume< T, Traits >( pp );
         }

         template< template< typename... > class Traits = traits, typename F, typename T >
         T consume_string( F&& string, T& t )
         {
            msgpack::basic_parts_parser< utf8_mode::CHECK, json_pegtl::memory_input< json_pegtl::tracking_mode::LAZY, json_pegtl::eol::lf_crlf, const char* > > pp( string, __FUNCTION__ );
            return json::consume< Traits >( pp, t );
         }

      }  // namespace msgpack

   }  // namespace json

}  // namespace tao

#endif
