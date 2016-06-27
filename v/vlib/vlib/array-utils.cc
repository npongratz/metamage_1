/*
	array-utils.cc
	--------------
*/

#include "vlib/array-utils.hh"

// Standard C++
#include <vector>

// plus
#include "plus/integer.hh"

// vlib
#include "vlib/list-utils.hh"
#include "vlib/throw.hh"
#include "vlib/types/byte.hh"


namespace vlib
{
	
	static
	unsigned subscript_integer( const Value& index )
	{
		if ( index.type() != Value_number )
		{
			THROW( "non-integer array subscript" );
		}
		
		const plus::integer& i = index.number();
		
		if ( i.is_negative() )
		{
			THROW( "negative array subscript" );
		}
		
		if ( i > 0xFFFFFFFFu )
		{
			THROW( "Array subscript is too large" );
		}
		
		return i.clipped();
	}
	
	static
	Value get_nth_element( const Value& array, unsigned i )
	{
		if ( Expr* expr = array.expr() )
		{
			if ( expr->op == Op_array )
			{
				return get_nth( expr->right, i );
			}
			
			THROW( "type not subscriptable" );
		}
		else if ( array.type() != V_str  &&  array.type() != V_data )
		{
			THROW( "type not subscriptable" );
		}
		
		const plus::string& s = array.string();
		
		if ( i >= s.size() )
		{
			return Value_empty_list;
		}
		
		return Byte( s[ i ] );
	}
	
	static
	Value indexed_subscript( const Value& array, unsigned i )
	{
		const Value nth = get_nth_element( array, i );
		
		if ( is_empty( nth ) )
		{
			THROW( "subscript exceeds array bounds" );
		}
		
		return nth;
	}
	
	static
	Value sliced_subscript( const Value& array, const Value& index )
	{
		Value results;
		
		if ( Expr* expr = index.expr() )
		{
			if ( expr->op == Op_array )
			{
				std::vector< unsigned > indices;
				
				const Value& list = expr->right;
				
				if ( is_empty( list ) )
				{
					return index;  // empty array
				}
				
				const Value* next = &list;
				
				while ( ! is_empty( *next ) )
				{
					indices.push_back( subscript_integer( first( *next ) ) );
					
					next = &rest( *next );
				}
				
				typedef std::vector< unsigned >::const_iterator Iter;
				
				Iter it = indices.end();
				
				results = indexed_subscript( array, *--it );
				
				while ( it > indices.begin() )
				{
					const unsigned i = *--it;
					
					results = Value( indexed_subscript( array, i ), results );
				}
			}
		}
		
		return make_array( results );
	}
	
	Value linear_subscript( const Value& array, const Value& index )
	{
		if ( index.type() == Value_number )
		{
			const unsigned i = subscript_integer( index );
			
			return indexed_subscript( array, i );
		}
		
		if ( Expr* expr = index.expr() )
		{
			if ( expr->op == Op_array )
			{
				return sliced_subscript( array, index );
			}
		}
		
		THROW( "unsupported subscript type" );
		
		return Value();
	}
	
}