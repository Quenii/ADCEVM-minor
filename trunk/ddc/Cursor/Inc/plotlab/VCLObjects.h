//---------------------------------------------------------------------------

#ifndef VCLObjectsH
#define VCLObjectsH
//---------------------------------------------------------------------------
//#define USE_STD_STRING

#ifdef USE_STD_STRING
  #include <string>
  typedef std::string CTString;
  typedef char _VCL_TCHAR;

#else
  #include <afx.h>
  typedef CString CTString;
  typedef _TCHAR _VCL_TCHAR; 

#endif

#include <VCLLoader.h>
//---------------------------------------------------------------------------
class CVCLObject;
//---------------------------------------------------------------------------
template <class TObject> class CVCLProperty
{
protected :
	TObject   &Object;
	const _VCL_TCHAR	 *PropertyName;
	CTString	  CPropertyName;

public :
	CVCLProperty( CVCLProperty<TObject> &Other ) : 
		Object( Other.Object ), CPropertyName( Other.CPropertyName ) 
			{
          #ifdef USE_STD_STRING
			PropertyName = CPropertyName.c_str();

		  #else
			PropertyName = CPropertyName.LockBuffer();

		  #endif
			}

	CVCLProperty( TObject &Object, CTString PropertyName ) : 
		Object( Object ), CPropertyName( PropertyName ) 
			{
          #ifdef USE_STD_STRING
			PropertyName = CPropertyName.c_str();

		  #else
			PropertyName = CPropertyName.LockBuffer();

		  #endif
			}

	virtual ~CVCLProperty() 
			{  
          #ifndef USE_STD_STRING
			CPropertyName.UnlockBuffer();
		  #endif
			}

public :
	CVCLProperty<TObject> & operator = ( int Value );
	CVCLProperty<TObject> & operator = ( long Value );
	CVCLProperty<TObject> & operator = ( __int64 Value );
	CVCLProperty<TObject> & operator = ( unsigned int Value );
	CVCLProperty<TObject> & operator = ( unsigned long Value );
	CVCLProperty<TObject> & operator = ( float Value );
	CVCLProperty<TObject> & operator = ( double Value );
	CVCLProperty<TObject> & operator = ( CTString Value );
	CVCLProperty<TObject> & operator = ( TObject &Value );
	CVCLProperty<TObject> & operator = ( void *Value );

public :
	bool operator == ( long Value );
	bool operator == ( unsigned long Value );
	bool operator == ( int Value );
	bool operator == ( unsigned int Value );
	bool operator == ( __int64 Value );
	bool operator == ( float Value );
	bool operator == ( double Value );
	bool operator == ( CTString Value );
	bool operator == ( TObject &Value );

	bool operator != ( int Value );
	bool operator != ( unsigned int Value );
	bool operator != ( long Value );
	bool operator != ( unsigned long Value );
	bool operator != ( __int64 Value );
	bool operator != ( float Value );
	bool operator != ( double Value );
	bool operator != ( CTString Value );
	bool operator != ( TObject &Value );

public :
	operator CTString ();
	operator int	 ();
	operator unsigned int();
	operator long	 ();
	operator unsigned long();
	operator __int64	 ();
	operator bool	 ();
	operator float	 ();
	operator double	 ();
	operator TObject ();

public :
	CTString		AsString();
	int				AsInt();
	unsigned int	AsUnsignedInt();
	__int64			AsInt64();
	bool			AsBool();
	float			AsFloat();
	double			AsDouble();
	TObject			AsObject();
};
//---------------------------------------------------------------------------
/*
inline int __stdcall GOnVCLException( void *CustomData, char *EexceptionMessage )
{
	throw EexceptionMessage;
}
*/
//---------------------------------------------------------------------------
inline VCLHANDLE __stdcall VCL_LoadLibrary( const wchar_t * LibraryFileName )
{
    char    ch[ 2000 ];

//	VCL_SetExceptionCallback( GOnVCLException, NULL );

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, LibraryFileName, 2000 );
#else
    wcstombs( ch, LibraryFileName, 2000 );
#endif

    return VCL_LoadLibrary( ch );
}

inline VCLHANDLE __stdcall VCL_NewComponent( const wchar_t * ComponentType )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, ComponentType, 2000 );
#else
    wcstombs( ch, ComponentType, 2000 );
#endif

    return VCL_NewComponent( ch, NULL, false );
}

inline VCLHANDLE __stdcall VCL_NewObject( const wchar_t * ComponentType )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, ComponentType, 2000 );
#else
    wcstombs( ch, ComponentType, 2000 );
#endif

	return VCL_NewComponent( ch, NULL, false );
}

inline VCLHANDLE __stdcall VCL_NewControl( HWND ParentWindow, const wchar_t * ControlType )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, ControlType, 2000 );
#else
    wcstombs( ch, ControlType, 2000 );
#endif

	return VCL_NewControl( ParentWindow, ch, NULL, false );
}

inline VCLHANDLE __stdcall VCL_NewControlSize( HWND ParentWindow, const wchar_t * ControlType, int Left, int Top, int Width, int Height )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, ControlType, 2000 );
#else
    wcstombs( ch, ControlType, 2000 );
#endif

	return VCL_NewControlSize( ParentWindow, ch, Left, Top, Width, Height, NULL, false );
}

inline int __stdcall VCL_ConnectPins( VCLHANDLE Object1, const wchar_t * Pin1Name, VCLHANDLE Object2, const wchar_t * Pin2Name )
{
    char    str1[ 2000 ];
    char    str2[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, str1, 2000, Pin1Name, 2000 );
    wcstombs_s( &i, str2, 2000, Pin2Name, 2000 );
#else
    wcstombs( str1, Pin1Name, 2000 );
    wcstombs( str2, Pin2Name, 2000 );
#endif

    return VCL_ConnectPins( Object1, str1, Object2, str2 );
}

inline int	__stdcall VCL_ConnectAfterPins( VCLHANDLE Object1, const wchar_t * Pin1Name, VCLHANDLE Object2, const wchar_t * Pin2Name, VCLHANDLE AfterObject, const wchar_t * AfterPinName )
{
    char    str1[ 2000 ];
    char    str2[ 2000 ];
    char    str3[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, str1, 2000, Pin1Name, 2000 );
    wcstombs_s( &i, str2, 2000, Pin2Name, 2000 );
    wcstombs_s( &i, str3, 2000, AfterPinName, 2000 );
#else
    wcstombs( str1, Pin1Name, 2000 );
    wcstombs( str2, Pin2Name, 2000 );
    wcstombs( str3, AfterPinName, 2000 );
#endif

    return VCL_ConnectAfterPins( Object1, str1, Object2, str2, AfterObject, str3 );
}

inline int	__stdcall VCL_DisconnectPin( VCLHANDLE Object, const wchar_t * PinName )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PinName, 2000 );
#else
    wcstombs( ch, PinName, 2000 );
#endif

	return VCL_DisconnectPin( Object, ch );
}

inline int	__stdcall VCL_PulsePin( VCLHANDLE Object, const wchar_t * PinName )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PinName, 2000 );
#else
    wcstombs( ch, PinName, 2000 );
#endif

	return VCL_PulsePin( Object, ch );
}

inline int	__stdcall VCL_SetMethodProperty( VCLHANDLE Object, const wchar_t * PropertyName, void *Function, void *Data )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif

	return VCL_SetMethodProperty( Object, ch, Function, Data );
}

inline int	__stdcall VCL_SetMethodPropertyAndType( VCLHANDLE Object, const wchar_t * PropertyName, void *Function, void *Data, int FunctionIndex )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif

	return VCL_SetMethodPropertyAndType( Object, ch, Function, Data, FunctionIndex );
}

inline int	__stdcall VCL_GetMethodProperty( VCLHANDLE Object, const wchar_t * PropertyName,  void **Function, void **Data )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif

	return VCL_GetMethodProperty( Object, ch, Function, Data );
}

inline VCLHANDLE __stdcall VCL_CreateAnsiString( wchar_t *str )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, str, 2000 );
#else
    wcstombs( ch, str, 2000 );
#endif
    return VCL_CreateAnsiString( ch );
}

inline int __stdcall VCL_SetStringProperty( VCLHANDLE Object, const wchar_t * PropertyName, const wchar_t * PropertyValue )
{
    char    ch[ 2000 ];
    char    chv[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
    wcstombs_s( &i, chv, 2000, PropertyValue, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
    wcstombs( chv, PropertyValue, 2000 );
#endif
    return VCL_SetStringProperty( Object, ch, chv );
}

inline int __stdcall VCL_SetIntegerProperty( VCLHANDLE Object, const wchar_t * PropertyName, int PropertyValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_SetIntegerProperty( Object, ch, PropertyValue );
}

inline int __stdcall VCL_SetInteger64Property( VCLHANDLE Object, const wchar_t * PropertyName, __int64 PropertyValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_SetInteger64Property( Object, ch, PropertyValue );
}

inline int __stdcall VCL_SetFloatProperty( VCLHANDLE Object, const wchar_t * PropertyName, float PropertyValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_SetFloatProperty( Object, ch, PropertyValue );
}

inline int __stdcall VCL_SetDoubleProperty( VCLHANDLE Object, const wchar_t * PropertyName, double PropertyValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_SetDoubleProperty( Object, ch, PropertyValue );
}

inline int __stdcall VCL_SetObjectProperty( VCLHANDLE Object, const wchar_t * PropertyName, VCLHANDLE PropertyValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_SetObjectProperty( Object, ch, PropertyValue );
}
//---------------------------------------------------------------------------
inline wchar_t* __stdcall VCL_GetStringProperty( VCLHANDLE Object, const wchar_t * PropertyName, VCLHANDLE *StringHandler )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    char *rtn = VCL_GetStringProperty( Object, ch, StringHandler );

    size_t Length = strlen( rtn ) + 1;
    wchar_t *UnicodeRtn = new wchar_t[ Length ];
#if _MSC_VER >= 1400
    mbstowcs_s( &i, UnicodeRtn, Length, rtn, Length );  
#else
    mbstowcs( UnicodeRtn, rtn, Length ); 
#endif

    return UnicodeRtn;
}
//---------------------------------------------------------------------------
inline int __stdcall VCL_GetIntegerProperty( VCLHANDLE Object, const wchar_t * PropertyName, int *ReturnValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_GetIntegerProperty( Object, ch, ReturnValue );
}
//---------------------------------------------------------------------------
inline int __stdcall VCL_GetInteger64Property( VCLHANDLE Object, const wchar_t * PropertyName, __int64 *ReturnValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_GetInteger64Property( Object, ch, ReturnValue );
}
//---------------------------------------------------------------------------
inline int __stdcall VCL_GetFloatProperty( VCLHANDLE Object, const wchar_t * PropertyName, float *ReturnValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_GetFloatProperty( Object, ch, ReturnValue );
}
//---------------------------------------------------------------------------
inline int __stdcall VCL_GetDoubleProperty( VCLHANDLE Object, const wchar_t * PropertyName, double *ReturnValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_GetDoubleProperty( Object, ch, ReturnValue );
}
//---------------------------------------------------------------------------
inline int __stdcall VCL_GetObjectProperty( VCLHANDLE Object, const wchar_t * PropertyName,  VCLHANDLE *ReturnValue )
{
    char    ch[ 2000 ];

#if _MSC_VER >= 1400
    size_t   i;
    wcstombs_s( &i, ch, 2000, PropertyName, 2000 );
#else
    wcstombs( ch, PropertyName, 2000 );
#endif
    return VCL_GetObjectProperty( Object, ch, ReturnValue );
}
//---------------------------------------------------------------------------
class CVCLProperties
{
    friend class CVCLObject;

protected :
	mutable CVCLObject *Object;

public :
	CVCLProperties() : Object( NULL ) {}

public :
	CVCLProperty<CVCLObject> operator [] ( const CTString Name ) const
	{
		return CVCLProperty<CVCLObject>( *Object, Name );
	}
};
//---------------------------------------------------------------------------
class CVCLObject
{
protected :
    VCLHANDLE   Handle;

protected :
    bool        OwnsHandle;

public :
    CVCLObject() :
		Handle( NULL ),
		OwnsHandle( false )
	{
		Properties.Object = this;
	}

    CVCLObject( CTString TypeName, bool AsComponent = true )
	{
		OwnsHandle = true;

    #ifdef USE_STD_STRING
        const char * __1_Param1 = TypeName.c_str();

    #else
      #ifdef _UNICODE
        int __1_Length = TypeName.GetLength();
        char * __1_Param1 = new char[ __1_Length * 2 + 1 ];
        wchar_t * __1_wch_ = TypeName.LockBuffer();
       #if _MSC_VER >= 1400
        size_t   __1_i_;
        wcstombs_s( &__1_i_, __1_Param1, __1_Length * 2, __1_wch_, __1_Length );
       #else
        wcstombs( __1_Param1, __1_wch_, __1_Length );
       #endif
      #else
        char * __1_Param1 = TypeName.LockBuffer();
      #endif
    #endif

		if( AsComponent )
		    Handle = VCL_NewComponent( __1_Param1, NULL, false );

		else
		    Handle = VCL_NewObject( __1_Param1 );

    #ifndef USE_STD_STRING
      #ifdef _UNICODE
        delete []__1_Param1;
      #endif
		TypeName.UnlockBuffer();
    #endif
		if( ! Handle )
	        throw CTString( "Unable to create object : " ) + TypeName;
	}

	CVCLObject( VCLHANDLE Handle, bool OwnsHandle = false ) :
	    Handle( Handle ), OwnsHandle( OwnsHandle )
	{
		Properties.Object = this;
	}

    virtual ~CVCLObject()
	{
		if( OwnsHandle )
			VCL_Delete( Handle );

	}

public :
	const CVCLProperties	Properties;

public :
	virtual VCLHANDLE    GetHandle() { return Handle; }

public :
	bool ConnectPin( CTString PinName, CVCLObject &Other, CTString OtherPinName )
	{
    #ifdef USE_STD_STRING
		bool Result = VCL_ConnectPins( Handle, PinName.c_str(), Other.Handle, OtherPinName.c_str() ) != 0;
	#else
		bool Result = VCL_ConnectPins( Handle, PinName.LockBuffer(), Other.Handle, OtherPinName.LockBuffer() ) != 0;
		PinName.UnlockBuffer();
		OtherPinName.UnlockBuffer();
	#endif
		return Result;
	}

	bool ConnectAfterPin( CTString PinName, CVCLObject &Other, CTString OtherPinName, CVCLObject &AfterPinObject, CTString AfterPinName )
	{
    #ifdef USE_STD_STRING
		bool Result = VCL_ConnectAfterPins( Handle, PinName.c_str(), Other.Handle, OtherPinName.c_str(), AfterPinObject.Handle, AfterPinName.c_str() ) != 0;
	#else
		bool Result = VCL_ConnectAfterPins( Handle, PinName.LockBuffer(), Other.Handle, OtherPinName.LockBuffer(), AfterPinObject.Handle, AfterPinName.LockBuffer() ) != 0;
		PinName.UnlockBuffer();
		OtherPinName.UnlockBuffer();
		AfterPinName.UnlockBuffer();
	#endif
		return Result;
	}

	bool DisconnectPin( CTString PinName )
	{
    #ifdef USE_STD_STRING
		bool Result = VCL_DisconnectPin( Handle, PinName.c_str() ) != 0;
	#else
		bool Result = VCL_DisconnectPin( Handle, PinName.LockBuffer() ) != 0;
		PinName.UnlockBuffer();
	#endif
		return Result;
	}

	bool PulsePin( CTString PinName )
	{
    #ifdef USE_STD_STRING
		bool Result = VCL_PulsePin( Handle, PinName.c_str() ) != 0;
	#else
		bool Result = VCL_PulsePin( Handle, PinName.LockBuffer() ) != 0;
		PinName.UnlockBuffer();
	#endif
		return Result;
	}

protected:
	bool SetEventInt( CTString EventName, void *CallBackFunction, void *UserData )
	{
    #ifdef USE_STD_STRING
		bool Result = VCL_SetMethodProperty( Handle, EventName.c_str(), CallBackFunction, UserData ) != 0;
	#else
		bool Result = VCL_SetMethodProperty( Handle, EventName.LockBuffer(), CallBackFunction, UserData ) != 0;
		EventName.UnlockBuffer();
	#endif
		return Result;
	}

	bool SetEventAndTypeInt( CTString EventName, void *CallBackFunction, void *UserData, int FunctionIndex )
	{
    #ifdef USE_STD_STRING
		bool Result = VCL_SetMethodPropertyAndType( Handle, EventName.c_str(), CallBackFunction, UserData, FunctionIndex ) != 0;
	#else
		bool Result = VCL_SetMethodPropertyAndType( Handle, EventName.LockBuffer(), CallBackFunction, UserData, FunctionIndex ) != 0;
		EventName.UnlockBuffer();
	#endif
		return Result;
	}

public :
	template< class T, class TR > bool SetEvent( CTString EventName, TR (__stdcall T::*CallBackFunction)(), T *Instance, int FuncIndex = -1 )
	{
		typedef TR (__stdcall T::*TTCallBackFunction)();
		TTCallBackFunction Ptr1 = (TTCallBackFunction)CallBackFunction;
		TTCallBackFunction *Ptr2 = &Ptr1;
		void **Ptr = (void **)Ptr2;
		return SetEventAndTypeInt( EventName, *Ptr, Instance, FuncIndex );
	}

	template< class T, class TR, class T1 > bool SetEvent( CTString EventName, TR (__stdcall T::*CallBackFunction)( T1 ), T *Instance, int FuncIndex = -1 )
	{
		typedef TR (__stdcall T::*TTCallBackFunction)();
		TTCallBackFunction Ptr1 = (TTCallBackFunction)CallBackFunction;
		TTCallBackFunction *Ptr2 = &Ptr1;
		void **Ptr = (void **)Ptr2;
		return SetEventAndTypeInt( EventName, *Ptr, Instance, FuncIndex );
	}

	template< class T, class TR, class T1, class T2 > bool SetEvent( CTString EventName, TR (__stdcall T::*CallBackFunction)( T1, T2 ), T *Instance, int FuncIndex = -1 )
	{
		typedef TR (__stdcall T::*TTCallBackFunction)();
		TTCallBackFunction Ptr1 = (TTCallBackFunction)CallBackFunction;
		TTCallBackFunction *Ptr2 = &Ptr1;
		void **Ptr = (void **)Ptr2;
		return SetEventAndTypeInt( EventName, *Ptr, Instance, FuncIndex );
	}

	template< class T, class TR, class T1, class T2, class T3 > bool SetEvent( CTString EventName, TR (__stdcall T::*CallBackFunction)( T1, T2, T3 ), T *Instance, int FuncIndex = -1 )
	{
		typedef TR (__stdcall T::*TTCallBackFunction)();
		TTCallBackFunction Ptr1 = (TTCallBackFunction)CallBackFunction;
		TTCallBackFunction *Ptr2 = &Ptr1;
		void **Ptr = (void **)Ptr2;
		return SetEventAndTypeInt( EventName, *Ptr, Instance, FuncIndex );
	}

	template< class T, class TR, class T1, class T2, class T3, class T4 > bool SetEvent( CTString EventName, TR (__stdcall T::*CallBackFunction)( T1, T2, T3, T4 ), T *Instance, int FuncIndex = -1 )
	{
		typedef TR (__stdcall T::*TTCallBackFunction)();
		TTCallBackFunction Ptr1 = (TTCallBackFunction)CallBackFunction;
		TTCallBackFunction *Ptr2 = &Ptr1;
		void **Ptr = (void **)Ptr2;
		return SetEventAndTypeInt( EventName, *Ptr, Instance, FuncIndex );
	}

	template< class T, class TR, class T1, class T2, class T3, class T4, class T5 > bool SetEvent( CTString EventName, TR (__stdcall T::*CallBackFunction)( T1, T2, T3, T4, T5 ), T *Instance, int FuncIndex = -1 )
	{
		typedef TR (__stdcall T::*TTCallBackFunction)();
		TTCallBackFunction Ptr1 = (TTCallBackFunction)CallBackFunction;
		TTCallBackFunction *Ptr2 = &Ptr1;
		void **Ptr = (void **)Ptr2;
		return SetEventAndTypeInt( EventName, *Ptr, Instance, FuncIndex );
	}

	template< class T, class TR, class T1, class T2, class T3, class T4, class T5, class T6 > bool SetEvent( CTString EventName, TR (__stdcall T::*CallBackFunction)( T1, T2, T3, T4, T5, T6 ), T *Instance, int FuncIndex = -1 )
	{
		typedef TR (__stdcall T::*TTCallBackFunction)();
		TTCallBackFunction Ptr1 = (TTCallBackFunction)CallBackFunction;
		TTCallBackFunction *Ptr2 = &Ptr1;
		void **Ptr = (void **)Ptr2;
		return SetEventAndTypeInt( EventName, *Ptr, Instance, FuncIndex );
	}

/*
	template< class T, class TR, class T1, class T2, class T3, class T4, class T5, class T6, class T7 > bool SetEvent( CTString EventName, TR (__stdcall T::*CallBackFunction)( T1, T2, T3, T4, T5, T6, T7 ), T *Instance )
	{
		typedef TR (__stdcall T::*TTCallBackFunction)();
		TTCallBackFunction Ptr1 = (TTCallBackFunction)CallBackFunction;
		TTCallBackFunction *Ptr2 = &Ptr1;
		void **Ptr = (void **)Ptr2;
		return SetEventInt( EventName, *Ptr, Instance );
	}
*/
	bool GetEvent( CTString EventName, void *&CallBackFunction, void *&UserData )
	{
    #ifdef USE_STD_STRING
		bool Result = VCL_GetMethodProperty( Handle, EventName.c_str(), &CallBackFunction, &UserData ) != 0;
	#else
		bool Result = VCL_GetMethodProperty( Handle, EventName.LockBuffer(), &CallBackFunction, &UserData ) != 0;
		EventName.UnlockBuffer();
	#endif
		return Result;
	}

	bool ClearEvent( CTString EventName )
	{
    #ifdef USE_STD_STRING
		bool Result = VCL_SetMethodProperty( Handle, EventName.c_str(), NULL, NULL ) != 0;
	#else
		bool Result = VCL_SetMethodProperty( Handle, EventName.LockBuffer(), NULL, NULL ) != 0;
		EventName.UnlockBuffer();
	#endif
		return Result;
	}

public :
    bool operator == ( const CVCLObject &Value )
	{
		return Handle == Value.Handle;
	}

    bool operator != ( const CVCLObject &Value )
	{
		return Handle != Value.Handle;
	}

    bool operator == ( const VCLHANDLE Value )
	{
		return Handle == Value;
	}

    bool operator != ( const VCLHANDLE Value )
	{
		return Handle != Value;
	}
};
//---------------------------------------------------------------------------
#include "VCLObjectsCode.h"
//---------------------------------------------------------------------------
class CVCLComponent : public CVCLObject
{
public :
    CVCLComponent() {}
    CVCLComponent( CTString TypeName )
	{
		OwnsHandle = true;

    #ifdef USE_STD_STRING
        const char * __1_Param1 = TypeName.c_str();
    #else
      #ifdef _UNICODE
        int __1_Length = TypeName.GetLength();
        char * __1_Param1 = new char[ __1_Length * 2 + 1 ];
        wchar_t * __1_wch_ = TypeName.LockBuffer();
      #if _MSC_VER >= 1400
        size_t   __1_i_;
        wcstombs_s( &__1_i_, __1_Param1, __1_Length * 2, __1_wch_, __1_Length );
      #else
        wcstombs( __1_Param1, __1_wch_, __1_Length );
      #endif
      #else
        char * __1_Param1 = TypeName.LockBuffer();
      #endif
    #endif

		Handle = VCL_NewComponent( __1_Param1, NULL, false );

    #ifndef USE_STD_STRING
      #ifdef _UNICODE
        delete []__1_Param1;
      #endif
		TypeName.UnlockBuffer();
    #endif
		if( ! Handle )
	        throw CTString( "Unable to create object : " ) + TypeName;
	}

public :
	bool Open( CTString TypeName )
	{
		Close();

    #ifdef USE_STD_STRING
        const char * __1_Param1 = TypeName.c_str();

    #else
      #ifdef _UNICODE
        int __1_Length = TypeName.GetLength();
        char * __1_Param1 = new char[ __1_Length * 2 + 1 ];
        wchar_t * __1_wch_ = TypeName.LockBuffer();
      #if _MSC_VER >= 1400
        size_t   __1_i_;
        wcstombs_s( &__1_i_, __1_Param1, __1_Length * 2, __1_wch_, __1_Length );
      #else
        wcstombs( __1_Param1, __1_wch_, __1_Length );
      #endif
      #else
        char * __1_Param1 = TypeName.LockBuffer();
      #endif
    #endif

		Handle = VCL_NewComponent( __1_Param1, NULL, false );

    #ifndef USE_STD_STRING
      #ifdef _UNICODE
        delete []__1_Param1;
      #endif
		TypeName.UnlockBuffer();
    #endif

		if( ! Handle )
			return false;

		OwnsHandle = true;
		return true;
	}

	void Close()
	{
		if( ! Handle )
			return;

		if( OwnsHandle )
			VCL_Delete( Handle );

		Handle = NULL;
	}
};
//---------------------------------------------------------------------------
class CVCLControl : public CVCLObject
{
public :
	CVCLControl() {}
	CVCLControl( HWND ParentWindow, CTString TypeName )
	{
		Open( ParentWindow, TypeName );
	}

	CVCLControl( HWND ParentWindow, CTString TypeName, int Left, int Top, int Width, int Height )
	{
		Open( ParentWindow, TypeName, Left, Top, Width, Height );
	}

public :
	virtual VCLHANDLE    GetHandle() 
	{ 
	    return VCL_GetControlHandle( Handle );
	}

public :
	bool Open( HWND ParentWindow, CTString TypeName )
	{
		if( ! ParentWindow )
			return false;

		Close();

    #ifdef USE_STD_STRING
        const char * __1_Param1 = TypeName.c_str();

    #else
      #ifdef _UNICODE
        int __1_Length = TypeName.GetLength();
        char * __1_Param1 = new char[ __1_Length * 2 + 1 ];
        wchar_t * __1_wch_ = TypeName.LockBuffer();
      #if _MSC_VER >= 1400
        size_t   __1_i_;
        wcstombs_s( &__1_i_, __1_Param1, __1_Length * 2, __1_wch_, __1_Length );
      #else
        wcstombs( __1_Param1, __1_wch_, __1_Length );
      #endif
      #else
        char * __1_Param1 = TypeName.LockBuffer();
      #endif
    #endif

		Handle = VCL_NewControl( ParentWindow, __1_Param1, NULL, false );

    #ifndef USE_STD_STRING
      #ifdef _UNICODE
        delete []__1_Param1;
      #endif
		TypeName.UnlockBuffer();
    #endif
		if( ! Handle )
			return false;

		OwnsHandle = true;

		return true;
	}

	bool Open( HWND ParentWindow, CTString TypeName, int Left, int Top, int Width, int Height )
	{
		if( ! ParentWindow )
			return false;

		Close();

    #ifdef USE_STD_STRING
        const char * __1_Param1 = TypeName.c_str();

    #else
      #ifdef _UNICODE
        int __1_Length = TypeName.GetLength();
        char * __1_Param1 = new char[ __1_Length * 2 + 1 ];
        wchar_t * __1_wch_ = TypeName.LockBuffer();
      #if _MSC_VER >= 1400
        size_t   __1_i_;
        wcstombs_s( &__1_i_, __1_Param1, __1_Length * 2, __1_wch_, __1_Length );
      #else
        wcstombs( __1_Param1, __1_wch_, __1_Length );
      #endif
      #else
        char * __1_Param1 = TypeName.LockBuffer();
      #endif
    #endif

		Handle = VCL_NewControlSize( ParentWindow, __1_Param1, Left, Top, Width, Height, NULL, false );

    #ifndef USE_STD_STRING
      #ifdef _UNICODE
        delete []__1_Param1;
      #endif
		TypeName.UnlockBuffer();
    #endif

		if( ! Handle )
			return false;

		OwnsHandle = true;

		return true;
	}

	void Close()
	{
		if( ! Handle )
			return;

		if( OwnsHandle )
			VCL_Delete( Handle );

		Handle = NULL;
	}
};
//---------------------------------------------------------------------------
#pragma comment(lib, "VCLLoaderMS.lib")
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
