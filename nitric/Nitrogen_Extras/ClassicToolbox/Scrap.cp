/*	========
 *	Scrap.cp
 *	========
 */

// *** A-line Processing Instructions ***
// API: ClassicMacToolbox (not Carbon)

#ifndef CLASSICTOOLBOX_SCRAP_H
#include "ClassicToolbox/Scrap.h"
#endif

// Nucleus
#ifndef NUCLEUS_ONLYONCE_H
#include "Nucleus/OnlyOnce.h"
#endif

// Nitrogen
#ifndef NITROGEN_OSSTATUS_H
#include "Nitrogen/OSStatus.h"
#endif


namespace Nitrogen
{
	
#if CALL_NOT_IN_CARBON
	
	void ZeroScrap()
	{
		Nucleus::OnlyOnce< RegisterScrapManagerErrors >();
		
		ThrowOSStatus( ::ZeroScrap() );
	}
	
#endif
	
}

