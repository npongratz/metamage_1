/*	==========
 *	MenuBar.cc
 *	==========
 */

#include "Pedestal/MenuBar.hh"

// Mac OS
#ifdef __APPLE_CC__
	#include <Carbon/Carbon.h>
#else
	#include <ToolUtils.h>
	#include <Devices.h>
#endif

// Nitrogen
#include "Nitrogen/Scoped.h"

// Pedestal
#include "Pedestal/MenuItemCode.hh"


namespace Nitrogen
{
	
#if CALL_NOT_IN_CARBON
	
	static void OpenDeskAcc( ConstStr255Param name )
	{
		Scoped< GrafPtr& >( Port() );

		::OpenDeskAcc( name );
	}
	
#endif
	
}

namespace Pedestal
{
	
	struct UnhighlightMenus
	{
		void operator()() const  { N::HiliteMenu(); }
	};
	
	template < class Func >
	class AtEnd
	{
		public:
			AtEnd( const Func& func = Func() ) : func( func )  {}
			~AtEnd()                                           { func(); }
		
		private:
			Func func;
	};
	
	static MenuItemCode TakeCodeFromItemText( Str255 ioItemText )
	{
		int len = ioItemText[ 0 ];
		
		if ( len < 7 )  return 0;
		if ( ioItemText[ len ] != ']' )  return 0;
		if ( ioItemText[ len - 5 ] != '[' )  return 0;
		
		MenuItemCode code = *reinterpret_cast< MenuItemCode* >( &ioItemText[ len - 4 ] );
		ioItemText[ 0 ] -= 7;
		
		return code;
	}
	
	static MenuItemCode ExtractItemCmdCode( MenuRef menu, short item )
	{
		N::Str255 itemText = N::GetMenuItemText( menu, item );
		MenuItemCode code = TakeCodeFromItemText( itemText );
		if ( code != 0 )
		{
			N::SetMenuItemText( menu, item, itemText );
		}
		
		return code;
	}
	
	static void ExtractCmdCodes( MenuRef menu, std::vector< MenuItemCode >& outCodes )
	{
		short count = N::CountMenuItems( menu );
		outCodes.resize( 1 + count );  // slot 0 is unused
		for ( short i = count;  i > 0;  i-- )
		{
			outCodes[ i ] = ExtractItemCmdCode( menu, i );
		}
	}
	
	MenuBar::MenuBar( const MenuItemHandler& handler )
	:
		handler    ( handler ), 
		appleMenuID()
	{
		N::InvalMenuBar();
	}
	
	void MenuBar::AddMenu( N::MenuID menuID )
	{
		MenuRef menu = N::GetMenuRef( menuID );
		
		ExtractCmdCodes( menu, myMenus[ menuID ] );
	}
	
	enum
	{
		kDeskAccessoryResourceType = 'DRVR'
	};
	
	void MenuBar::AddAppleMenu( N::MenuID menuID )
	{
		AddMenu( menuID );
		
		appleMenuID = menuID;
		
		N::AppendResMenu( N::GetMenuRef( menuID ), kDeskAccessoryResourceType );
	}
	
	void MenuBar::ProcessMenuItem( N::MenuID menuID, SInt16 item )
	{
		AtEnd< UnhighlightMenus > unhighlightMenus;
		
		Menus::const_iterator it = myMenus.find( menuID );
		
		if ( it != myMenus.end() )
		{
			const std::vector< MenuItemCode >& commands = it->second;
			
			if ( item < commands.size() )
			{
				MenuItemCode code = commands[ item ];
				
				if ( code != 0 )
				{
					handler.Run( code );
				}
			}
			
		#if CALL_NOT_IN_CARBON
			
			else if ( menuID == appleMenuID )
			{
				N::OpenDeskAcc( N::GetMenuItemText( N::GetMenuRef( menuID ), item ) );
			}
			
		#endif
		}
	}
	
	void MenuBar::ProcessMenuItem( int menuItem )
	{
		N::MenuID menuID = HiWord( menuItem );
		SInt16    item   = LoWord( menuItem );
		
		ProcessMenuItem( menuID, item );
		
	}
	
}

