/*
	load_store.cc
	-------------
*/

#include "v68k/load_store.hh"

// v68k
#include "v68k/instruction.hh"
#include "v68k/macros.hh"
#include "v68k/state.hh"


namespace v68k
{
	
	#define N( x )  (!!(x) << 3)
	#define Z( x )  (!!(x) << 2)
	#define V( x )  (!!(x) << 1)
	#define C( x )  (!!(x) << 0)
	
	
	bool load( processor_state& s, op_params& pb )
	{
		bool ok = true;
		
		const int32_t target = pb.target;
		
		if ( target >= 0 )
		{
			pb.second = s.regs.d[ target ];
			
			if ( target > 7 )
			{
				// address register, don't sign-extend
				return true;
			}
		}
		else
		{
			const uint32_t addr = pb.address;
			
			uint8_t   byte;
			uint16_t  word;
			
			switch ( pb.size )
			{
				case byte_sized:
					ok = s.mem.get_byte( addr, byte, s.data_space() );
					
					pb.second = byte;
					
					break;
				
				case word_sized:
					ok = s.mem.get_word( addr, word, s.data_space() );
					
					pb.second = word;
					
					break;
				
				case long_sized:
					ok = s.mem.get_long( addr, pb.second, s.data_space() );
					
					break;
				
				default:
					break;
			}
		}
		
		pb.second = sign_extend( pb.second, pb.size );
		
		return ok;
	}
	
	bool store( processor_state& s, const op_params& pb, int flags )
	{
		uint32_t data = pb.result;
		
		if ( !(flags & stores_data) )
		{
			return true;
		}
		
		const int32_t target = pb.target;
		
		if ( target > 7 )
		{
			// Address register:  don't touch CCR
			
			s.regs.d[ target ] = data;
			
			return true;
		}
		
		if ( flags & and_sets_CCR )
		{
			// CCR is already set
		}
		else
		{
			const int32_t signed_data = sign_extend( data, pb.size );
			
			s.regs.nzvc = N( signed_data <  0 )
			            | Z( signed_data == 0 )
			            | V( 0 )
			            | C( 0 );
		}
		
		if ( target >= 0 )
		{
			s.regs.d[ target ] = update( s.regs.d[ target ], data, pb.size );
			
			return true;
		}
		
		// destination is a memory address
		
		const uint32_t addr = pb.address;
		
		switch ( pb.size )
		{
			case byte_sized:  return s.mem.put_byte( addr, data, s.data_space() );
			case word_sized:  return s.mem.put_word( addr, data, s.data_space() );
			case long_sized:  return s.mem.put_long( addr, data, s.data_space() );
			
			default:
				break;
		}
		
		return true;
	}
	
}

