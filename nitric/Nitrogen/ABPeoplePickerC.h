//  ABPeoplePickerC.h

#ifndef NITROGEN_ABPEOPLEPICKER_H
#define	NITROGEN_ABPEOPLEPICKER_H

#if	!TARGET_RT_MAC_MACHO
#error "These routines are only directly callable from MachO"
#endif

#include <AddressBook/ABPeoplePickerC.h>

#ifndef NITROGEN_FRAMEWORKHEADER_H
#include "Nitrogen/FrameworkHeader.h"
#endif

#ifndef NITROGEN_OWNED_H
#include "Nitrogen/Owned.h"
#endif

#ifndef NITROGEN_CFARRAY_H
#include "Nitrogen/CFArray.h"
#endif

#ifndef NITROGEN_CFSTRING_H
#include "Nitrogen/CFString.h"
#endif

#ifndef NITROGEN_ADDRESSBOOKC_H
#include "Nitrogen/ABAddressBookC.h"
#endif

namespace Nitrogen {

//	typedef struct OpaqueABPicker*  ABPickerRef;
	using ::ABPickerRef;
   template <> struct Disposer< ABPickerRef >: public std::unary_function< ABPickerRef, void >
     {
      void operator()( ABPickerRef pick ) const
        {
         OnlyOnce<RegisterAddressBookErrors>();
         ::CFRelease ( pick );
        }
     };

//	---------------------------------------
//	Picker creation and manipulation
//	---------------------------------------

//	Creates an ABPickerRef. The window is created hidden. 
//	Call ABPickerSetVisibility() to show it.
    inline Owned<ABPickerRef> ABPickerCreate ( void ) {
		OnlyOnce<RegisterAddressBookErrors>();
		ABPickerRef result = ::ABPickerCreate ();
		return Owned<ABPickerRef>::Seize( result );
    	}

// Change the structural frame of the window.
    inline void ABPickerSetFrame ( ABPickerRef inPicker, const HIRect &inFrame ) {
		OnlyOnce<RegisterAddressBookErrors>();
		::ABPickerSetFrame ( inPicker, &inFrame );
		}
	 
    inline HIRect ABPickerGetFrame ( ABPickerRef inPicker ) {
		OnlyOnce<RegisterAddressBookErrors>();
		HIRect result;
		::ABPickerGetFrame ( inPicker, &result );
		return result;
		}
	
//	extern void ABPickerSetVisibility ( ABPickerRef inPicker, bool visible );
	using ::ABPickerSetVisibility;
	
//	extern bool ABPickerIsVisible ( ABPickerRef inPicker );
	using ::ABPickerIsVisible;

//	---------------------------------------
//	Look and Feel
//	---------------------------------------
//	extern ABPickerAttributes ABPickerGetAttributes ( ABPickerRef inPicker );
	using ::ABPickerGetAttributes;
	
//	extern void ABPickerChangeAttributes ( ABPickerRef inPicker, ABPickerAttributes inAttributesToSet, ABPickerAttributes inAttributesToClear );
	using ::ABPickerGetAttributes;
	
//	Nitrogen Additions
    inline void ABPickerSetAttributes ( ABPickerRef inPicker, ABPickerAttributes inAttributesToSet ) {
		ABPickerChangeAttributes ( inPicker, inAttributesToSet, ABPickerAttributes ( 0 ));
		}
	
    inline void ABPickerClearAttributes ( ABPickerRef inPicker, ABPickerAttributes inAttributesToClear ) {
		ABPickerChangeAttributes ( inPicker, ABPickerAttributes ( 0 ), inAttributesToClear );
		}


//	---------------------------------------
//	Value column
//	---------------------------------------

// These methods control what data (if any) is shown in the values column. The column will only
// display if an AB property is added. A popup button in the column header will be used if more
// than one property is added. Titles for built in properties will localized automatically. A
// list of AB properties can be found in <AddressBook/ABGlobals.h>.

//	extern void ABPickerAddProperty ( ABPickerRef inPicker, CFStringRef inProperty );
	using ::ABPickerAddProperty;
	
//	extern void ABPickerRemoveProperty ( ABPickerRef inPicker, CFStringRef inProperty );
	using ::ABPickerRemoveProperty;
	
// Returns an array of AB Properties as CFStringRefs.
    inline Owned<CFArrayRef> ABPickerCopyProperties ( ABPickerRef inPicker ) {
		OnlyOnce<RegisterAddressBookErrors>();
		CFArrayRef result = ::ABPickerCopyProperties ( inPicker );
		return Owned<CFArrayRef>::Seize( result );
		}

//	Localized titles for third party properties should be set with these methods.
//	extern void ABPickerSetColumnTitle ( ABPickerRef inPicker, CFStringRef inTitle, CFStringRef inProperty );
	using ::ABPickerSetColumnTitle;
	
    inline Owned<CFStringRef> ABPickerCopyColumnTitle ( ABPickerRef inPicker, CFStringRef inProperty ) {
		OnlyOnce<RegisterAddressBookErrors>();
		CFStringRef result = ::ABPickerCopyColumnTitle ( inPicker, inProperty );
		return Owned<CFStringRef>::Seize( result );
    	}

//	Display one of the properties added above in the values column.
//	extern void ABPickerSetDisplayedProperty ( ABPickerRef inPicker, CFStringRef inProperty );
	using ::ABPickerSetDisplayedProperty;
	
	inline Owned<CFStringRef> ABPickerCopyDisplayedProperty ( ABPickerRef inPicker ) {
		OnlyOnce<RegisterAddressBookErrors>();
		CFStringRef result = ::ABPickerCopyDisplayedProperty ( inPicker );
		return Owned<CFStringRef>::Seize( result );
    	}

//	---------------------------------------
//	Selection
//	---------------------------------------

//	Returns group column selection as an array of ABGroupRef objects.
	inline Owned<CFArrayRef> ABPickerCopySelectedGroups ( ABPickerRef inPicker ) {
		OnlyOnce<RegisterAddressBookErrors>();
		CFArrayRef result = ::ABPickerCopySelectedGroups ( inPicker );
		return Owned<CFArrayRef>::Seize( result );
		}

//	Returns names column selection as an array of ABGroupRef or ABPersonRef objects.
	inline Owned<CFArrayRef> ABPickerCopySelectedRecords ( ABPickerRef inPicker ) {
		OnlyOnce<RegisterAddressBookErrors>();
		CFArrayRef result = ::ABPickerCopySelectedRecords ( inPicker );
		return Owned<CFArrayRef>::Seize( result );
		}

//	This method returns an array of selected multi-value identifiers. Returns nil if the displayed
//	property is a single value type.
	inline Owned<CFArrayRef> ABPickerCopySelectedIdentifiers ( ABPickerRef inPicker, ABPersonRef inPerson ) {
		OnlyOnce<RegisterAddressBookErrors>();
		CFArrayRef result = ::ABPickerCopySelectedIdentifiers ( inPicker, inPerson );
		return Owned<CFArrayRef>::Seize( result );
		}

//	Returns an array containing CFStringRefs for each item selected in the values column.
	inline Owned<CFArrayRef> ABPickerCopySelectedValues ( ABPickerRef inPicker ) {
		OnlyOnce<RegisterAddressBookErrors>();
		CFArrayRef result = ::ABPickerCopySelectedValues ( inPicker );
		return Owned<CFArrayRef>::Seize( result );
		}

//	Select group/name/value programatically.
//	extern void ABPickerSelectGroup		 ( ABPickerRef inPicker, ABGroupRef inGroup, bool inExtendSelection );
//	extern void ABPickerSelectRecord	 ( ABPickerRef inPicker, ABRecordRef inRecord, bool inExtendSelection );
//	extern void ABPickerSelectIdentifier ( ABPickerRef inPicker, ABPersonRef inPerson, CFStringRef inIdentifier, bool inExtendSelection );
	using ::ABPickerSelectGroup;	
	using ::ABPickerSelectRecord;
	using ::ABPickerSelectIdentifier;

//	Remove selection
//	extern void ABPickerDeselectGroup	   ( ABPickerRef inPicker, ABGroupRef inGroup );
//	extern void ABPickerDeselectRecord	   ( ABPickerRef inPicker, ABRecordRef inRecord );
//	extern void ABPickerDeselectIdentifier ( ABPickerRef inPicker, ABPersonRef inPerson, CFStringRef inIdentifier );
//	extern void ABPickerDeselectAll		   ( ABPickerRef inPicker );
	using ::ABPickerDeselectGroup;
	using ::ABPickerDeselectRecord;
	using ::ABPickerDeselectIdentifier;
	using ::ABPickerDeselectAll;

/*
 * Events and Actions
 *
 * Your delegate will be notified when the user changes the selection or displayed property of the picker.
 * Picker events have an event class of kEventClassABPeoplePicker and one of the kinds listed below. Picker
 * events contain an event parameter which contains the ABPickerRef. To obtain this:
 *
 * GetEventParameter(inEvent, kEventParamABPickerRef,
 *                   typeCFTypeRef, NULL, sizeof(ABPickerRef),
 *                   NULL, &outPickerRef);
 *
 */

//	Set the event handler for People Picker events.
//	extern void        ABPickerSetDelegate ( ABPickerRef inPicker, HIObjectRef inDelegate );
//	extern HIObjectRef ABPickerGetDelegate ( ABPickerRef inPicker );
	using ::ABPickerSetDelegate;
	using ::ABPickerGetDelegate;

//	Clear the search field and reset the list of displayed names.
//	extern void ABPickerClearSearchField(ABPickerRef inPicker);
	using ::ABPickerClearSearchField;

//	Launch AddressBook and edit the current selection
//	extern void ABPickerEditInAddressBook   ( ABPickerRef inPicker );
//	extern void ABPickerSelectInAddressBook ( ABPickerRef inPicker );
	using ::ABPickerEditInAddressBook;
	using ::ABPickerSelectInAddressBook;
	}

#endif

