/*	==============
 *	BinaryImage.cc
 *	==============
 */

#include "Genie/BinaryImage.hh"

// Nitrogen
#include "Nitrogen/Files.h"

// Io
#include "io/slurp.hh"


namespace Nucleus
{
	
	template <>
	struct Converter< Owned< Nitrogen::Ptr >, Nitrogen::Handle >: public std::unary_function< Nitrogen::Handle, Owned< Nitrogen::Ptr > >
	{
		Owned< Nitrogen::Ptr > operator()( const Nitrogen::Handle& h ) const
		{
			Nitrogen::Size size = Nitrogen::GetHandleSize( h );
			
			Owned< Nitrogen::Ptr > result = Nitrogen::NewPtr( size );
			
			std::copy( *h.Get(), *h.Get() + size, result.Get().Get() );
			
			return result;
		}
	};
	
}

namespace Genie
{
	
	namespace N = Nitrogen;
	namespace NN = Nucleus;
	
	struct BinaryFileMetadata
	{
		UInt32 dataForkLength;
		UInt32 creationDate;
		UInt32 modificationDate;
		UInt32 fileID;
		
		BinaryFileMetadata()  {}
		
		BinaryFileMetadata( const HFileInfo& hFileInfo ) : dataForkLength  ( hFileInfo.ioFlLgLen ),
		                                                   creationDate    ( hFileInfo.ioFlCrDat ),
		                                                   modificationDate( hFileInfo.ioFlMdDat ),
		                                                   fileID          ( hFileInfo.ioDirID   )
		{
		}
		
		friend bool operator==( const BinaryFileMetadata& a, const BinaryFileMetadata& b )
		{
			return    a.dataForkLength   == b.dataForkLength
			       && a.creationDate     == b.creationDate
			       && a.modificationDate == b.modificationDate
			       && a.fileID           == b.fileID;
		}
		
		friend bool operator!=( const BinaryFileMetadata& a, const BinaryFileMetadata& b )
		{
			return !( a == b );
		}
	};
	
	struct BinaryImageCacheEntry
	{
		//BinaryImage         image;
		NN::Shared< N::Ptr >  image;
		BinaryFileMetadata   metadata;
	};
	
	template < class T > static int cmp( const T& a, const T& b )
	{
		return   a < b ? -1
		       : b < a ? +1
		       :          0;
	}
	
	static int less_PascalStrings( const unsigned char* a, const unsigned char* b )
	{
		return std::lexicographical_compare( a + 1, a + 1 + a[0], b + 1, b + 1 + b[0] );
	}
	
	struct less_FSSpecs
	{
		bool operator()( const FSSpec& a, const FSSpec& b ) const
		{
			return   a.vRefNum != b.vRefNum ? a.vRefNum > b.vRefNum  // -1 before -2
			       : a.parID   != b.parID   ? a.parID   < b.parID
			       :                          less_PascalStrings( a.name, b.name );
		}
	};
	
	typedef std::map< FSSpec, BinaryImageCacheEntry, less_FSSpecs > BinaryImageCache;
	
	static BinaryImageCache gBinaryImageCache;
	
	static BinaryFileMetadata GetFileMetadata( const FSSpec& file )
	{
		CInfoPBRec pb;
		
		N::FSpGetCatInfo( file, pb );
		
		return BinaryFileMetadata( pb.hFileInfo );
	}
	
	inline NN::Owned< N::Ptr > ReadImageFromResource( const FSSpec& file, N::ResType type, N::ResID id )
	{
		NN::Owned< N::ResFileRefNum > resFile = N::FSpOpenResFile( file, N::fsRdPerm );
		
		return NN::Convert< NN::Owned< N::Ptr > >( N::Get1Resource( type, id ) );
	}
	
	inline NN::Owned< N::Ptr > ReadImageFromFile( const FSSpec& file )
	{
		const bool rsrc = TARGET_CPU_68K && !TARGET_RT_MAC_CFM;
		
		return rsrc ? ReadImageFromResource( file, N::ResType( 'Wish' ), N::ResID( 0 ) )
		            : io::slurp_file< N::PtrFlattener >( file );
	}
	
	NN::Shared< N::Ptr > GetBinaryImage( const FSSpec& file )
	{
		if ( TARGET_CPU_68K )
		{
			// Can't share code resources among threads, so don't bother caching it
			return ReadImageFromFile( file );
		}
		
		BinaryFileMetadata metadata = GetFileMetadata( file );
		
		BinaryImageCache::iterator it = gBinaryImageCache.find( file );
		
		BinaryImageCacheEntry* cacheEntry = NULL;
		
		// Do we have a cached image for this binary?
		if ( it != gBinaryImageCache.end() )
		{
			cacheEntry = &it->second;
			
			// Do the metadata match?
			if ( cacheEntry->metadata == metadata )
			{
				return cacheEntry->image;  // Yup, we're done
			}
		}
		else
		{
			cacheEntry = &gBinaryImageCache[ file ];  // insert null cache entry
		}
		
		BinaryImageCacheEntry newEntry;
		
		newEntry.metadata = metadata;
		newEntry.image    = ReadImageFromFile( file );
		
		// Install the new cache entry
		*cacheEntry = newEntry;
		
		return newEntry.image;
	}
	
}

