/*
	Resources.cc
	------------
*/

#include "Resources.hh"

// Mac OS
#ifndef __MACMEMORY__
#include <MacMemory.h>
#endif

// Standard C
#include <string.h>

// Standard C++
#include <new>

// gear
#include "gear/hexadecimal.hh"

// plus
#include "plus/var_string.hh"

// freemount-client
#include "freemount/synced.hh"

// ams-common
#include "FCB.hh"
#include "module_A4.hh"


#define STRLEN( s )  (sizeof "" s - 1)
#define STR_LEN( s )  "" s, (sizeof s - 1)
#define PSTR_LEN( s )  "\p" s, (sizeof s - 1)


short MemErr    : 0x0220;
Str31 CurApName : 0x0910;
short CurMap    : 0x0A5A;
short ResErr    : 0x0A60;

const short memFullErr  = -108;
const short resNotFound = -192;

pascal void RsrcZoneInit_patch()
{
	FCBSPtr->fcbs[ 0 ].fcbFlNum = -1;  // claim for System resource fork
	FCBSPtr->fcbs[ 1 ].fcbFlNum = -1;  // claim for application resource fork
	
	// CurApRefNum is automatically fixed at 2
	const short CurApRefNum = 2;
	
	CurMap = CurApRefNum;
}

pascal short ResError_patch()
{
	return ResErr;
}

pascal short CurResFile_patch()
{
	return CurMap;
}

pascal void UseResFile_patch( short refnum )
{
	CurMap = refnum;
}

static
bool try_to_get( const char* begin, const char* end, plus::var_string& data )
{
	plus::string path( begin, end - begin, plus::delete_never );
	
	try
	{
		namespace F = freemount;
		
		const int in  = 6;
		const int out = 7;
		
		data = F::synced_get( in, out, path ).move();
		
		return true;
	}
	catch ( const std::bad_alloc& )
	{
		ResErr = memFullErr;
	}
	catch ( ... )
	{
		ResErr = resNotFound;
	}
	
	return false;
}

static
bool try_to_get( char*              insert_end,
                 char*              end,
                 const char*        name,
                 size_t             len,
                 plus::var_string&  result )
{
	char* begin = insert_end - len;
	
	memcpy( begin, name, len );
	
	return try_to_get( begin, end, result );
}

static
Handle GetResource_core( ResType type : __D0, short id : __D1 )
{
	/*
		The app name can only be 31 bytes (not 32), but with the extra byte,
		"TYPE" is word-aligned.
	*/
	
	char tmp_path[] = "1234567890" "1234567890" "1234567890" "12/r/1234.TYPE";
	
	char* const end      = tmp_path + sizeof tmp_path - 1;
	char* const name_end = tmp_path + 32;
	
	char* p = end - STRLEN( "1234.TYPE" );
	
	gear::encode_16_bit_hex( id, name_end + STRLEN( "/r/" ) );
	
	p += 5;
	
	*(ResType*) p = type;
	
	plus::var_string rsrc;
	
	Handle result = 0;  // NULL
	
	bool got = false;
	
	if ( CurApName[ 0 ] != '\0' )
	{
		const size_t len = CurApName[ 0 ];
		
		got = try_to_get( name_end, end, (char*) CurApName + 1, len, rsrc );
	}
	
	if ( ! got )
	{
		got = try_to_get( name_end, end, STR_LEN( "System" ), rsrc );
	}
	
	if ( ! got )
	{
		got = try_to_get( name_end, end, STR_LEN( "AMS Resources" ), rsrc );
	}
	
	if ( ! got )
	{
		// ResErr is already set.
		return result;
	}
	
	const unsigned long size = rsrc.size();
	
	result = NewHandle( size );
	
	if ( result == 0 )  // NULL
	{
		ResErr = MemErr;
		return result;
	}
	
	memcpy( *result, rsrc.data(), size );
	
	ResErr = noErr;
	
	return result;
}

static
Handle GetResource_handler( ResType type : __D0, short id : __D1 )
{
	temp_A4 a4;
	
	return GetResource_core( type, id );
}

asm
pascal Handle GetResource_patch( ResType type, short id )
{
	MOVEM.L  D1-D2/A1-A2,-(SP)
	
	LEA      20(SP),A2
	MOVE.W   (A2)+,D1
	MOVE.L   (A2)+,D0
	
	JSR      GetResource_handler
	MOVE.L   A0,(A2)
	
	MOVEM.L  (SP)+,D1-D2/A1-A2
	
	MOVEA.L  (SP)+,A0
	
	ADDQ.L   #6,SP
	
	JMP      (A0)
}

static
Handle GetNamedResource_handler( ResType type : __D0, const UInt8* name : __A0 )
{
	if ( type == 'SCOT'  &&  memcmp( name, PSTR_LEN( "Terry" ) + 1 ) == 0 )
	{
		return GetResource_handler( type, 1 );
	}
	
	if ( type == 'ANDY'  &&  memcmp( name, PSTR_LEN( "Gariepy" ) + 1 ) == 0 )
	{
		return GetResource_handler( type, 1 );
	}
	
	ResErr = resNotFound;
	
	return 0;  // NULL
}

asm
pascal Handle GetNamedResource_patch( ResType type, ConstStr255Param name )
{
	MOVEM.L  D1-D2/A1-A2,-(SP)
	
	LEA      20(SP),A2
	MOVEA.L  (A2)+,A0
	MOVE.L   (A2)+,D0
	
	JSR      GetNamedResource_handler
	MOVE.L   A0,(A2)
	
	MOVEM.L  (SP)+,D1-D2/A1-A2
	
	MOVEA.L  (SP)+,A0
	
	ADDQ.L   #8,SP
	
	JMP      (A0)
}

pascal void ReleaseResource_patch( Handle resource )
{
	DisposeHandle( resource );
}

pascal void DetachResource_patch( Handle resource )
{
}

pascal long SizeRsrc_patch( Handle resource )
{
	return GetHandleSize( resource );
}
