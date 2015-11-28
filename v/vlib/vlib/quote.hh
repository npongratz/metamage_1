/*
	quote.hh
	--------
*/

#ifndef VLIB_QUOTE_HH
#define VLIB_QUOTE_HH

// plus
#include "plus/string.hh"


namespace vlib
{
	
	unsigned char unquote_byte( const plus::string& s );
	
	inline
	plus::string unquote_string( const plus::string& s )
	{
		return s.substr( 1, s.size() - 2 );
	}
	
	plus::string unquote_escaped_string( const plus::string& s );
	
	plus::string quote_byte( unsigned char c );
	
	plus::string quote_string( const plus::string& s );
	
}

#endif
