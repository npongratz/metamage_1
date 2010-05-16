/*	====================
 *	IncrementalSearch.hh
 *	====================
 */

#ifndef PEDESTAL_INCREMENTALSEARCH_HH
#define PEDESTAL_INCREMENTALSEARCH_HH

// Standard C++
#include <vector>

// plus
#include "plus/var_string.hh"

// Pedestal
#include "Pedestal/Quasimode.hh"


namespace Pedestal
{
	
	struct TextSelection
	{
		unsigned  start;
		unsigned  end;
		
		TextSelection() : start(), end()
		{
		}
		
		bool defined() const  { return int( start ) >= 0; }
		
		void undefine()  { start = unsigned( -1 ); }
	};
	
	inline bool operator==( const TextSelection& a, const TextSelection& b )
	{
		return a.start == b.start  &&  a.end == b.end;
	}
	
	inline bool operator!=( const TextSelection& a, const TextSelection& b )
	{
		return !( a == b );
	}
	
	
	short TextSearch( const char*           text,
	                  std::size_t           text_length,
	                  const char*           pattern,
	                  std::size_t           pattern_length,
	                  const TextSelection&  selection,
	                  bool                  backward,
	                  bool                  matchAtPosition );
	
	
	class IncrementalSearchEditor
	{
		public:
			virtual void BeginQuasimode() = 0;
			virtual void EndQuasimode() = 0;
			
			virtual TextSelection GetCurrentSelection() const = 0;
			
			virtual void Select( unsigned start, unsigned end ) = 0;
			
			void SetCurrentSelection( const TextSelection& selection )
			{
				Select( selection.start, selection.end );
			}
			
			virtual TextSelection GetPriorSelection() const = 0;
			
			virtual void SetPriorSelection( const TextSelection& selection ) = 0;
			
			void AugmentSelection();
			
			virtual int Search( const char*           pattern,
			                    std::size_t           pattern_length,
			                    const TextSelection&  selection,
			                    bool                  searchBackwards,
			                    bool                  matchAtPosition ) const = 0;
	};
	
	
	void ResetArrowKeyChordability();
	
	bool Try_ArrowKeyChord( IncrementalSearchEditor& editor, char c );
	
	
	const plus::string& GetLastSearchPattern();
	
	class IncrementalSearchQuasimode : public Quasimode
	{
		private:
			IncrementalSearchEditor&      itsView;
			bool                          itSearchesBackward;
			unsigned short                itsModifierMask;
			TextSelection                 itsSavedSelection;
			std::vector< TextSelection >  itsMatches;
			plus::var_string              itsPattern;
		
		public:
			IncrementalSearchQuasimode( IncrementalSearchEditor& editor, bool backward );
			
			~IncrementalSearchQuasimode();
			
			bool KeyDown( const EventRecord& event );
	};
	
	bool Try_RepeatSearch( IncrementalSearchEditor& editor, const EventRecord& event );
	
}

#endif

