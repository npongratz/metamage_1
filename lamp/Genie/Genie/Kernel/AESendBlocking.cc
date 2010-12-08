/*	=================
 *	AESendBlocking.cc
 *	=================
 */

// Nitrogen
#include "Nitrogen/AEInteraction.hh"
#include "Nitrogen/OSStatus.hh"

// Nitrogen Extras / AEFramework
#include "AEFramework/AEFramework.h"

// Genie
#include "Genie/current_process.hh"
#include "Genie/Process.hh"
#include "Genie/SystemCallRegistry.hh"


namespace Genie
{
	
	namespace N = Nitrogen;
	
	
	static OSStatus AESendBlocking( const AppleEvent* appleEventPtr, AppleEvent* replyPtr )
	{
		try
		{
			N::AppleEvent const& appleEvent = static_cast< const N::AppleEvent& >( *appleEventPtr );
			N::AppleEvent      & reply      = static_cast<       N::AppleEvent& >( *replyPtr      );
			
			(void) N::AESend( appleEvent,
			                  N::kAEQueueReply | N::kAECanInteract );
			
			// Now that we've sent the event, retrieve the return ID
			N::AEReturnID_32Bit returnID = N::AEGetAttributePtr< N::keyReturnIDAttr >( appleEvent );
			
			// Subscribe to AEFramework's queued reply delivery and wake-up service
			N::ExpectReply( returnID, &reply );
			
			// Sleep until the reply is delivered
			current_process().Stop();
		}
		catch ( const N::OSStatus& err )
		{
			return err;
		}
		
		return noErr;
	}
	
	#pragma force_active on
	
	REGISTER_SYSTEM_CALL( AESendBlocking );
	
	#pragma force_active reset
	
}

