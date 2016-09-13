// Copyright (c) 2016 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_INTERNAL_VALUE_WRITER_HH
#define TAOCPP_JSON_INCLUDE_INTERNAL_VALUE_WRITER_HH

#include <ostream>

#include "escape.hh"

#include "../external/double.hh"

namespace tao
{
   namespace json
   {
      namespace internal
      {
         class value_writer
         {
         private:
            std::ostream & os;
            bool first;

         public:
            explicit value_writer( std::ostream & os ) noexcept
                 : os( os )
            { }

            void null()
            {
               os.write( "null", 4 );
            }

            void boolean( const bool v )
            {
               if ( v ) {
                  os.write( "true", 4 );
               }
               else {
                  os.write( "false", 5 );
               }
            }

            void number( const std::int64_t v )
            {
               os << v;
            }

            void number( const std::uint64_t v )
            {
               os << v;
            }

            void number( const double v )
            {
               json_double_conversion::Dtostr( os, v );
            }

            void string( const std::string & v )
            {
               internal::escape( os, v );
            }

            // array
            void begin_array()
            {
               os.put( '[' );
               first = true;
            }

            void element()
            {
               os.put( ',' );
               first = false;
            }

            void end_array()
            {
               if ( ! first ) {
                  os.seekp( -1, std::ios_base::cur );
               }
               os.put( ']' );
               first = false;
            }

            // object
            void begin_object()
            {
               os.put( '{' );
               first = true;
            }

            void key( const std::string & v )
            {
               if ( ! first ) {
                  os.put( ',' );
               }
               internal::escape( os, v );
               os.put( ':' );
            }

            void value()
            {
               first = false;
            }

            void end_object()
            {
               os.put( '}' );
               first = false;
            }
         };

      } // internal

   } // json

} // tao

#endif
