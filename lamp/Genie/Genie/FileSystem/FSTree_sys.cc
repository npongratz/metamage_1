/*	=============
 *	FSTree_sys.cc
 *	=============
 */

#include "Genie/FileSystem/FSTree_sys.hh"

// Nucleus
#include "Nucleus/ArrayContainerFunctions.h"

// Nitrogen
#include "Nitrogen/Gestalt.h"
#include "Nitrogen/Processes.h"

// POSeven
#include "POSeven/Errno.hh"

// Genie
#include "Genie/FileSystem/FSTree_Directory.hh"
#include "Genie/FileSystem/FSTree_sys_mac.hh"
#include "Genie/FileSystem/FSTree_sys_set.hh"
#include "Genie/IO/Base.hh"
#include "Genie/IO/Device.hh"
#include "Genie/IO/MemoryFile.hh"
#include "Genie/SystemCallRegistry.hh"


namespace Genie
{
	
	namespace N = Nitrogen;
	namespace NN = Nucleus;
	namespace p7 = poseven;
	
	
	typedef const SystemCall* SystemCallPtr;
	
	struct SystemCall_KeyName_Traits
	{
		typedef SystemCallPtr Key;
		
		static std::string NameFromKey( const Key& key )
		{
			return key->name ? key->name
			                 : "." + Pointer_KeyName_Traits< SystemCallPtr >::NameFromKey( key );
		}
		
		static Key CheckKey( Key key )
		{
			if ( key == NULL )  p7::throw_errno( ENOENT );
			
			return key;
		}
		
		static Key KeyFromName( const std::string& name )
		{
			return CheckKey( LookUpSystemCallByName( name.c_str() ) );
		}
	};
	
	
	class FSTree_sys_kernel_bin_EXE : public FSTree
	{
		private:
			typedef int (*Main0)();
			typedef int (*Main2)( int argc, char const *const *argv );
			typedef int (*Main3)( int argc, char const *const *argv, char const *const *envp );
			
			MainEntry itsMainEntry;
		
		public:
			FSTree_sys_kernel_bin_EXE( const FSTreePtr&    parent,
			                           const std::string&  name,
			                           Main3               main ) : FSTree( parent, name ),
			                                                        itsMainEntry( GetMainEntryFromAddress( main ) )
			{
			}
			
			FSTree_sys_kernel_bin_EXE( const FSTreePtr&    parent,
			                           const std::string&  name,
			                           Main2               main ) : FSTree( parent, name ),
			                                                        itsMainEntry( GetMainEntryFromAddress( main ) )
			{
			}
			
			FSTree_sys_kernel_bin_EXE( const FSTreePtr&    parent,
			                           const std::string&  name,
			                           Main0               main ) : FSTree( parent, name ),
			                                                        itsMainEntry( GetMainEntryFromAddress( main ) )
			{
			}
			
			mode_t FilePermMode() const  { return S_IRUSR | S_IXUSR; }
			
			MainEntry GetMainEntry() const  { return itsMainEntry; }
	};
	
	
	struct sys_kernel_syscall_Details : public SystemCall_KeyName_Traits
	{
		typedef SystemCallRegistry Sequence;
		
		static const Sequence& ItemSequence()  { return GetSystemCallRegistry(); }
		
		static Key KeyFromValue( const Sequence::value_type& value )  { return &value; }
		
		static bool KeyIsValid( const Key& key )
		{
			return key != NULL;
		}
		
		FSTreePtr GetChildNode( const FSTreePtr&    parent,
		                        const std::string&  name,
		                        const Key&          key ) const;
	};
	
	typedef FSTree_Sequence< sys_kernel_syscall_Details > FSTree_sys_kernel_syscall;
	
	
	namespace
	{
		
		int main_true()
		{
			return 0;
		}
		
		int main_false()
		{
			return 1;
		}
		
		int main_beep()
		{
			N::SysBeep();
			
			return 0;
		}
		
	}
	
	template < int (*main)() >
	static FSTreePtr Executable_Factory( const FSTreePtr&    parent,
	                                     const std::string&  name )
	{
		return MakeFSTree( new FSTree_sys_kernel_bin_EXE( parent, name, main ) );
	}
	
	extern const Singleton_Mapping sys_kernel_bin_Mappings[];
	
	const Singleton_Mapping sys_kernel_bin_Mappings[] =
	{
		{ "true",  &Executable_Factory< main_true  > },
		{ "false", &Executable_Factory< main_false > },
		
		{ "beep", &Executable_Factory< main_beep > },
		
		{ NULL, NULL }
	};
	
	
	extern const Singleton_Mapping sys_kernel_Mappings[];
	
	const Singleton_Mapping sys_kernel_Mappings[] =
	{
		{ "bin",     &Premapped_Factory< sys_kernel_bin_Mappings > },
		
		{ "syscall", &Singleton_Factory< FSTree_sys_kernel_syscall > },
		
		{ NULL, NULL }
	};
	
	static const Singleton_Mapping sys_Mappings[] =
	{
		{ "kernel", &Premapped_Factory< sys_kernel_Mappings > },
		{ "mac",    &Premapped_Factory< sys_mac_Mappings    > },
		{ "set",    &Premapped_Factory< sys_set_Mappings    > }
	};
	
	void FSTree_sys::Init()
	{
		AddMappings( sys_Mappings, NN::ArrayEnd( sys_Mappings ) );
	}
	
	
	FSTreePtr sys_kernel_syscall_Details::GetChildNode( const FSTreePtr&    parent,
		                                                const std::string&  name,
		                                                const Key&          key ) const
	{
		return MakeFSTree( new FSTree_Functional< Key >( parent, name, key ) );
	}
	
}

