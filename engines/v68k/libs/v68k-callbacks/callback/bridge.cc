/*
	bridge.cc
	---------
*/

#include "callback/bridge.hh"

// POSIX
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// Standard C
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// must
#include "must/write.h"

// v68k-alloc
#include "v68k-alloc/memory.hh"

// v68k-auth
#include "auth/auth.hh"


#pragma exceptions off


#define ERR_MSG( msg )  "v68k: exception: " msg "\n"

#define STRLEN( s )  (sizeof "" s - 1)

#define STR_LEN( s )  "" s, (sizeof s - 1)

#define WRITE_ERR( msg )  must_write( STDERR_FILENO, STR_LEN( ERR_MSG( msg ) ) )


namespace v68k     {
namespace callback {

using v68k::auth::fully_authorized;


enum
{
	rts = 0x4E75,
	nil = 0
};

typedef uint32_t (*function_type)( v68k::processor_state& s );


static uint32_t unimplemented_callback( v68k::processor_state& s )
{
	abort();
	
	// Not reached
	return nil;
}

static uint32_t no_op_callback( v68k::processor_state& s )
{
	return rts;
}

static uint32_t load_callback( v68k::processor_state& s )
{
	const uint32_t path_addr = s.regs.a[0];
	const uint32_t path_size = s.regs.d[0];  // includes trailing NUL
	
	s.regs.a[0] = 0;
	
	if ( !fully_authorized )
	{
		s.regs.d[1] = EPERM;
		
		return rts;
	}
	
	const uint8_t* p = s.mem.translate( path_addr,
	                                    path_size,
	                                    v68k::user_data_space,
	                                    v68k::mem_read );
	
	if ( p == NULL )
	{
		s.regs.d[1] = EFAULT;
		
		return rts;
	}
	
	if ( path_size == 0  ||  p[0] == '\0'  ||  p[ path_size - 1 ] != '\0' )
	{
		s.regs.d[1] = EINVAL;
		
		return rts;
	}
	
	const char* path = (const char*) p;
	
	int fd = open( path, O_RDONLY );
	
	if ( fd < 0 )
	{
		s.regs.d[1] = errno;
		
		return rts;
	}
	
	struct stat sb;
	
	int err = fstat( fd, &sb );
	
	if ( err < 0 )
	{
		s.regs.d[1] = errno;
	}
	else
	{
		const size_t file_size = sb.st_size;
		
		using v68k::alloc::page_size;
		using v68k::alloc::page_size_bits;
		using v68k::alloc::allocate_n_pages;
		using v68k::alloc::deallocate;
		
		const size_t n = (file_size + page_size - 1) >> page_size_bits;  // round up
		
		void* alloc = calloc( n, page_size );
		
		const uint32_t addr = allocate_n_pages( alloc, n );
		
		if ( addr == 0 )
		{
			free( alloc );
			
			s.regs.d[1] = ENOMEM;
		}
		else
		{
			const ssize_t n_read = read( fd, alloc, file_size );
			
			if ( n_read != file_size )
			{
				deallocate( addr );  // frees alloc also
				
				s.regs.d[1] = n_read < 0 ? errno : EIO;
			}
			else
			{
				s.regs.d[0] = n_read;
				s.regs.a[0] = addr;
			}
		}
	}
	
	close( fd );
	
	return rts;
}

static char hex[] =
{
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'A', 'B',
	'C', 'D', 'E', 'F'
};

#define UNIMPLEMENTED_TRAP_PREFIX  "v68k: exception: Unimplemented Mac trap: "

static uint32_t unimplemented_trap_callback( v68k::processor_state& s )
{
	static char buffer[] = UNIMPLEMENTED_TRAP_PREFIX "A123\n";
	
	char* p = buffer + STRLEN( UNIMPLEMENTED_TRAP_PREFIX );
	
	const uint16_t trap = s.regs.d[1];
	
	p[1] = hex[ trap >> 8 & 0xF ];
	p[2] = hex[ trap >> 4 & 0xF ];
	p[3] = hex[ trap      & 0xF ];
	
	must_write( STDERR_FILENO, buffer, STRLEN( UNIMPLEMENTED_TRAP_PREFIX "A123\n" ) );
	
	raise( SIGILL );
	
	// Not reached
	return nil;
}

static uint32_t NewPtr_callback( v68k::processor_state& s )
{
	const uint32_t size = s.regs.d[0];
	
	uint32_t addr = v68k::alloc::allocate( size );
	
	s.regs.a[0] = addr;
	
	if ( addr == 0 )
	{
		const uint32_t addr_MemErr = 0x0220;
		
		const int16_t memFullErr = -108;
		
		s.mem.put_word( addr_MemErr, memFullErr, v68k::user_data_space );
	}
	
	return rts;
}

static uint32_t DisposePtr_callback( v68k::processor_state& s )
{
	const uint32_t addr = s.regs.a[0];
	
	v68k::alloc::deallocate( addr );
	
	return rts;
}

static uint32_t BlockMove_callback( v68k::processor_state& s )
{
	const uint32_t src = s.regs.a[0];
	const uint32_t dst = s.regs.a[1];
	
	const uint32_t n = s.regs.d[0];
	
	const uint8_t* p = s.mem.translate( src, n, v68k::user_data_space, v68k::mem_read );
	
	if ( p == NULL )
	{
		abort();
		return nil;  // FIXME
	}
	
	uint8_t* q = s.mem.translate( dst, n, v68k::user_data_space, v68k::mem_write );
	
	if ( q == NULL )
	{
		abort();
		return nil;  // FIXME
	}
	
	memcpy( q, p, n );
	
	s.mem.translate( dst, n, v68k::user_data_space, v68k::mem_update );
	
	return rts;
}

static uint32_t Gestalt_callback( v68k::processor_state& s )
{
	const int32_t gestaltUndefSelectorErr = -5551;
	
	const uint32_t selector = s.regs.d[0];
	
	uint32_t value = 0;
	int32_t result = 0;
	
	switch ( selector )
	{
		case 'v68k':
		//	value = 0;
			break;
		
		case 'proc':
			value = (s.model >> 8) + 1;
			break;
		
		default:
			result = gestaltUndefSelectorErr;
			break;
	}
	
	s.regs.d[0] = result;
	s.regs.a[0] = value;
	
	return rts;
}


static uint32_t illegal_instruction_callback( v68k::processor_state& s )
{
	WRITE_ERR( "Illegal Instruction" );
	
	raise( SIGILL );
	
	return nil;
}

static uint32_t division_by_zero_callback( v68k::processor_state& s )
{
	WRITE_ERR( "Division By Zero" );
	
	raise( SIGFPE );
	
	return nil;
}

static uint32_t chk_trap_callback( v68k::processor_state& s )
{
	WRITE_ERR( "CHK range exceeded" );
	
	raise( SIGFPE );
	
	return nil;
}

static uint32_t trapv_trap_callback( v68k::processor_state& s )
{
	WRITE_ERR( "TRAPV on overflow" );
	
	raise( SIGFPE );
	
	return nil;
}

static uint32_t privilege_violation_callback( v68k::processor_state& s )
{
	WRITE_ERR( "Privilege Violation" );
	
	raise( SIGILL );
	
	return nil;
}

static uint32_t trace_exception_callback( v68k::processor_state& s )
{
	WRITE_ERR( "Trace Exception" );
	
	raise( SIGTRAP );
	
	return nil;
}

static uint32_t line_A_emulator_callback( v68k::processor_state& s )
{
	WRITE_ERR( "Line A Emulator" );
	
	raise( SIGILL );
	
	return nil;
}

static uint32_t line_F_emulator_callback( v68k::processor_state& s )
{
	WRITE_ERR( "Line F Emulator" );
	
	raise( SIGILL );
	
	return nil;
}


static const function_type the_callbacks[] =
{
	&unimplemented_callback,
	&load_callback,
	&illegal_instruction_callback,
	&division_by_zero_callback,
	&chk_trap_callback,
	&trapv_trap_callback,
	&privilege_violation_callback,
	&trace_exception_callback,
	&line_A_emulator_callback,
	&line_F_emulator_callback,
	&unimplemented_trap_callback,
	&NewPtr_callback,
	&DisposePtr_callback,
	&BlockMove_callback,
	&Gestalt_callback,
	&no_op_callback
};


uint32_t bridge( v68k::processor_state& s )
{
	const int32_t pc = s.regs.pc;
	
	const uint32_t call_number = pc / -2 - 1;
	
	const size_t n_callbacks = sizeof the_callbacks / sizeof the_callbacks[0];
	
	if ( call_number < n_callbacks )
	{
		const function_type f = the_callbacks[ call_number ];
		
		if ( f != NULL )
		{
			return f( s );
		}
	}
	
	return nil;
}

}  // namespace v68k
}  // namespace callback

