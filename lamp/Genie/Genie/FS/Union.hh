/*
	Union.hh
	--------
	
	Copyright 2010, Joshua Juran
*/

#ifndef GENIE_FS_UNION_HH
#define GENIE_FS_UNION_HH

// Genie
#include "Genie/FS/FSTree.hh"


namespace Genie
{
	
	class FSTree_Union : public FSTree
	{
		private:
			FSTreePtr itsTop;
			FSTreePtr itsBottom;
		
		public:
			FSTree_Union( const FSTreePtr&     parent,
			              const plus::string&  name );
			
			void SetTop( const FSTreePtr& top )
			{
				itsTop = top;
			}
			
			void SetBottom( const FSTreePtr& bottom )
			{
				itsBottom = bottom;
			}
			
			FSTreePtr Lookup_Child( const plus::string& name, const FSTree* parent ) const;
			
			void IterateIntoCache( FSTreeCache& cache ) const;
	};
	
}

#endif

