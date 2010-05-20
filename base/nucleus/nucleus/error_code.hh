// nucleus/error_code.hh
// ---------------------

// Written 2002-2009 by Lisa Lippincott and Joshua Juran.
//
// This code was written entirely by the above contributors, who place it
// in the public domain.


/*
	One of the more distressing problems arising when using C code from C++
	is that C functions return error codes, and C++ code gets along better
	with exceptions.  A common approach to makng the transition is to wrap
	error codes in a class which is then thrown.
	
	But this approach doesn't produce exceptions with the fine granularity
	one expects from C++ exceptions.  Often one must catch the error class,
	test the code it contains, and rethrow those exceptions one didn't want
	to catch.
	
	These templates extend the error class approch to provide fine-grained
	exception throwing.  Consider an error code type error_number, and an
	exception class wrapper ErrorClass for that type.

	
	The classes generated by the template
	
		template < class ErrorClass, error_number number > class error_code
	
	each represent a particular, numbered error.   These classes all
	descend from ErrorClass, and initialize that base class with their
	particular number.
	
	
	The function template
	
		template < class ErrorClass > void throw_error_code( ErrorClass n )
	
	throws an exception representing the error given by n.  The type of the
	exception thrown is either ErrorClass or a subclass of ErrorClass.
		
		-- If the error number n has been registered, the exception has type
				error_code< ErrorClass, n >
		-- Otherwise, the exception thrown has type ErrorClass.
	
	In most cases, this function isn't called directly; instead, one calls a
	wrapper function which filters out those numbers which indicate success.
	
	
	The functions
	
		template < class ErrorClass, error_number number > void register_error_code()
	
	regsiter particular error numbers, ensuring that they will be thrown as
	error_code< ErrorClass, number > by throw_error_code< ErrorClass >.
	
	
	--- Advanced usage ---
	
	The error_number type is inferred from the ErrorClass type by a traits class
	
		template < class ErrorClass >
		struct error_class_traits
		{
			typedef typename ErrorClass::error_number error_number;
		};
	
	Error classes may specify their underlying error code type with a typedef,
	or one may use this sceme with an existing error class by specializing
	error_class_traits.
	
	The template function convert() is used to convert error_number to ErrorClass
	and vice versa.  By default, it attempts an implicit conversion; if
	these conversions are not allowed, convert() may be extended to provide
	the necessary conversions.
	
	The class template error_code may be specialized to provide a richer
	representation of particular errors.  For example, one might use a
	specialization derived from both ErrorClass and std::bad_alloc to
	represent a memory allocation error.

	Likewise, the function template used to throw the specific exceptions,
	
		template < class Exception > void throw_exception()
	
	may be specialized to modify the way a perticular code is thrown.
*/

#ifndef NUCLEUS_ERRORCODE_HH
#define NUCLEUS_ERRORCODE_HH

#ifndef NUCLEUS_RICH_ERRORCODES
  #if defined( __MWERKS__ )
	 #define NUCLEUS_RICH_ERRORCODES 0
  #else
	 #define NUCLEUS_RICH_ERRORCODES 1
  #endif
#endif

// Standard C++
#if NUCLEUS_RICH_ERRORCODES
#include <map>
#endif

// Debug
#if TARGET_CONFIG_DEBUGGING  &&  !defined( NUCLEUS_DEBUGGING_CONTEXT )
#include "recall/backtrace.hh"
#define NUCLEUS_DEBUGGING_CONTEXT  ::recall::debugging_context
#endif

// Nucleus
#include "nucleus/convert.hh"


#if NUCLEUS_RICH_ERRORCODES
	
	#define DEFINE_ERRORCODE( error_type, c_name, new_name )          \
		                                                              \
		typedef ::nucleus::error_code< error_type, c_name > new_name
	
#else
	
	#define DEFINE_ERRORCODE( error_type, c_name, new_name )       \
		                                                           \
		inline ::nucleus::error_code< error_type > new_name()      \
		{                                                          \
			return ::nucleus::error_code< error_type >( c_name );  \
		}
	
#endif


namespace nucleus
{
	
#ifdef NUCLEUS_DEBUGGING_CONTEXT
	
	typedef NUCLEUS_DEBUGGING_CONTEXT debugging_context;
	
#endif
	
	template < class ErrorClass >
	struct error_class_traits
	{
		typedef typename ErrorClass::error_number error_number;
	};   
	
	// The error number is passed as a template parameter for rich error codes
	// and as a constructor argument otherwise.
	template < class ErrorClass
	           #if NUCLEUS_RICH_ERRORCODES
	           ,
	           typename error_class_traits< ErrorClass >::error_number number
	           #endif
	           >
	class error_code : public ErrorClass
	                   #ifdef NUCLEUS_DEBUGGING_CONTEXT
	                   ,
	                   public debugging_context
	                   #endif
	{
		public:
			error_code(
			            #if !NUCLEUS_RICH_ERRORCODES
			            typename error_class_traits< ErrorClass >::error_number number
			            #endif
			             )
			:
				ErrorClass( convert< ErrorClass >( number ) )
			{
			}
	};
	
	template < class Exception >
	void throw_exception()
	{
		throw Exception();
	}

	
#if NUCLEUS_RICH_ERRORCODES
	
	template < class ErrorClass >
	class error_code_thrower
	{
		private:
			typedef typename error_class_traits< ErrorClass >::error_number error_number;
			
			typedef std::map< error_number, void(*)() > map_type;
		
			map_type map;

			// not implemented:
			error_code_thrower           ( const error_code_thrower& );
			error_code_thrower& operator=( const error_code_thrower& );
		
		public:
			error_code_thrower()
			{
			}
			
			template < error_number number >
			void register_error()
			{
				typedef error_code< ErrorClass, number > rich_error_code;
				
				map[ number ] = nucleus::throw_exception< rich_error_code >;
			}
			
			void throw_exception( ErrorClass error ) const
			{
				const error_number number = convert< error_number >( error );
				
				typename map_type::const_iterator found = map.find( number );
				
				if ( found != map.end() )
				{
					return found->second();
				}
				
				throw error;
			}
	};


	template < class ErrorClass >
	error_code_thrower< ErrorClass >& the_global_error_code_thrower()
	{
		static error_code_thrower< ErrorClass > global_error_code_thrower;
		
		return global_error_code_thrower;
	}
	
#endif
	
	template < class ErrorClass, typename error_class_traits< ErrorClass >::error_number number >
	inline void register_error_code()
	{
	#if NUCLEUS_RICH_ERRORCODES
		
		{
			the_global_error_code_thrower< ErrorClass >().template register_error< number >();
		}
		
	#endif
	}
	
	template < class ErrorClass >
	inline void throw_error_code( ErrorClass error )
	{
	#if NUCLEUS_RICH_ERRORCODES
		
		the_global_error_code_thrower< ErrorClass >().throw_exception( error );
		
	#else
		
		throw error_code< ErrorClass >( error );
		
	#endif
	}
}

namespace nucleus
{
	
	template < class ErrorClass, typename error_class_traits< ErrorClass >::error_number number >
	struct error_code_end_of_enumeration
	{
	#if NUCLEUS_RICH_ERRORCODES
		
		typedef error_code< ErrorClass, number > end_of_enumeration;
		
		static bool exception_is_end_of_enumeration( const end_of_enumeration& err )
		{
			return true;
		}
		
	#else
		
		typedef error_code< ErrorClass > end_of_enumeration;
		
		static bool exception_is_end_of_enumeration( const end_of_enumeration& err )
		{
			return err == number;
		}
		
	#endif
	};
	
}

#endif

