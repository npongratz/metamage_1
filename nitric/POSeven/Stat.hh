// Stat.hh
// -------
//
// Maintained by Joshua Juran

// Part of the Nitrogen project.
//
// Written 2007 by Joshua Juran.
//
// This code was written entirely by the above contributor, who places it
// in the public domain.


#ifndef POSEVEN_STAT_HH
#define POSEVEN_STAT_HH

// Standard C++
#include <string>

// POSIX
#include <sys/stat.h>

// Io
#include "io/io.hh"

// POSeven
#include "POSeven/Errno.hh"
#include "POSeven/FileDescriptor.hh"
#include "POSeven/functions/mkdir.hh"


namespace poseven
{
	
	inline void chmod( const char* pathname, mode_t mode )
	{
		throw_posix_result( ::chmod( pathname, mode ) );
	}
	
	inline void chmod( const std::string& pathname, mode_t mode )
	{
		chmod( pathname.c_str(), mode );
	}
	
	inline void fchmod( fd_t fd, mode_t mode )
	{
		throw_posix_result( ::fchmod( fd, mode ) );
	}
	
	inline struct stat fstat( fd_t fd )
	{
		struct stat sb;
		
		throw_posix_result( ::fstat( fd, &sb ) );
		
		return sb;
	}
	
	inline void mkfifo( const char* pathname, mode_t mode )
	{
		throw_posix_result( ::mkfifo( pathname, mode ) );
	}
	
	inline void mkfifo( const std::string& pathname, mode_t mode )
	{
		mkfifo( pathname.c_str(), mode );
	}
	
	inline bool stat( const char* pathname, struct stat& sb )
	{
		int status = ::stat( pathname, &sb );
		
		if ( status == -1 )
		{
			if ( errno == ENOENT )
			{
				return false;
			}
			
			throw_errno( errno );
		}
		
		return true;
	}
	
	inline struct stat stat( const char* pathname )
	{
		struct stat sb;
		
		throw_posix_result( ::stat( pathname, &sb ) );
		
		return sb;
	}
	
	inline bool stat( const std::string& pathname, struct stat& sb )
	{
		return stat( pathname.c_str(), sb );
	}
	
	inline struct stat stat( const std::string& pathname )
	{
		return stat( pathname.c_str() );
	}
	
	inline bool lstat( const char* pathname, struct stat& sb )
	{
		int status = ::lstat( pathname, &sb );
		
		if ( status == -1 )
		{
			if ( errno == ENOENT )
			{
				return false;
			}
			
			throw_errno( errno );
		}
		
		return true;
	}
	
	inline struct stat lstat( const char* pathname )
	{
		struct stat sb;
		
		throw_posix_result( ::lstat( pathname, &sb ) );
		
		return sb;
	}
	
	inline bool lstat( const std::string& pathname, struct stat& sb )
	{
		return lstat( pathname.c_str(), sb );
	}
	
	inline struct stat lstat( const std::string& pathname )
	{
		return lstat( pathname.c_str() );
	}
	
}

namespace io
{
	
	// Existence
	
	inline bool item_exists( const char* item )
	{
		struct ::stat sb;
		
		return poseven::stat( item, sb );
	}
	
	inline bool item_exists( const std::string& item )
	{
		return item_exists( item.c_str() );
	}
	
	
	inline bool item_is_file( const struct ::stat& sb )
	{
		return S_ISREG( sb.st_mode );
	}
	
	inline bool item_is_directory( const struct ::stat& sb )
	{
		return S_ISDIR( sb.st_mode );
	}
	
	
	inline bool file_exists( const char* item )
	{
		struct ::stat sb;
		
		return poseven::stat( item, sb ) && item_is_file( sb );
	}
	
	inline bool file_exists( const std::string& item )
	{
		return file_exists( item.c_str() );
	}
	
	
	inline bool directory_exists( const char* item )
	{
		struct ::stat sb;
		
		return poseven::stat( item, sb ) && item_is_directory( sb );
	}
	
	inline bool directory_exists( const std::string& item )
	{
		return directory_exists( item.c_str() );
	}
	
	inline std::size_t get_file_size( poseven::fd_t stream, overload = overload() )
	{
		struct stat status = poseven::fstat( stream );
		
		if ( !S_ISREG( status.st_mode ) )
		{
			poseven::throw_errno( ESPIPE );
		}
		
		return status.st_size;
	}
	
}

#endif

