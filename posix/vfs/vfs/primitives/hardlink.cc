/*
	hardlink.cc
	-----------
*/

#include "vfs/primitives/hardlink.hh"

// poseven
#include "poseven/types/errno_t.hh"

// vfs
#include "vfs/node.hh"
#include "vfs/functions/access.hh"
#include "vfs/methods/file_method_set.hh"
#include "vfs/methods/node_method_set.hh"
#include "vfs/primitives/parent.hh"


namespace vfs
{
	
	namespace p7 = poseven;
	
	
	void hardlink( const node& that, const node& target )
	{
		access( *parent( target ), W_OK );
		
		const node_method_set* methods = that.methods();
		
		const file_method_set* file_methods;
		
		if ( methods  &&  (file_methods = methods->file_methods) )
		{
			if ( file_methods->hardlink )
			{
				file_methods->hardlink( &that, &target );
				
				return;
			}
		}
		
		p7::throw_errno( EINVAL );
	}
	
}
