// Nitrogen/AEDataModel.h
// ----------------------
//
// Maintained by Joshua Juran

// Part of the Nitrogen project.
//
// Written 2002-2007 by Lisa Lippincott and Joshua Juran.
//
// This code was written entirely by the above contributors, who place it
// in the public domain.


#ifndef NITROGEN_AEDATAMODEL_H
#define NITROGEN_AEDATAMODEL_H

#ifndef NITROGEN_FRAMEWORKHEADER_H
#include "Nitrogen/FrameworkHeader.h"
#endif
#ifndef __AEDATAMODEL__
#include FRAMEWORK_HEADER(AE,AEDataModel.h)
#endif
#ifndef __EVENTS__
#include FRAMEWORK_HEADER(HIToolbox,Events.h)
#endif

#ifndef NUCLEUS_FLAG_H
#include "Nucleus/Flag.h"
#endif
#ifndef NUCLEUS_ID_H
#include "Nucleus/ID.h"
#endif
#ifndef NUCLEUS_NASSERT_H
#include "Nucleus/NAssert.h"
#endif
#ifndef NUCLEUS_OWNED_H
#include "Nucleus/Owned.h"
#endif
#ifndef NUCLEUS_SELECTOR_H
#include "Nucleus/Selector.h"
#endif

#ifndef NITROGEN_AEKEYWORD_H
#include "Nitrogen/AEKeyword.h"
#endif
#ifndef NITROGEN_DESCTYPE_H
#include "Nitrogen/DescType.h"
#endif

#ifndef NITROGEN_ALIASES_H
#include "Nitrogen/Aliases.h"
#endif
#ifndef NITROGEN_MACMEMORY_H
#include "Nitrogen/MacMemory.h"
#endif
#ifndef NITROGEN_MACTYPES_H
#include "Nitrogen/MacTypes.h"
#endif
#ifndef NITROGEN_PROCESSES_H
#include "Nitrogen/Processes.h"
#endif
#ifndef NITROGEN_OSSTATUS_H
#include "Nitrogen/OSStatus.h"
#endif
#ifndef NITROGEN_REFCON_H
#include "Nitrogen/RefCon.h"
#endif
#ifndef NITROGEN_UPP_H
#include "Nitrogen/UPP.h"
#endif

#include <string>


#ifdef AEPutKeyPtr
#undef AEPutKeyPtr

inline OSErr AEPutKeyPtr( AppleEvent*  theAppleEvent,
                          AEKeyword    theAEKeyword,
                          DescType     typeCode,
                          const void*  dataPtr,
                          Size         dataSize )
{
	return AEPutParamPtr( theAppleEvent,
	                      theAEKeyword,
	                      typeCode,
	                      dataPtr,
	                      dataSize );
}

#endif

#ifdef AEPutKeyDesc
#undef AEPutKeyDesc

inline OSErr AEPutKeyDesc( AppleEvent*    theAppleEvent,
                           AEKeyword      theAEKeyword,
                           const AEDesc*  theAEDesc )
{
	return AEPutParamDesc( theAppleEvent, theAEKeyword, theAEDesc );
}

#endif

#ifdef AEGetKeyPtr
#undef AEGetKeyPtr

inline OSErr AEGetKeyPtr( const AppleEvent*  theAppleEvent,
                          AEKeyword          theAEKeyword,
                          DescType           desiredType,
                          DescType*          typeCode,
                          void*              dataPtr,
                          Size               maximumSize,
                          Size*              actualSize )
{
	return AEGetParamPtr( theAppleEvent,
	                      theAEKeyword,
	                      desiredType,
	                      typeCode,
	                      dataPtr,
	                      maximumSize,
	                      actualSize );
}

#endif

#ifdef AEGetKeyDesc
#undef AEGetKeyDesc

inline OSErr AEGetKeyDesc( const AppleEvent*  theAppleEvent,
                           AEKeyword          theAEKeyword,
                           DescType           desiredType,
                           AEDesc*            result )
{
	return AEGetParamDesc( theAppleEvent,
	                       theAEKeyword,
	                       desiredType,
	                       result );
}

#endif

#ifdef AESizeOfKeyDesc
#undef AESizeOfKeyDesc

inline OSErr AESizeOfKeyDesc( const AppleEvent*  theAppleEvent,
                              AEKeyword          theAEKeyword,
                              DescType*          typeCode,
                              Size*              dataSize )
{
	return AESizeOfParam( theAppleEvent,
	                      theAEKeyword,
	                      typeCode,
	                      dataSize );
}

#endif

#ifdef AEDeleteKeyDesc
#undef AEDeleteKeyDesc

inline OSErr AEDeleteKeyDesc( AppleEvent*  theAppleEvent,
                              AEKeyword    theAEKeyword )
{
	return AEDeleteParam( theAppleEvent, theAEKeyword );
}

#endif


namespace Nitrogen
{
	
	class AppleEventManagerErrorsRegistrationDependency
	{
		public:
			AppleEventManagerErrorsRegistrationDependency();
	};
	
	#pragma mark -
	#pragma mark � DescType �
	
	// Constants used creating an AppleEvent
	
	enum AEReturnID
	{
		kAutoGenerateReturnID = ::kAutoGenerateReturnID,
		
		kAEReturnID_Max = Nucleus::Enumeration_Traits< ::AEReturnID >::max
	};
	
	enum AETransactionID
	{
		kAnyTransactionID = ::kAnyTransactionID,
		
		kAETransactionID_Max = Nucleus::Enumeration_Traits< ::AETransactionID >::max
	};
	
	typedef Nucleus::Selector< class AEEventClass_Tag, ::AEEventClass >::Type  AEEventClass;
	typedef Nucleus::Selector< class AEEventID_Tag,    ::AEEventID    >::Type  AEEventID;
	
	typedef Nucleus::Selector< class AEEnumerated_Tag, UInt32 >::Type AEEnumerated;
	typedef AEEnumerated AEEnumeration;
	typedef AEEnumerated AEKeyForm;
	
	
	enum AESendPriority
	{
		kAENormalPriority = ::kAENormalPriority,
		kAEHighPriority   = ::kAEHighPriority,
		
		kAESendPriority_Max = Nucleus::Enumeration_Traits< ::AESendPriority >::max
	};
	
	NUCLEUS_DEFINE_FLAG_OPS( AESendPriority )
	
	enum AESendMode
	{
		kAENoReply               = ::kAENoReply,
		kAEQueueReply            = ::kAEQueueReply,
		kAEWaitReply             = ::kAEWaitReply,
		kAEDontReconnect         = ::kAEDontReconnect,
		kAEWantReceipt           = ::kAEWantReceipt,
		kAENeverInteract         = ::kAENeverInteract,
		kAECanInteract           = ::kAECanInteract,
		kAEAlwaysInteract        = ::kAEAlwaysInteract,
		kAECanSwitchLayer        = ::kAECanSwitchLayer,
		kAEDontRecord            = ::kAEDontRecord,
		kAEDontExecute           = ::kAEDontExecute,
		kAEProcessNonReplyEvents = ::kAEProcessNonReplyEvents,
		
		kAESendMode_Max = Nucleus::Enumeration_Traits< ::AESendMode >::max
	};
	
	NUCLEUS_DEFINE_FLAG_OPS( AESendMode )
	
	
	#pragma mark -
	#pragma mark � DescType_Traits �
	
	template < DescType > struct DescType_Traits;
	
	template<> struct DescType_Traits< typeChar > : public Nucleus::StringFlattener< std::string > {};
	
	template<> struct DescType_Traits< typeFixed > : public FixedFlattener {};
	
	template<> struct DescType_Traits< typeNull >                   { typedef void Result; };
	
	template<> struct DescType_Traits< typeBoolean >                : BooleanFlattener                     {};
	template<> struct DescType_Traits< typeSInt16 >                 : Nucleus::PodFlattener< SInt16 >      {};
	template<> struct DescType_Traits< typeSInt32 >                 : Nucleus::PodFlattener< SInt32 >      {};
	template<> struct DescType_Traits< typeUInt32 >                 : Nucleus::PodFlattener< UInt32 >      {};
	template<> struct DescType_Traits< typeSInt64 >                 : Nucleus::PodFlattener< SInt64 >      {};
	template<> struct DescType_Traits< typeIEEE32BitFloatingPoint > : Nucleus::PodFlattener< float >       {};
	template<> struct DescType_Traits< typeIEEE64BitFloatingPoint > : Nucleus::PodFlattener< double >      {};
	template<> struct DescType_Traits< type128BitFloatingPoint >    : Nucleus::PodFlattener< long double > {};
	
	inline std::size_t SizeOf_AppParameters( const AppParameters& appParameters )
	{
		return sizeof (AppParameters) + appParameters.messageLength;
	}
	
	template<> struct DescType_Traits< typeEventRecord >            : Nucleus::PodFlattener< EventRecord >                      {};
	template<> struct DescType_Traits< typeAlias >                  : TypedHandleFlattener< AliasRecord >                       {};
	template<> struct DescType_Traits< typeEnumerated >             : Nucleus::ConvertingPODFlattener< AEEnumerated, UInt32 >   {};
	template<> struct DescType_Traits< typeType >                   : Nucleus::ConvertingPODFlattener< DescType, ::DescType >   {};
	template<> struct DescType_Traits< typeAppParameters >          : Nucleus::VariableLengthPodFlattener< AppParameters, SizeOf_AppParameters > {};
	template<> struct DescType_Traits< typeFSS >                    : Nucleus::PodFlattener< FSSpec >                           {};
	template<> struct DescType_Traits< typeFSRef >                  : Nucleus::PodFlattener< FSRef >                            {};
	template<> struct DescType_Traits< typeKeyword >                : Nucleus::ConvertingPODFlattener< AEKeyword, ::AEKeyword > {};
	template<> struct DescType_Traits< typeApplSignature >          : Nucleus::ConvertingPODFlattener< OSType, ::OSType >       {};
	template<> struct DescType_Traits< typeQDRectangle >            : Nucleus::PodFlattener< Rect >                             {};
	template<> struct DescType_Traits< typeProcessSerialNumber >    : Nucleus::PodFlattener< ProcessSerialNumber >              {};
	template<> struct DescType_Traits< typeApplicationURL >         : DescType_Traits< typeChar >                               {};
	
	
	template < DescType type >
	struct DescType_Map_Traits
	{
		static const DescType result = type;
	};
	
	template < class Integer > struct Integer_DescType_Traits;
	
	template <> struct Integer_DescType_Traits< SInt16 >  { static const DescType descType = typeSInt16; };
	template <> struct Integer_DescType_Traits< SInt32 >  { static const DescType descType = typeSInt32; };
	template <> struct Integer_DescType_Traits< UInt32 >  { static const DescType descType = typeUInt32; };
	
	struct Type_DescType_Traits  { static const DescType descType = typeType;       };
	struct Enum_DescType_Traits  { static const DescType descType = typeEnumerated; };
	
	template < class POD, class Integer >
	struct Integer_AEKeyword_Traits : Nucleus::ConvertingPODFlattener< POD, Integer >,
	                                  Integer_DescType_Traits< Integer >
	{
	};
	
	template < class POD >
	struct Type_AEKeyword_Traits : Nucleus::ConvertingPODFlattener< POD, ::FourCharCode >,
	                               Type_DescType_Traits
	{
	};
	
	template < class POD >
	struct Enum_AEKeyword_Traits : Nucleus::ConvertingPODFlattener< POD, ::FourCharCode >,
	                               Enum_DescType_Traits
	{
	};
	
	template < AEKeyword key > struct AEKeyword_Traits;
	
	template <> struct AEKeyword_Traits< keyTransactionIDAttr > : Integer_AEKeyword_Traits< AETransactionID, ::AETransactionID > {};
	template <> struct AEKeyword_Traits< keyReturnIDAttr      > : Integer_AEKeyword_Traits< AEReturnID,      ::AEReturnID      > {};
	
	template <> struct AEKeyword_Traits< keyEventClassAttr > : Type_AEKeyword_Traits< AEEventClass > {};
	template <> struct AEKeyword_Traits< keyEventIDAttr    > : Type_AEKeyword_Traits< AEEventID    > {};
	
	// In AppleEvents.h due to dependency on enum AEEventSource.
	//template <> struct AEKeyword_Traits< keyEventSourceAttr > : Integer_AEKeyword_Traits< AEEventSource, SInt16 > {};
	
	template <> struct AEKeyword_Traits< keyMissedKeywordAttr > : Type_AEKeyword_Traits< AEKeyword > {};
	
	#pragma mark -
	#pragma mark � AEDesc �
	
	using ::AEDesc;
	using ::AEDescList;
	using ::AERecord;
	using ::AEKeyDesc;
	
	struct AEDesc_Data : AEDesc
	{
	};
	
	typedef AEDesc_Data AEDescList_Data, AERecord_Data;
	typedef AEDesc_Data AEAddressDesc, AppleEvent;
	typedef AEDesc_Data AEDesc_ObjectSpecifier;
	
	struct AEDesc_Token : AEDesc
	{
	};
	
	typedef AEDesc_Token AEDescList_Token, AERecord_Token;
	
}

namespace Nucleus
{
	
	template <> struct Converter< Nitrogen::DescType,     std::string > : public Nitrogen::StringToFourCharCode_Converter< Nitrogen::DescType     > {};
	template <> struct Converter< Nitrogen::AEKeyword,    std::string > : public Nitrogen::StringToFourCharCode_Converter< Nitrogen::AEKeyword    > {};
	template <> struct Converter< Nitrogen::AEEventClass, std::string > : public Nitrogen::StringToFourCharCode_Converter< Nitrogen::AEEventClass > {};
	template <> struct Converter< Nitrogen::AEEventID,    std::string > : public Nitrogen::StringToFourCharCode_Converter< Nitrogen::AEEventID    > {};
	template <> struct Converter< Nitrogen::AEEnumerated, std::string > : public Nitrogen::StringToFourCharCode_Converter< Nitrogen::AEEnumerated > {};
	
	template <> struct Converter< std::string, Nitrogen::DescType     > : public Nitrogen::FourCharCodeToString_Converter< Nitrogen::DescType     > {};
	template <> struct Converter< std::string, Nitrogen::AEKeyword    > : public Nitrogen::FourCharCodeToString_Converter< Nitrogen::AEKeyword    > {};
	template <> struct Converter< std::string, Nitrogen::AEEventClass > : public Nitrogen::FourCharCodeToString_Converter< Nitrogen::AEEventClass > {};
	template <> struct Converter< std::string, Nitrogen::AEEventID    > : public Nitrogen::FourCharCodeToString_Converter< Nitrogen::AEEventID    > {};
	template <> struct Converter< std::string, Nitrogen::AEEnumerated > : public Nitrogen::FourCharCodeToString_Converter< Nitrogen::AEEnumerated > {};
	
	template <>
	struct Maker< Nitrogen::AEDesc >
	{
		Nitrogen::AEDesc operator()() const
		{
			Nitrogen::AEDesc result = { typeNull, NULL };
			return result;
		}
	};
	
	template <>
	struct Maker< Nitrogen::AEDesc_Data >
	{
		Nitrogen::AEDesc_Data operator()() const
		{
			Nitrogen::AEDesc_Data result;
			
			static_cast< AEDesc& >( result ) = Make< AEDesc >();
			
			return result;
		}
	};
	
	template <>
	struct Maker< Nitrogen::AEDesc_Token >
	{
		Nitrogen::AEDesc_Token operator()() const
		{
			Nitrogen::AEDesc_Token result;
			
			static_cast< AEDesc& >( result ) = Make< AEDesc >();
			
			return result;
		}
	};
	
	template <>
	struct Disposer< Nitrogen::AEDesc_Data > : public std::unary_function< Nitrogen::AEDesc, void >,
	                                           private Nitrogen::DefaultDestructionOSStatusPolicy
	{
		// parameter can't be const
		void operator()( Nitrogen::AEDesc desc ) const
		{
			// AEDisposeDesc() is documented as only ever returning noErr,
			// but we check anyway to be future-proof.
			
			(void) Nitrogen::AppleEventManagerErrorsRegistrationDependency();
			
			HandleDestructionOSStatus( ::AEDisposeDesc( &desc ) );
		}
	};
	
	template <>
	struct LivelinessTraits< Nitrogen::AEDesc_Data, Disposer< Nitrogen::AEDesc_Data > >   { typedef SeizedValuesAreLive LivelinessTest; };
	
	template <>
	struct Disposer< Nitrogen::AEDesc_Token > : public std::unary_function< Nitrogen::AEDesc, void >,
	                                            private Nitrogen::DefaultDestructionOSStatusPolicy
	{
		// parameter can't be const
		void operator()( Nitrogen::AEDesc desc ) const
		{
			(void) Nitrogen::AppleEventManagerErrorsRegistrationDependency();
			
			HandleDestructionOSStatus( ::AEDisposeToken( &desc ) );
		}
	};
	
	template <>
	struct LivelinessTraits< Nitrogen::AEDesc_Token, Disposer< Nitrogen::AEDesc_Token > >   { typedef SeizedValuesAreLive LivelinessTest; };
	
	template <>
	struct Disposer< Nitrogen::AEKeyDesc > : public std::unary_function< Nitrogen::AEKeyDesc, void >,
	                                         private Nitrogen::DefaultDestructionOSStatusPolicy
	{
		// parameter can't be const
		void operator()( Nitrogen::AEKeyDesc keyDesc ) const
		{
			Disposer< Nitrogen::AEDesc_Data >()( keyDesc.descContent );
		}
	};
	
	template <>
	struct LivelinessTraits< Nitrogen::AEKeyDesc, Disposer< Nitrogen::AEKeyDesc > >
	{
		typedef SeizedValuesAreLive LivelinessTest;
	};
	
	template <>
	struct Maker< Nitrogen::AEKeyDesc >
	{
		Nitrogen::AEKeyDesc operator()() const
		{
			Nitrogen::AEKeyDesc result = { Nitrogen::AEKeyword(), Make< Nitrogen::AEDesc >() };
			return result;
		}
	};
	
}

namespace Nitrogen
{
	
	#pragma mark -
	#pragma mark � Coercions �
	
	struct AECoerceDescUPP_Details: Basic_UPP_Details< ::AECoerceDescUPP,
	                                                   ::AECoerceDescProcPtr,
	                                                   ::NewAECoerceDescUPP,
	                                                   ::DisposeAECoerceDescUPP,
	                                                   ::InvokeAECoerceDescUPP >
	{
	};
	
	struct AECoercePtrUPP_Details: Basic_UPP_Details< ::AECoercePtrUPP,
	                                                  ::AECoercePtrProcPtr,
	                                                  ::NewAECoercePtrUPP,
	                                                  ::DisposeAECoercePtrUPP,
	                                                  ::InvokeAECoercePtrUPP >
	{
	};
	
	typedef UPP< AECoerceDescUPP_Details > AECoerceDescUPP;
	typedef UPP< AECoercePtrUPP_Details  > AECoercePtrUPP;
	
	inline Nucleus::Owned< AECoerceDescUPP > NewAECoerceDescUPP( ::AECoerceDescProcPtr p )
	{
		return NewUPP< AECoerceDescUPP >( p );
	}
	
	inline Nucleus::Owned< AECoercePtrUPP > NewAECoercePtrUPP( ::AECoercePtrProcPtr p )
	{
		return NewUPP< AECoercePtrUPP >( p );
	}
	
	inline void DisposeAECoerceDescUPP( Nucleus::Owned< AECoerceDescUPP > )  {}
	inline void DisposeAECoercePtrUPP ( Nucleus::Owned< AECoercePtrUPP  > )  {}
	
	inline void InvokeAECoerceDescUPP( const AEDesc_Data&  fromDesc,
	                                   DescType            toType,
	                                   RefCon              handlerRefCon,
	                                   AEDesc_Data&        toDesc,
	                                   AECoerceDescUPP     userUPP )
	{
		ThrowOSStatus( userUPP( &fromDesc,
		                        toType,
		                        handlerRefCon,
		                        &toDesc ) );
	}
	
	inline void InvokeAECoercePtrUPP( DescType        typeCode,
	                                  const void*     dataPtr,
	                                  std::size_t     dataSize,
	                                  DescType        toType,
	                                  RefCon          handlerRefCon,
	                                  AEDesc_Data&    toDesc,
	                                  AECoercePtrUPP  userUPP )
	{
		ThrowOSStatus( userUPP( typeCode,
		                        dataPtr,
		                        dataSize,
		                        toType,
		                        handlerRefCon,
		                        &toDesc ) );
	}
	
	struct AECoercionHandlerUPP : AECoerceDescUPP
	{
		AECoercionHandlerUPP()  {}
		AECoercionHandlerUPP( ::AECoerceDescUPP p ) : AECoerceDescUPP( p )  {}
	
	#if TARGET_CPU_68K && !TARGET_RT_MAC_CFM  ||  OPAQUE_UPP_TYPES
		
		AECoercionHandlerUPP( ::AECoercePtrUPP p )
		:
			AECoerceDescUPP( reinterpret_cast< ::AECoerceDescUPP >( p ) )
		{
		}
		
	#endif
	};
	
	struct AECoercionHandler
	{
		DescType              fromType;
		DescType              toType;
		AECoercionHandlerUPP  handler;
		RefCon                handlerRefCon;
		bool                  fromTypeIsDesc;
		bool                  isSysHandler;
		
		AECoercionHandler();
		
		AECoercionHandler( DescType              fromType,
		                   DescType              toType,
		                   AECoercionHandlerUPP  handler,
		                   RefCon                handlerRefCon,
		                   bool                  fromTypeIsDesc,
		                   bool                  isSysHandler )
		:
			fromType      ( fromType       ),
			toType        ( toType         ),
			handler       ( handler        ),
			handlerRefCon ( handlerRefCon  ),
			fromTypeIsDesc( fromTypeIsDesc ),
			isSysHandler  ( isSysHandler   )
		{
		}
		
		AECoercionHandler( DescType         fromType,
		                   DescType         toType,
		                   AECoerceDescUPP  handler,
		                   RefCon           handlerRefCon,
		                   bool             isSysHandler )
		:
			fromType      ( fromType      ),
			toType        ( toType        ),
			handler       ( handler       ),
			handlerRefCon ( handlerRefCon ),
			fromTypeIsDesc( true          ),
			isSysHandler  ( isSysHandler  )
		{
		}
		
		AECoercionHandler( DescType        fromType,
		                   DescType        toType,
		                   AECoercePtrUPP  handler,
		                   RefCon          handlerRefCon,
		                   bool            isSysHandler )
		:
			fromType      ( fromType      ),
			toType        ( toType        ),
			handler       ( handler       ),
			handlerRefCon ( handlerRefCon ),
			fromTypeIsDesc( false         ),
			isSysHandler  ( isSysHandler  )
		{
		}
	};
	
	bool operator==( const AECoercionHandler& a, const AECoercionHandler& b );
	
	inline bool operator!=( const AECoercionHandler& a, const AECoercionHandler& b )
	{
		return !( a == b );
	}
	
}

namespace Nucleus
{
	
	template <>
	struct Disposer< Nitrogen::AECoercionHandler > : public std::unary_function< Nitrogen::AECoercionHandler, void >,
	                                                 private Nitrogen::DefaultDestructionOSStatusPolicy
	{
		void operator()( const Nitrogen::AECoercionHandler& installation ) const
		{
			HandleDestructionOSStatus( ::AERemoveCoercionHandler( installation.fromType,
			                                                      installation.toType,
			                                                      installation.handler,
			                                                      installation.isSysHandler ) );
		}
	};
	
}

namespace Nitrogen
{
	
	typedef Nucleus::Owned< AEDesc_Data > ( *AECoerceDescProcPtr )( const AEDesc_Data&  fromDesc,
	                                                                DescType            toType,
	                                                                RefCon              refCon );
	
	typedef Nucleus::Owned< AEDesc_Data > ( *AECoercePtrProcPtr )( DescType     typeCode,
	                                                               const void*  dataPtr,
	                                                               std::size_t  datasize,
	                                                               DescType     toType,
	                                                               RefCon       refCon );
	
	template < AECoerceDescProcPtr handler >
	struct AECoercionHandler_Desc_Callback
	{
		static pascal OSErr Adapter( const AEDesc*  fromDesc,
		                             ::DescType     toType,
		                             long           refCon,
		                             AEDesc*        result )
		{
			try
			{
				*result = handler( static_cast< const AEDesc_Data& >( *fromDesc ),
				                   DescType( toType ),
				                   refCon ).Release();
			}
			catch ( ... )
			{
				return Nucleus::Convert< OSStatus >( Nucleus::TheExceptionBeingHandled(),
				                                     OSStatus( errAEEventFailed ) );
			}
			
			return noErr;
		}
	};
	
	template < AECoercePtrProcPtr handler >
	struct AECoercionHandler_Ptr_Callback
	{
		static pascal OSErr Adapter( ::DescType   typeCode,
		                             const void*  dataPtr,
		                             ::Size       dataSize,
		                             ::DescType   toType,
		                             long         refCon,
		                             AEDesc*      result )
		{
			try
			{
				*result = handler( DescType( typeCode ),
				                   dataPtr,
				                   dataSize,
				                   DescType( toType ),
				                   refCon ).Release();
			}
			catch ( ... )
			{
				return Nucleus::Convert< OSStatus >( Nucleus::TheExceptionBeingHandled(),
				                                     OSStatus( errAEEventFailed ) );
			}
			
			return noErr;
		}
	};
	
	// 388
	Nucleus::Owned< AECoercionHandler > AEInstallCoercionHandler( const AECoercionHandler& toInstall );
	
	inline Nucleus::Owned< AECoercionHandler > AEInstallCoercionHandler( DescType fromType,
	                                                                     DescType toType,
	                                                                     AECoerceDescUPP handler,
	                                                                     RefCon handlerRefCon = RefCon(),
	                                                                     Boolean isSysHandler = false )
	{
		return AEInstallCoercionHandler( AECoercionHandler( fromType,
		                                                    toType,
		                                                    handler,
		                                                    handlerRefCon,
		                                                    isSysHandler ) );
	}
	
	inline Nucleus::Owned< AECoercionHandler > AEInstallCoercionHandler( DescType        fromType,
	                                                                     DescType        toType,
	                                                                     AECoercePtrUPP  handler,
	                                                                     RefCon          handlerRefCon = RefCon(),
	                                                                     Boolean         isSysHandler  = false )
	{
		return AEInstallCoercionHandler( AECoercionHandler( fromType,
		                                                    toType,
		                                                    handler,
		                                                    handlerRefCon,
		                                                    isSysHandler ) );
	}
	
	template < typename AECoerceDescUPP::ProcPtr handler >
	Nucleus::Owned< AECoercionHandler > AEInstallCoercionHandler( DescType  fromType,
	                                                              DescType  toType,
	                                                              RefCon    handlerRefCon = RefCon(),
	                                                              Boolean   isSysHandler  = false )
	{
		return AEInstallCoercionHandler( AECoercionHandler( fromType,
		                                                    toType,
		                                                    StaticUPP< AECoerceDescUPP, handler >(),
		                                                    handlerRefCon,
		                                                    isSysHandler ) );
	}
	
	template < typename AECoercePtrUPP::ProcPtr handler >
	Nucleus::Owned< AECoercionHandler > AEInstallCoercionHandler( DescType  fromType,
	                                                              DescType  toType,
	                                                              RefCon    handlerRefCon = RefCon(),
	                                                              Boolean   isSysHandler  = false )
	{
		return AEInstallCoercionHandler( AECoercionHandler( fromType,
		                                                    toType,
		                                                    StaticUPP< AECoercePtrUPP, handler >(),
		                                                    handlerRefCon,
		                                                    isSysHandler ) );
	}
	
	template < AECoerceDescProcPtr handler >
	Nucleus::Owned< AECoercionHandler > AEInstallCoercionHandler( DescType  fromType,
	                                                              DescType  toType,
	                                                              RefCon    handlerRefCon = RefCon(),
	                                                              Boolean   isSysHandler  = false )
	{
		return AEInstallCoercionHandler< AECoercionHandler_Desc_Callback< handler >::Adapter >( fromType,
		                                                                                        toType,
		                                                                                        handlerRefCon,
		                                                                                        isSysHandler );
	}
	
	template < AECoercePtrProcPtr handler >
	Nucleus::Owned< AECoercionHandler > AEInstallCoercionHandler( DescType  fromType,
	                                                              DescType  toType,
	                                                              RefCon    handlerRefCon = RefCon(),
	                                                              Boolean   isSysHandler  = false )
	{
		return AEInstallCoercionHandler< AECoercionHandler_Ptr_Callback< handler >::Adapter >( fromType,
		                                                                                       toType,
		                                                                                       handlerRefCon,
		                                                                                       isSysHandler );
	}
	
	// 406
	inline void AERemoveCoercionHandler( Nucleus::Owned< AECoercionHandler > )  {}
	
	typedef AECoercionHandler AEGetCoercionHandler_Result;
	
	AECoercionHandler AEGetCoercionHandler( DescType  fromType,
	                                        DescType  toType,
	                                        bool      isSysHandler );
	
	// 444
	Nucleus::Owned< AEDesc_Data > AECoercePtr( DescType     typeCode,
	                                           const void*  dataPtr,
	                                           Size         dataSize,
	                                           DescType     toType );
	
	// 461
	Nucleus::Owned< AEDesc_Data > AECoerceDesc( const AEDesc& desc, DescType toType );
	
	#pragma mark -
	#pragma mark � AEDescs �
	
	namespace Detail
	{
		
		template < class AEDesc_Type >
		class AEDescEditor
		{
			private:
				Nucleus::Owned< AEDesc_Type >& itsDesc;
				AEDesc_Type                    itsWorkingCopy;
			
			public:
				AEDescEditor( Nucleus::Owned< AEDesc_Type >& desc )
				:
					itsDesc       ( desc           ), 
					itsWorkingCopy( desc.Release() )
				{
				}
				
				~AEDescEditor()  { itsDesc = Nucleus::Owned< AEDesc_Type >::Seize( itsWorkingCopy ); }
				
				AEDesc_Type& Get()       { return itsWorkingCopy; }
				operator AEDesc_Type&()  { return Get();          }
		};
		
	}
	
	struct AEDesc_Info
	{
		DescType typeCode;
		Size dataSize;
		
		operator Size() const  { return dataSize; }
	};
	
	typedef AEDesc_Info AESizeOfNthItem_Result,
	                    AESizeOfKeyDesc_Result,
	                    AEGetKeyPtr_Result,
	                    AESizeOfParam_Result,
	                    AESizeOfAttribute_Result,
	                    AEGetParamPtr_Result,
	                    AEGetAttributePtr_Result;

	// 484
	inline AEDesc AEInitializeDesc()
	{
		return Nucleus::Make< AEDesc >();
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AEInitializeDesc()
	{
		// AEDesc_Type must be a subclass of AEDesc
		(void) static_cast< const AEDesc& >( AEDesc_Type() );
		
		AEDesc desc = AEInitializeDesc();
		
		return Nucleus::Owned< AEDesc_Type >::Seize( static_cast< const AEDesc_Type& >( desc ) );
	}
	
	namespace Detail
	{
		
		AEDesc AECreateDesc_Unowned( DescType     typeCode,
		                             const void*  dataPtr,
		                             Size         dataSize );
		
		AEDesc AECreateDesc_Unowned( DescType typeCode, Handle handle );
		
		AEDesc AECreateDesc_Unowned( DescType typeCode, Nucleus::Owned< Handle > handle );
		
		AEDesc AEDuplicateDesc_Unowned( const AEDesc& desc );
		
		AEDesc AECreateList_Unowned( const void*  factoringPtr,
		                             std::size_t  factoredSize,
		                             bool         isRecord );
		
		AEDesc AEGetNthDesc_Unowned( const AEDesc&  listDesc,
		                             long           index,
		                             DescType       desiredType,
		                             ::AEKeyword*   keyword );
		
		AEDesc AEGetKeyDesc_Unowned( const AERecord&  record,
		                             AEKeyword        keyword,
		                             DescType         desiredType );
		
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AECreateDesc( DescType     typeCode,
	                                                   const void*  dataPtr,
	                                                   Size         dataSize )
	{
		// AEDesc_Type must be a subclass of AEDesc
		(void) static_cast< const AEDesc& >( AEDesc_Type() );
		
		AEDesc desc = Detail::AECreateDesc_Unowned( typeCode, dataPtr, dataSize );
		
		return Nucleus::Owned< AEDesc_Type >::Seize( static_cast< const AEDesc_Type& >( desc ) );
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AECreateDesc( DescType  typeCode,
	                                                   Handle    handle )
	{
		// AEDesc_Type must be a subclass of AEDesc
		(void) static_cast< const AEDesc& >( AEDesc_Type() );
		
		AEDesc desc = Detail::AECreateDesc_Unowned( typeCode, handle );
		
		return Nucleus::Owned< AEDesc_Type >::Seize( static_cast< const AEDesc_Type& >( desc ) );
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AECreateDesc( DescType                  typeCode,
	                                                   Nucleus::Owned< Handle >  handle )
	{
		// AEDesc_Type must be a subclass of AEDesc
		(void) static_cast< const AEDesc& >( AEDesc_Type() );
		
		AEDesc desc = Detail::AECreateDesc_Unowned( typeCode, handle );
		
		return Nucleus::Owned< AEDesc_Type >::Seize( static_cast< const AEDesc_Type& >( desc ) );
	}
	
	template < class AEDesc_Type, class T >
	inline Nucleus::Owned< AEDesc_Type > AECreateDesc( DescType typeCode, T** handle )
	{
		return AECreateDesc< AEDesc_Type >( typeCode, Handle( handle ) );
	}
	
	template < class AEDesc_Type, class T >
	inline Nucleus::Owned< AEDesc_Type > AECreateDesc( DescType                                            typeCode,
	                                                   Nucleus::Owned< T**, Nucleus::Disposer< Handle > >  handle )
	{
		return AECreateDesc< AEDesc_Type >( typeCode, Nucleus::Owned< Handle >( handle ) );
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AECreateDesc( DescType typeCode, Nucleus::Owned< AEDesc_Type > desc )
	{
		Detail::AEDescEditor< AEDesc_Type >( desc ).Get().descriptorType = typeCode;
		
		return desc;
	}
	
	
	inline void AEDisposeDesc( Nucleus::Owned< AEDesc_Data > )
	{
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AEDuplicateDesc( const AEDesc& original )
	{
		AEDesc desc = Detail::AEDuplicateDesc_Unowned( original );
		
		return Nucleus::Owned< AEDesc_Type >::Seize( static_cast< const AEDesc_Type& >( desc ) );
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AEDuplicateDesc( const AEDesc_Type& desc )
	{
		const AEDesc& basic( desc );
		
		return AEDuplicateDesc< AEDesc_Type >( basic );
	}
	
	#pragma mark -
	#pragma mark � AEDescLists �
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AECreateList( const void*  factoringPtr,
	                                                   std::size_t  factoredSize,
	                                                   bool         isRecord )
	{
		// Generally speaking we won't use factoring for tokens, but since the
		// unfactored version calls this one it's simpler to be general.
		
		AEDesc desc = Detail::AECreateList_Unowned( factoringPtr, factoredSize, isRecord );
		
		return Nucleus::Owned< AEDesc_Type >::Seize( static_cast< const AEDesc_Type& >( desc ) );
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AECreateList( bool isRecord = false )
	{
		return AECreateList< AEDesc_Type >( NULL, 0, isRecord );
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AECreateList( DescType typeCode, bool isRecord )
	{
		return AECreateDesc( typeCode, AECreateList< AEDesc_Type >( isRecord ) );
	}
	
	long AECountItems( const AEDesc& desc );
	
	void AEPutPtr( AEDescList&  list,
	               long         index,
	               DescType     type,
	               const void*  dataPtr,
	               Size         dataSize );
	
	template < class AEDescList_Type >
	inline void AEPutPtr( Nucleus::Owned< AEDescList_Type >&  list,
	                      long                                index,
	                      DescType                            type,
	                      const void*                         dataPtr,
	                      Size                                dataSize )
	{
		AEPutPtr( Detail::AEDescEditor< AEDescList_Type >( list ),
		          index,
		          type,
		          dataPtr,
		          dataSize );
	}
	
	void AEPutDesc( AEDescList&    list,
	                long           index,
	                const AEDesc&  desc );
	
	// Assumes AEDesc_Foo == AEDescList_Foo
	template < class AEDesc_Type >
	inline void AEPutDesc( Nucleus::Owned< AEDesc_Type >&  list,
	                long                                   index,
	                const AEDesc_Type&                     desc )
	{
		AEPutDesc( Detail::AEDescEditor< AEDesc_Type >( list ), index, desc );
	}
	
	struct GetNthPtr_Result
	{
		AEKeyword keyword;
		DescType typeCode;
		Size actualSize;
	};
	
	GetNthPtr_Result AEGetNthPtr( const AEDesc&  listDesc,
	                              long           index,
	                              DescType       desiredType,
	                              void*          dataPtr,
	                              Size           maximumSize );
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AEGetNthDesc( const AEDesc&  listDesc,
	                                                   long           index,
	                                                   DescType       desiredType = typeWildCard,
	                                                   ::AEKeyword*   keyword     = NULL )
	{
		AEDesc desc = Detail::AEGetNthDesc_Unowned( listDesc, index, desiredType, keyword );
		
		return Nucleus::Owned< AEDesc_Type >::Seize( static_cast< const AEDesc_Type& >( desc ) );
	}
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Type > AEGetNthDesc( const AEDesc&  listDesc,
	                                                   long           index,
	                                                   ::AEKeyword*   keyword )
	{
		return AEGetNthDesc< AEDesc_Type >( listDesc, index, typeWildCard, keyword );
	}
	
	AESizeOfNthItem_Result AESizeOfNthItem( const AEDescList& list, long index );
	
	// If you have a reason for deleting an item in a token list, please let me know
	
	void AEDeleteItem(                 AEDescList_Data  & listDesc, long index );
	void AEDeleteItem( Nucleus::Owned< AEDescList_Data >& listDesc, long index );
	
	#pragma mark -
	#pragma mark � AERecords �
	
	inline bool AECheckIsRecord( const AEDesc& theDesc )
	{
		return ::AECheckIsRecord( &theDesc );
	}
	
	void AEPutKeyPtr( AERecord&    record,
	                  AEKeyword    keyword,
	                  DescType     typeCode,
	                  const void*  dataPtr,
	                  std::size_t  dataSize );
	
	template < class AEDesc_Type >
	inline void AEPutKeyPtr( Nucleus::Owned< AEDesc_Type >&  record,
	                         AEKeyword                       keyword,
	                         DescType                        typeCode,
	                         const void*                     dataPtr,
	                         std::size_t                     dataSize )
	{
		AEPutKeyPtr( Detail::AEDescEditor< AEDesc_Type >( record ),
		             keyword,
		             typeCode,
		             dataPtr,
		             dataSize );
	}
	
	void AEPutKeyDesc( AERecord&      record,
	                   AEKeyword      keyword,
	                   const AEDesc&  desc );
	
	void AEPutKeyDesc( AERecord&         record,
	                   const AEKeyDesc&  keyDesc );
	
	template < class AEDesc_Type >
	inline void AEPutKeyDesc( Nucleus::Owned< AEDesc_Type >&  record,
	                          AEKeyword                       keyword,
	                          const AEDesc_Type&              desc )
	{
		AEPutKeyDesc( Detail::AEDescEditor< AEDesc_Type >( record ), keyword, desc );
	}
	
	template < class AEDesc_Type >
	inline void AEPutKeyDesc( Nucleus::Owned< AEDesc_Type >&  record,
	                          const AEKeyDesc&                keyDesc )
	{
		AEPutKeyDesc( Detail::AEDescEditor< AEDesc_Type >( record ), keyDesc );
	}
	
	class AEPutKeyDesc_Binding
	{
		private:
			AEKeyword      itsKey;
			const AEDesc&  itsData;
		
		public:
			AEPutKeyDesc_Binding( AEKeyword key, const AEDesc& data ) : itsKey( key ), itsData( data )  {}
			
			AEKeyword Key() const  { return itsKey; }
			
			const AEDesc& Data() const  { return itsData; }
	};
	
	inline AEPutKeyDesc_Binding AEPutKeyDesc( AEKeyword key, const AEDesc& data )
	{
		return AEPutKeyDesc_Binding( key, data );
	}
	
	AEGetKeyPtr_Result AEGetKeyPtr( const AERecord&  record,
	                                AEKeyword        keyword,
	                                DescType         desiredType,
	                                void*            dataPtr,
	                                std::size_t      maximumSize );
	
	template < class AEDesc_Type >
	inline Nucleus::Owned< AEDesc_Data > AEGetKeyDesc( const AERecord&  record,
	                                                   AEKeyword        keyword,
	                                                   DescType         desiredType = typeWildCard )
	{
		AEDesc desc = Detail::AEGetKeyDesc_Unowned( record, keyword, desiredType );
		
		return Nucleus::Owned< AEDesc_Type >::Seize( static_cast< const AEDesc_Type& >( desc ) );
	}
	
	AESizeOfKeyDesc_Result AESizeOfKeyDesc( const AERecord&  record,
	                                        AEKeyword        keyword );
	
	void AEDeleteKeyDesc(                 AERecord  & record, AEKeyword keyword );
	
	template < class AEDesc_Type >
	inline void AEDeleteKeyDesc( Nucleus::Owned< AEDesc_Type >& record, AEKeyword keyword )
	{
		AEDeleteKeyDesc( Detail::AEDescEditor< AEDesc_Type >( record ), keyword );
	}
	
	#pragma mark -
	#pragma mark � AppleEvents �
	
	Nucleus::Owned< AppleEvent > AECreateAppleEvent( AEEventClass          eventClass,
	                                                 AEEventID             eventID,
	                                                 const AEAddressDesc&  target,
	                                                 AEReturnID            returnID      = AEReturnID(),
	                                                 AETransactionID       transactionID = AETransactionID() );
	
	void AEPutParamPtr( AppleEvent&  appleEvent,
	                    AEKeyword    keyword,
	                    DescType     typeCode,
	                    const void*  dataPtr,
	                    std::size_t  dataSize );
	
	void AEPutParamPtr( Nucleus::Owned< AppleEvent >&  appleEvent,
	                    AEKeyword                      keyword,
	                    DescType                       typeCode,
	                    const void*                    dataPtr,
	                    std::size_t                    dataSize );
	
	void AEPutParamDesc( AppleEvent&    appleEvent,
	                     AEKeyword      keyword,
	                     const AEDesc&  desc );
	
	void AEPutParamDesc( Nucleus::Owned< AppleEvent >&  appleEvent,
	                     AEKeyword                      keyword,
	                     const AEDesc&                  desc );
	
	AEGetParamPtr_Result AEGetParamPtr( const AppleEvent&  appleEvent,
	                                    AEKeyword          keyword,
	                                    DescType           desiredType,
	                                    void*              dataPtr,
	                                    std::size_t        maximumSize );
	
	Nucleus::Owned< AEDesc_Data > AEGetParamDesc( const AppleEvent&  appleEvent,
	                                              AEKeyword          keyword,
	                                              DescType           desiredType = typeWildCard );
	
	AESizeOfParam_Result AESizeOfParam( const AppleEvent&  appleEvent,
	                                    AEKeyword          keyword );
	
	void AEDeleteParam(                 AppleEvent  & appleEvent, AEKeyword keyword );
	void AEDeleteParam( Nucleus::Owned< AppleEvent >& appleEvent, AEKeyword keyword );
	
	void AEPutAttributePtr( AppleEvent&  appleEvent,
	                        AEKeyword    keyword,
	                        DescType     typeCode,
	                        const void*  dataPtr,
	                        std::size_t  dataSize );
	
	void AEPutAttributePtr( Nucleus::Owned< AppleEvent >&  appleEvent,
	                        AEKeyword                      keyword,
	                        DescType                       typeCode,
	                        const void*                    dataPtr,
	                        std::size_t                    dataSize );
	
	void AEPutAttributeDesc( AppleEvent&    appleEvent,
	                         AEKeyword      keyword,
	                         const AEDesc&  desc );
	
	void AEPutAttributeDesc( Nucleus::Owned< AppleEvent >&  appleEvent,
	                         AEKeyword                      keyword,
	                         const AEDesc&                  desc );
	
	AEGetAttributePtr_Result AEGetAttributePtr( const AppleEvent&  appleEvent,
	                                            AEKeyword          keyword,
	                                            DescType           desiredType,
	                                            void*              dataPtr,
	                                            std::size_t        maximumSize );
	
	Nucleus::Owned< AEDesc_Data > AEGetAttributeDesc( const AppleEvent&  appleEvent,
	                                                  AEKeyword          keyword,
	                                                  DescType           desiredType = typeWildCard );
	
	AESizeOfAttribute_Result AESizeOfAttribute( const AppleEvent&  appleEvent,
	                                            AEKeyword          keyword );
	
	#pragma mark -
	#pragma mark � Opaque data �
	
	void AEGetDescData( const AEDesc&  desc,
	                    void*          dataPtr,
	                    std::size_t    maximumSize );
	
	inline std::size_t AEGetDescDataSize( const AEDesc& desc )
	{
		return ::AEGetDescDataSize( &desc );
	}
	
	void AEReplaceDescData( DescType     typeCode,
	                        const void*  dataPtr,
	                        std::size_t  dataSize,
	                        AEDesc&      result );
	
	void AEReplaceDescData( DescType                        typeCode,
	                        const void*                     dataPtr,
	                        std::size_t                     dataSize,
	                        Nucleus::Owned< AEDesc_Data >&  result );
	
	
	#pragma mark -
	#pragma mark � AEEventHandlerUPP �
	
	struct AEEventHandlerUPP_Details: Basic_UPP_Details< ::AEEventHandlerUPP,
	                                                     ::AEEventHandlerProcPtr,
	                                                     ::NewAEEventHandlerUPP,
	                                                     ::DisposeAEEventHandlerUPP,
	                                                     ::InvokeAEEventHandlerUPP >
	{
	};
	
	typedef UPP< AEEventHandlerUPP_Details > AEEventHandlerUPP;
	
	//using ::AEEventHandlerProcPtr;
	
	inline Nucleus::Owned< AEEventHandlerUPP > NewAEEventHandlerUPP( ::AEEventHandlerProcPtr p )
	{
		return NewUPP< AEEventHandlerUPP >( p );
	}
	
	inline void DisposeAEEventHandlerUPP( Nucleus::Owned< AEEventHandlerUPP > )
	{
	}
	
	inline void InvokeAEEventHandlerUPP( const AppleEvent& theAppleEvent,
	                                     AppleEvent& reply,
	                                     RefCon handlerRefCon,
	                                     AEEventHandlerUPP userUPP )
	{
		ThrowOSStatus( userUPP( &theAppleEvent, &reply, handlerRefCon ) );
	}
	
	#pragma mark -
	#pragma mark � Powered by DescType_Traits �
	
	class AECoercePtr_Putter
	{
		private:
			DescType fromType;
			DescType toType;
			Nucleus::Owned< AEDesc_Data >& theDesc;
		
		public:
			AECoercePtr_Putter( DescType                        from,
			                    DescType                        to,
			                    Nucleus::Owned< AEDesc_Data >&  desc ) : fromType( from ),
			                                                             toType  ( to   ),
			                                                             theDesc ( desc )
			{
			}
			
			void operator()( const void *begin, const void *end ) const
			{
				theDesc = AECoercePtr( fromType, begin, Detail::Distance( begin, end ), toType );
			}
	};
	
	template < DescType type >
	inline Nucleus::Owned< AEDesc_Data > AECoercePtr( typename DescType_Traits< type >::Parameter  data,
	                                                  DescType                                     toType )
	{
		Nucleus::Owned< AEDesc_Data > result;
		
		DescType_Traits< type >().Put( data,
		                               AECoercePtr_Putter( DescType_Map_Traits< type >::result,
		                                                   toType,
		                                                   result ) );
		
		return result;
	}
	
	
	template < class AEDesc_Type >
	class AECreateDesc_Putter
	{
		private:
			DescType                        theType;
			Nucleus::Owned< AEDesc_Type >&  theDesc;
		
		public:
			AECreateDesc_Putter( DescType                        type,
			                     Nucleus::Owned< AEDesc_Type >&  desc ) : theType( type ),
			                                                              theDesc( desc )
			{
			}
			
			void operator()( const void *begin, const void *end ) const
			{
				theDesc = AECreateDesc< AEDesc_Type >( theType, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < class AEDesc_Type, DescType type >
	inline Nucleus::Owned< AEDesc_Type > AECreateDesc( typename DescType_Traits< type >::Parameter  data )
	{
		Nucleus::Owned< AEDesc_Type > result;
		
		DescType_Traits< type >().Put( data,
		                               AECreateDesc_Putter< AEDesc_Type >( DescType_Map_Traits< type >::result,
		                                                                   result ) );
		
		return result;
	}
	
	
	class AEPutPtr_Putter
	{
		private:
			AEDescList&  theList;
			long         theIndex;
			DescType     theType;
		
		public:
			AEPutPtr_Putter( AEDescList&  list,
			                 long         index,
			                 DescType     type ) : theList ( list  ),
			                                       theIndex( index ),
			                                       theType ( type  )
			{
			}
			
			void operator()( const void *begin, const void *end ) const
			{
				AEPutPtr( theList, theIndex, theType, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline void AEPutPtr( AEDescList&                                  list,
	                      long                                         index,
	                      typename DescType_Traits< type >::Parameter  data )
	{
		DescType_Traits< type >().Put( data,
		                               AEPutPtr_Putter( list,
		                               index,
		                               DescType( DescType_Map_Traits< type >::result ) ) );
	}
	
	template < DescType type, class AEDescList_Type >
	inline void AEPutPtr( Nucleus::Owned< AEDescList_Type >&           list,
	                      long                                         index,
	                      typename DescType_Traits< type >::Parameter  data )
	{
		DescType_Traits< type >().Put( data,
		                               AEPutPtr_Putter( Detail::AEDescEditor< AEDescList_Type >( list ),
		                                                index,
		                                                DescType( DescType_Map_Traits< type >::result ) ) );
	}
	
	
	template < DescType type >
	class AEGetNthPtr_Getter
	{
		private:
			const AEDescList&  theList;
			long               theIndex;
		
		public:
			AEGetNthPtr_Getter( const AEDescList&  list,
			                    long               index ) : theList ( list  ),
			                                                 theIndex( index )
			{
			}
			
			std::size_t size() const
			{
				AESizeOfNthItem_Result info = AESizeOfNthItem( theList, theIndex );
				
				if ( DescType_Traits< type >::hasStaticSize )
				{
					return sizeof (typename DescType_Traits< type >::Buffer);
				}
				
				ASSERT( info.typeCode == type );
				
				return info.dataSize;
			}
			
			void operator()( void *begin, void *end ) const
			{
				AEGetNthPtr( theList, theIndex, type, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline typename DescType_Traits< type >::Result
	AEGetNthPtr( const AEDescList&  listDesc,
	             long               index )
	{
		return DescType_Traits< type >().Get( AEGetNthPtr_Getter< DescType_Map_Traits< type >::result >( listDesc, index ) );
	}
	
	
	class AEPutKeyPtr_Putter
	{
		private:
			AERecord& theRecord;
			AEKeyword theKeyword;
			DescType  theType;
		
		public:
			AEPutKeyPtr_Putter( AERecord&  record,
			                    AEKeyword  keyword,
			                    DescType   type )
			: theRecord ( record  ),
			  theKeyword( keyword ),
			  theType   ( type    )  {}
			
			void operator()( const void *begin, const void *end ) const
			{
				AEPutKeyPtr( theRecord, theKeyword, theType, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline void AEPutKeyPtr( AERecord&                                    record,
	                         AEKeyword                                    keyword,
	                         typename DescType_Traits< type >::Parameter  data )
	{
		DescType_Traits< type >().Put( data,
		                               AEPutKeyPtr_Putter( record,
		                                                   keyword,
		                                                   DescType( DescType_Map_Traits< type >::result ) ) );
	}
	
	template < class AERecord_Type, DescType type >
	inline void AEPutKeyPtr( Nucleus::Owned< AERecord_Type >&             record,
	                         AEKeyword                                    keyword,
	                         typename DescType_Traits< type >::Parameter  data )
	{
		DescType_Traits< type >().Put( data,
		                               AEPutKeyPtr_Putter( Detail::AEDescEditor< AERecord_Type >( record ),
		                                                   keyword,
		                                                   DescType( DescType_Map_Traits< type >::result ) ) );
	}
	
	template < AEKeyword key >
	inline void AEPutKeyPtr( AERecord&                                    record,
	                         typename AEKeyword_Traits< key >::Parameter  data )
	{
		AEKeyword_Traits< key >().Put( data,
		                               AEPutKeyPtr_Putter( record,
		                                                   key,
		                                                   DescType( AEKeyword_Traits< key >::descType ) ) );
	}
	
	template < class AERecord_Type, AEKeyword key >
	inline void AEPutKeyPtr( Nucleus::Owned< AERecord_Type >&             record,
	                         typename AEKeyword_Traits< key >::Parameter  data )
	{
		AEPutKeyPtr< key >( Detail::AEDescEditor< AERecord_Type >( record ), data );
	}
	
	template < AEKeyword key >
	class AEPutKeyPtr_Binding
	{
		private:
			typedef typename AEKeyword_Traits< key >::Parameter Parameter;
			
			Parameter itsData;
		
		public:
			AEPutKeyPtr_Binding( Parameter data ) : itsData( data )  {}
			
			Parameter Data() const  { return itsData; }
	};
	
	template < AEKeyword key >
	inline AEPutKeyPtr_Binding< key > AEPutKeyPtr( typename AEKeyword_Traits< key >::Parameter data )
	{
		return AEPutKeyPtr_Binding< key >( data );
	}
	
	
	template < DescType type >
	class AEGetKeyPtr_Getter
	{
		private:
			const AERecord& theRecord;
			AEKeyword       theKeyword;
		
		public:
			AEGetKeyPtr_Getter( const AERecord&  record,
			                    AEKeyword        keyword ) : theRecord ( record  ),
			                                                 theKeyword( keyword )
			{
			}
			
			std::size_t size() const
			{
				AESizeOfKeyDesc_Result info = AESizeOfKeyDesc( theRecord, theKeyword );
				
				if ( DescType_Traits< type >::hasStaticSize )
				{
					return sizeof (typename DescType_Traits< type >::Buffer);
				}
				
				ASSERT( info.typeCode == type );
				
				return info.dataSize;
			}
			
			void operator()( void *begin, void *end ) const
			{
				AEGetKeyPtr( theRecord, theKeyword, type, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline typename DescType_Traits< type >::Result
	AEGetKeyPtr( const AERecord&  record,
	             AEKeyword        keyword )
	{
		return DescType_Traits< type >().Get( AEGetKeyPtr_Getter< DescType_Map_Traits< type >::result >( record, keyword ) );
	}
	
	template < AEKeyword key >
	inline typename AEKeyword_Traits< key >::Result
	AEGetKeyPtr( const AERecord& record )
	{
		return AEKeyword_Traits< key >().Get( AEGetKeyPtr_Getter< AEKeyword_Traits< key >::descType >( record, key ) );
	}
	
	
	class AEPutParamPtr_Putter
	{
		private:
			AppleEvent&  theAppleEvent;
			AEKeyword    theKeyword;
			DescType     theType;
		
		public:
			AEPutParamPtr_Putter( AppleEvent&  appleEvent,
			                      AEKeyword    keyword,
			                      DescType     type ) : theAppleEvent( appleEvent  ),
			                                            theKeyword   ( keyword     ),
			                                            theType      ( type        )
			{
			}
			
			void operator()( const void *begin, const void *end ) const
			{
				AEPutParamPtr( theAppleEvent, theKeyword, theType, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline void AEPutParamPtr( AppleEvent&                                  appleEvent,
	                           AEKeyword                                    keyword,
	                           typename DescType_Traits< type >::Parameter  data )
	{
		DescType_Traits< type >().Put( data,
		                               AEPutParamPtr_Putter( appleEvent,
		                                                     keyword,
		                                                     DescType( DescType_Map_Traits< type >::result ) ) );
	}
	
	template < DescType type >
	inline void AEPutParamPtr( Nucleus::Owned< AppleEvent >&                appleEvent,
	                           AEKeyword                                    keyword,
	                           typename DescType_Traits< type >::Parameter  data )
	{
		DescType_Traits< type >().Put( data,
		                               AEPutParamPtr_Putter( Detail::AEDescEditor< AppleEvent >( appleEvent ),
		                                                     keyword,
		                                                     DescType( DescType_Map_Traits< type >::result ) ) );
	}
	
	template < AEKeyword key >
	inline void AEPutParamPtr( AppleEvent&                                  appleEvent,
	                           typename AEKeyword_Traits< key >::Parameter  data )
	{
		AEKeyword_Traits< key >().Put( data,
		                               AEPutParamPtr_Putter( appleEvent,
		                                                     key,
		                                                     DescType( AEKeyword_Traits< key >::descType ) ) );
	}
	
	template < AEKeyword key >
	inline void AEPutParamPtr( Nucleus::Owned< AppleEvent >&                appleEvent,
	                           typename AEKeyword_Traits< key >::Parameter  data )
	{
		AEPutParamPtr< key >( Detail::AEDescEditor< AppleEvent >( appleEvent ), data );
	}
	
	
	template < DescType type >
	class AEGetParamPtr_Getter
	{
		private:
			const AppleEvent&  theAppleEvent;
			AEKeyword          theKeyword;
		
		public:
			AEGetParamPtr_Getter( const AppleEvent&  appleEvent,
			                      AEKeyword          keyword ) : theAppleEvent( appleEvent ),
			                                                     theKeyword   ( keyword    )
			{
			}
			
			std::size_t size() const
			{
				AESizeOfParam_Result info = AESizeOfParam( theAppleEvent, theKeyword );
				
				if ( DescType_Traits< type >::hasStaticSize )
				{
					return sizeof (typename DescType_Traits< type >::Buffer);
				}
				
				ASSERT( info.typeCode == type );
				
				return info.dataSize;
			}
			
			void operator()( void *begin, void *end ) const
			{
				AEGetParamPtr( theAppleEvent, theKeyword, type, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline typename DescType_Traits< type >::Result
	AEGetParamPtr( const AppleEvent&  appleEvent,
	               AEKeyword          keyword )
	{
		return DescType_Traits< type >().Get( AEGetParamPtr_Getter< DescType_Map_Traits< type >::result >( appleEvent, keyword ) );
	}
	
	template < AEKeyword key >
	inline typename AEKeyword_Traits< key >::Result
	AEGetParamPtr( const AppleEvent& appleEvent )
	{
		return AEKeyword_Traits< key >().Get( AEGetParamPtr_Getter< AEKeyword_Traits< key >::descType >( appleEvent, key ) );
	}
	
	
	class AEPutAttributePtr_Putter
	{
		private:
			AppleEvent&  theAppleEvent;
			AEKeyword    theKeyword;
			DescType     theType;
		
		public:
			AEPutAttributePtr_Putter( AppleEvent&  appleEvent,
			                          AEKeyword    keyword,
			                          DescType     type ) : theAppleEvent( appleEvent  ),
			                                                theKeyword   ( keyword     ),
			                                                theType      ( type        )
			{
			}
			
			void operator()( const void *begin, const void *end ) const
			{
				AEPutAttributePtr( theAppleEvent, theKeyword, theType, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline void AEPutAttributePtr( AppleEvent&                                  appleEvent,
	                               AEKeyword                                    keyword,
	                               typename DescType_Traits< type >::Parameter  data )
	{
		DescType_Traits< type >().Put( data,
		                               AEPutAttributePtr_Putter( appleEvent,
		                                                         keyword,
		                                                         DescType( DescType_Map_Traits< type >::result ) ) );
	}
	
	template < DescType type >
	inline void AEPutAttributePtr( Nucleus::Owned< AppleEvent >&                appleEvent,
	                               AEKeyword                                    keyword,
	                               typename DescType_Traits< type >::Parameter  data )
	{
		DescType_Traits< type >().Put( data,
		                               AEPutAttributePtr_Putter( Detail::AEDescEditor< AppleEvent >( appleEvent ),
		                                                         keyword,
		                                                         DescType( DescType_Map_Traits< type >::result ) ) );
	}
	
	template < AEKeyword key >
	inline void AEPutAttributePtr( AppleEvent&                                  appleEvent,
	                               typename AEKeyword_Traits< key >::Parameter  data )
	{
		AEKeyword_Traits< key >().Put( data,
		                               AEPutAttributePtr_Putter( appleEvent,
		                                                         key,
		                                                         DescType( AEKeyword_Traits< key >::descType ) ) );
	}
	
	template < AEKeyword key >
	inline void AEPutAttributePtr( Nucleus::Owned< AppleEvent >&                appleEvent,
	                               typename AEKeyword_Traits< key >::Parameter  data )
	{
		AEPutAttributePtr< key >( Detail::AEDescEditor< AppleEvent >( appleEvent ), data );
	}
	
	
	template < DescType type >
	class AEGetAttributePtr_Getter
	{
		private:
			const AppleEvent& theAppleEvent;
			AEKeyword         theKeyword;
		
		public:
			AEGetAttributePtr_Getter( const AppleEvent&  appleEvent,
			                          AEKeyword          keyword ) : theAppleEvent( appleEvent ),
			                                                         theKeyword   ( keyword    )
			{
			}
			
			std::size_t size() const
			{
				AESizeOfAttribute_Result info = AESizeOfAttribute( theAppleEvent, theKeyword );
				
				if ( DescType_Traits< type >::hasStaticSize )
				{
					return sizeof (typename DescType_Traits< type >::Buffer);
				}
				
				ASSERT( info.typeCode == type );
				
				return info.dataSize;
			}
			
			void operator()( void *begin, void *end ) const
			{
				AEGetAttributePtr( theAppleEvent, theKeyword, type, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline typename DescType_Traits< type >::Result
	AEGetAttributePtr( const AppleEvent&  appleEvent,
	                   AEKeyword          keyword )
	{
		return DescType_Traits< type >().Get( AEGetAttributePtr_Getter< DescType_Map_Traits< type >::result >( appleEvent, keyword ) );
	}
	
	template < AEKeyword key >
	inline typename AEKeyword_Traits< key >::Result
	AEGetAttributePtr( const AppleEvent& appleEvent )
	{
		return AEKeyword_Traits< key >().Get( AEGetAttributePtr_Getter< AEKeyword_Traits< key >::descType >( appleEvent, key ) );
	}
	
	
	class AEGetDescData_Getter
	{
		private:
			const AEDesc& theDesc;
		
		public:
			AEGetDescData_Getter( const AEDesc& desc = AEInitializeDesc() ) : theDesc( desc )
			{
			}
			
			std::size_t size() const  { return AEGetDescDataSize( theDesc ); }
			
			void operator()( void *begin, void *end ) const
			{
				AEGetDescData( theDesc, begin, Detail::Distance( begin, end ) );
			}
	};
	
	template < DescType type >
	inline typename DescType_Traits< type >::Result
	AEGetDescData( const AEDesc&  desc,
	               DescType       requiredType = DescType_Map_Traits< type >::result )
	{
		ASSERT( requiredType == typeWildCard || requiredType == desc.descriptorType );
		
		(void) requiredType;
		
		return DescType_Traits< type >().Get( AEGetDescData_Getter( desc ) );
	}
	
	template < DescType type >
	inline typename DescType_Traits< type >::Result AECoerceDescData( const AEDesc& desc )
	{
		return AEGetDescData< type >( AECoerceDesc( desc, DescType_Map_Traits< type >::result ) );
	}
	
	
	class AEReplaceDescData_Putter
	{
		private:
			DescType                        theType;
			Nucleus::Owned< AEDesc_Data >&  theDesc;
		
		public:
			AEReplaceDescData_Putter( DescType                        type,
			                          Nucleus::Owned< AEDesc_Data >&  desc ) : theType( type ),
			                                                                   theDesc( desc )
			{
			}
			
			void operator()( const void *begin, const void *end ) const
			{
				AEReplaceDescData( theType, begin, Detail::Distance( begin, end ), theDesc );
			}
	};
	
	template < DescType type >
	inline void AEReplaceDescData( typename DescType_Traits< type >::Parameter  data,
	                               AEDesc&                                      result )
	{
		DescType_Traits< type >().Put( data,
		                               AEReplaceDescData_Putter( DescType_Map_Traits< type >::result,
		                                                         result ) );
	}
	
	template < DescType type >
	inline void AEReplaceDescData( typename DescType_Traits< type >::Parameter  data,
	                               Nucleus::Owned< AEDesc_Data >&               result )
	{
		DescType_Traits< type >().Put( data,
		                               AEReplaceDescData_Putter( DescType_Map_Traits< type >::result,
		                                                         Detail::AEDescEditor< AEDesc_Data >( result ) ) );
	}
	
}

#endif

