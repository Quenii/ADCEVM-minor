//---------------------------------------------------------------------------
#ifndef VCLSupportH
#define VCLSupportH
//---------------------------------------------------------------------------
#include <VCLObjects.h>
#include <VCLSet.h>
#include <Mmsystem.h>
//---------------------------------------------------------------------------
typedef int ( __stdcall *TLPFunctionEntry)();

//---------------------------------------------------------------------------

enum ELPHandleMode { hmNone, hmOwned };

#define __LP__CONSTRUCTORS__(A_NAME)                                        \
  A_NAME( CLPBaseComponent *a_component, const CLPString a_PropertyName ) : \
    inherited( a_component, a_PropertyName )				    \
  {									    \
  }									    \
									    \
  A_NAME( CLPClassProperty *a_property, const CLPString a_PropertyName ) :  \
    inherited( a_property, a_PropertyName )				    \
  {									    \
  }									    \
									    \
  A_NAME( _VCL_TCHAR * name ) :				\
    inherited( name )				    \
  {									    \
  }										\
									    \
  A_NAME( VCLHANDLE handle, ELPHandleMode owns_handle = hmNone ) :			\
    inherited( handle, owns_handle )				    \
  {									    \
  }										

//---------------------------------------------------------------------------
typedef DWORD FOURCC; 
//------------------------------------------------------------------------------
template < class _TYPE_ > class CLPArray
{
protected:
  _TYPE_ *m_Buffer;
  int   m_Size;

protected:
  void CopyFrom( const CLPArray &a_array )
  {
    CopyFrom( a_array.m_Buffer, a_array.m_Size ); 
  }
  
  void CopyFrom( const _TYPE_ *a_array, int a_size )
  {
    if( m_Buffer )
      delete [] m_Buffer;

    m_Size = a_size;
    if( m_Size == 0 )
      m_Buffer = NULL;

    else
      {
      m_Buffer = new _TYPE_ [ m_Size ];
      memcpy( m_Buffer, a_array, m_Size * sizeof(_TYPE_) );
      }

  }

public:
  CLPArray() :
    m_Buffer( NULL ),
    m_Size( 0 )
  {
  }

  CLPArray( const _TYPE_ *a_array, int a_size ) :
    m_Buffer( NULL )
  {
    CopyFrom( a_array, a_size );
  }

  CLPArray( const CLPArray &a_array ) :
    m_Buffer( NULL )
  {
    CopyFrom( a_array );
  }

  ~CLPArray()
  {
    if( m_Buffer )
      delete [] m_Buffer;

    m_Buffer = NULL;
  }

public:
  int GetSize() { return m_Size; }

public:
  operator _TYPE_ *() { return m_Buffer; }

public:
  _TYPE_ operator[]( int index ) { return m_Buffer[ i ]; }
  CLPArray &operator = ( const CLPArray &a_array ) { CopyFrom( a_array ); }
};
//------------------------------------------------------------------------------
class CLPString
{
protected:
  _VCL_TCHAR *m_Buffer;
  int   m_Size;

protected:
  void CopyFrom( const _VCL_TCHAR *a_string );
  void CopyFrom( const CLPString &a_string );

public:
  CLPString();
  CLPString( const _VCL_TCHAR *a_string );
  CLPString( const CLPString &a_string );
  CLPString( int a_value );

  virtual ~CLPString();

public:
  operator _VCL_TCHAR *() { return m_Buffer; }

public:
  _VCL_TCHAR *c_str() { return m_Buffer; }

public:
  CLPString &operator = ( const _VCL_TCHAR *a_string );
  CLPString operator + ( const _VCL_TCHAR *a_string );
  CLPString &operator += ( const _VCL_TCHAR *a_string );
  CLPString &operator = ( const CLPString &a_string );
  CLPString operator + ( const CLPString &a_string );
  CLPString &operator += ( const CLPString &a_string );
};
//---------------------------------------------------------------------------
class CLPBaseClass
{
public:
	virtual VCLHANDLE Get_VCL_Handle() const { return NULL; }

public:
	virtual ~CLPBaseClass() {}
};
//---------------------------------------------------------------------------
class CLPBaseComponent : public CLPBaseClass
{
protected:
  CLPBaseComponent *GetInstance()
  {
    return this;
  }

public:
  CVCLObject *Object;

protected:
  virtual VCLHANDLE Get_VCL_Handle() const = 0;
  virtual VCLHANDLE Get_VCL_FunctionHandle() const { return Get_VCL_Handle(); }

public:
  virtual TLPFunctionEntry  GetFunction( const char *function_name ) 
  {
    return NULL;
  }
};
//---------------------------------------------------------------------------
class CLPComponent : public CLPBaseComponent
{
public:
  mutable CVCLComponent Component;

protected:
  CLPComponent()
  {
    Object = &Component;
  }

  CLPComponent( const CLPComponent &other )
  {
    Object = &Component;
  }

  virtual ~CLPComponent() {}

protected:
  virtual VCLHANDLE Get_VCL_Handle() const {   return Component.GetHandle(); }
  virtual VCLHANDLE Get_VCL_FunctionHandle() const { return Get_VCL_Handle(); }

public:
  void OpenComponent( CTString component_name )
  {
    Component.Open( component_name );
  }
};
//---------------------------------------------------------------------------
typedef unsigned int CTColor;
typedef unsigned int CTGPColor;
typedef int CTCursor;
typedef double CTDate;
typedef double CTTime;
typedef unsigned char CTFontCharset;

enum CTFontPitch { fpDefault, fpVariable, fpFixed };

enum CTGPLineJoin 
{
    LineJoinMiter,
    LineJoinBevel,
    LineJoinRound,
    LineJoinMiterClipped
};

enum CTMouseButton { mbLeft, mbRight, mbMiddle };

struct CTGPBlend
{
    float Position;
    float Value;
};

struct CTGPInterpolationColor
{
    float		Position;
    CTGPColor	Color;
};

struct CTGPPointF
{
    float X;
    float Y;
};

enum CTFontStyle { fsBold, fsItalic, fsUnderline, fsStrikeOut };
typedef CTSet<CTFontStyle, fsBold, fsStrikeOut> CTFontStyles;

enum CTShiftStateItems { ssShift, ssAlt, ssCtrl, ssLeft, ssRight, ssMiddle, ssDouble };
typedef CTSet<CTShiftStateItems, ssShift, ssDouble> CTShiftState;

enum CTPixelFormat { pfDevice, pf1bit, pf4bit, pf8bit, pf15bit, pf16bit, pf24bit, pf32bit, pfCustom };
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class T > class CLPIndexProperty_1_Item;
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class T > class CLPIndexProperty_1 : public CLPBaseClass
{
  friend class CLPIndexProperty_1_Item<TObject, TIndex1, T>;

protected:
  mutable TObject *m_Object;
  T (TObject::*m_Getter)( TIndex1 index1 );
  void (TObject::*m_Setter)( TIndex1 index1, T value );

public:
  CLPIndexProperty_1( TObject *object, T (TObject::*getter)( TIndex1 index1 ), void (TObject::*setter)( TIndex1 index1, T value )) :
		m_Object( object ),
		m_Getter( getter ),
		m_Setter( setter )
	{
	}

public:
  CLPIndexProperty_1_Item<TObject,TIndex1,T> operator[]( TIndex1 index1 );

};
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class T > class CLPIndexProperty_1_Item
{
protected:
  TIndex1 m_Index1;
  CLPIndexProperty_1<TObject, TIndex1, T> *m_Owner;

public:
  CLPIndexProperty_1_Item( CLPIndexProperty_1<TObject, TIndex1, T> *owner, TIndex1 index1 ) :
	  m_Owner( owner ),
	  m_Index1( index1 )
  {
  }

public:
  operator T() const
  {
      return ( m_Owner->m_Object->*( m_Owner->m_Getter ) )( m_Index1 );
  }

  CLPIndexProperty_1_Item &operator = ( const T &value )
  {
	(( m_Owner->m_Object )->* ( m_Owner->m_Setter ))( m_Index1, value );
	return *this;
  }

  CLPIndexProperty_1_Item &operator = ( const CLPIndexProperty_1_Item &value )
  {
	m_Owner = value.m_Owner;
    m_Index1 = value.m_Index1;
	return *this;
  }
};
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class T > class CLPReadIndexProperty_1 : public CLPBaseClass
{
protected:
  mutable TObject *m_Object;
  T (TObject::*m_Getter)( TIndex1 index1 );

public:
  CLPReadIndexProperty_1( TObject *object, T (TObject::*getter)( TIndex1 index1 )) :
		m_Object( object ),
		m_Getter( getter )
	{
	}

public:
  T operator[]( TIndex1 index1 )
  {
	 return ( m_Object->*( m_Getter ) )( index1 );
  }

};
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > class CLPReadIndexProperty_2_Item;
template< class TObject, class TIndex1, class TIndex2, class T > class CLPReadIndexProperty_2_ArrayItem;
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > class CLPReadIndexProperty_2 : public CLPBaseClass
{
	friend class CLPReadIndexProperty_2_Item<TObject, TIndex1, TIndex2, T>;

protected:
  mutable TObject *m_Object;
  T (TObject::*m_Getter)( TIndex1 index1, TIndex2 index2 );

public:
  CLPReadIndexProperty_2( TObject *object, T (TObject::*getter)( TIndex1 index1, TIndex2 index2 )) :
		m_Object( object ),
		m_Getter( getter )
	{
	}

public:
  CLPReadIndexProperty_2_ArrayItem<TObject,TIndex1,TIndex2,T> operator[]( TIndex1 index1 );

};
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > class CLPReadIndexProperty_2_Item
{
protected:
  TIndex1 m_Index1;
  TIndex2 m_Index2;
  CLPReadIndexProperty_2<TObject, TIndex1, TIndex2, T> *m_Owner;

public:
  CLPReadIndexProperty_2_Item( CLPReadIndexProperty_2<TObject, TIndex1, TIndex2, T> *owner, TIndex1 index1, TIndex1 index2 ) :
	  m_Owner( owner ),
	  m_Index1( index1 ),
	  m_Index2( index2 )
  {
  }

public:
  operator T() const
  {
      return ( m_Owner->m_Object->*( m_Owner->m_Getter ) )( m_Index1, m_Index2 );
  }

  CLPReadIndexProperty_2_Item &operator = ( const CLPReadIndexProperty_2_Item &value )
  {
	m_Owner = value.m_Owner;
    m_Index1 = value.m_Index1;
	return *this;
  }
};
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > class CLPReadIndexProperty_2_ArrayItem
{
protected:
  TIndex1 m_Index1;
  CLPReadIndexProperty_2<TObject, TIndex1, TIndex2, T> *m_Owner;

public:
  CLPReadIndexProperty_2_ArrayItem( CLPReadIndexProperty_2<TObject, TIndex1, TIndex2, T> *owner, TIndex1 index1 ) :
	  m_Owner( owner ),
	  m_Index1( index1 )
  {
  }

public:
  CLPReadIndexProperty_2_Item<TObject, TIndex1, TIndex2, T> operator[]( TIndex2 index2 )
    {
	  return CLPReadIndexProperty_2_Item<TObject, TIndex1, TIndex2, T>( m_Owner, m_Index1, index2 );
    }

};
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > class CLPIndexProperty_2_Item;
template< class TObject, class TIndex1, class TIndex2, class T > class CLPIndexProperty_2_ArrayItem;
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > class CLPIndexProperty_2 : public CLPBaseClass
{
	friend class CLPIndexProperty_2_Item<TObject, TIndex1, TIndex2, T>;

protected:
  mutable TObject *m_Object;
  T (TObject::*m_Getter)( TIndex1 index1, TIndex2 index2 );
  void (TObject::*m_Setter)( TIndex1 index1, TIndex2 index2, T value );

public:
  CLPIndexProperty_2( TObject *object, T (TObject::*getter)( TIndex1 index1, TIndex2 index2 ), void (TObject::*setter)( TIndex1 index1, TIndex2 index2, T value )) :
		m_Object( object ),
		m_Getter( getter ),
		m_Setter( setter )
	{
	}

public:
  CLPIndexProperty_2_ArrayItem<TObject,TIndex1,TIndex2,T> operator[]( TIndex1 index1 );

};
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > class CLPIndexProperty_2_Item
{
protected:
  TIndex1 m_Index1;
  TIndex2 m_Index2;
  CLPIndexProperty_2<TObject, TIndex1, TIndex2, T> *m_Owner;

public:
  CLPIndexProperty_2_Item( CLPIndexProperty_2<TObject, TIndex1, TIndex2, T> *owner, TIndex1 index1, TIndex1 index2 ) :
	  m_Owner( owner ),
	  m_Index1( index1 ),
	  m_Index2( index2 )
  {
  }

public:
  operator T() const
  {
      return ( m_Owner->m_Object->*( m_Owner->m_Getter ) )( m_Index1, m_Index2 );
  }

  CLPIndexProperty_2_Item &operator = ( const T &value )
  {
	( ( m_Owner->m_Object )->*( m_Owner->m_Setter ))( m_Index1, m_Index2, value );
	return *this;
  }

  CLPIndexProperty_2_Item &operator = ( const CLPIndexProperty_2_Item &value )
  {
	m_Owner = value.m_Owner;
    m_Index1 = value.m_Index1;
	return *this;
  }
};
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > class CLPIndexProperty_2_ArrayItem
{
protected:
  TIndex1 m_Index1;
  CLPIndexProperty_2<TObject, TIndex1, TIndex2, T> *m_Owner;

public:
  CLPIndexProperty_2_ArrayItem( CLPIndexProperty_2<TObject, TIndex1, TIndex2, T> *owner, TIndex1 index1 ) :
	  m_Owner( owner ),
	  m_Index1( index1 )
  {
  }

public:
  CLPIndexProperty_2_Item<TObject, TIndex1, TIndex2, T> operator[]( TIndex2 index2 )
    {
	  return CLPIndexProperty_2_Item<TObject, TIndex1, TIndex2, T>( m_Owner, m_Index1, index2 );
    }

};
//---------------------------------------------------------------------------
template< class TObject, class T > class CLPAccessProperty : public CLPBaseClass
{
protected:
  mutable TObject *m_Object;
  T (TObject::*m_Getter)();
  void (TObject::*m_Setter)( T value );

public:
  CLPAccessProperty( TObject *object, T (TObject::*getter)(), void (TObject::*setter)( T value )) :
		m_Object( object ),
		m_Getter( getter ),
		m_Setter( setter )
	{
	}

public:
  operator T()
    {
    return ( m_Object->*m_Getter )();
    }

  CLPAccessProperty &operator = ( const T &data )
    {
	( m_Object->*m_Setter )( data );
    return *this;
    }
};
//------------------------------------------------------------------------------
template< class TObject, class T > class CLPReadAccessProperty : public CLPBaseClass
{
protected:
  TObject *m_Object;
  T (TObject::*m_Getter)();

public:
  CLPReadAccessProperty( TObject *object, T (TObject::*getter)()) :
		m_Object( object ),
		m_Getter( getter )
	{
	}

public:
  operator T()
    {
    return ( m_Object->*m_Getter )();
    }

};
//------------------------------------------------------------------------------
template< class TObject, class T > class CLPWriteAccessProperty : public CLPBaseClass
{
protected:
  TObject *m_Object;
  void (TObject::*m_Setter)( T value );

public:
  CLPWriteAccessProperty( TObject *object, void (TObject::*setter)( T value )) :
		m_Object( object ),
		m_Setter( setter )
	{
	}

public:
  CLPWriteAccessProperty &operator = ( const T &data )
    {
	( m_Object->*m_Setter )( data );
    return *this;
    }
};
//------------------------------------------------------------------------------
class CLPBaseProperty : public CLPBaseClass
{
protected:
  mutable CVCLObject *m_Object;

public:
  mutable CLPString			m_PropertyName;
  mutable CLPBaseClass	   *m_Parent;
  mutable CLPBaseComponent *m_control;

public:
	VCLHANDLE GetInternalHandle() const { return Get_VCL_Handle(); }

protected:
  virtual VCLHANDLE Get_VCL_Handle() const
  {
	if( m_Object )
		return m_Object->GetHandle();

	else
	{
/*
		VCLHANDLE Result = NULL;
		if( m_Parent )
			if( m_Parent->Get_VCL_Handle())
			{
				::VCL_GetObjectProperty( m_Parent->Get_VCL_Handle(), (_VCL_TCHAR *)m_Name, &Result );
			}
*/
		int Value = m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ];
		return *((VCLHANDLE*)&Value );
	}
  }

  virtual VCLHANDLE Get_VCL_FunctionHandle() const { return Get_VCL_Handle(); }
  virtual TLPFunctionEntry  GetFunction( const char *function_name ) { return m_control->GetFunction( function_name ); }

protected:
  CLPBaseProperty( char * name ) :
	m_Object( new CVCLObject( CTString( name ), false )),
    m_control( NULL ),
    m_Parent( NULL )
  {
  }

  CLPBaseProperty( const CLPBaseProperty &other ) : 
	m_Object( NULL ),
    m_control( other.m_control ), 
    m_PropertyName( other.m_PropertyName ),
    m_Parent( other.m_Parent )
  {
	if( other.m_Object )
      m_Object = new CVCLObject( other.m_Object->GetHandle() );
  }

  CLPBaseProperty( CLPBaseProperty *a_property, const CLPString a_PropertyName ) :
	m_Object( NULL ),
    m_control( a_property->m_control ),
    m_Parent( a_property )
//    m_PropertyName( a_PropertyName )
  {
    m_PropertyName = a_property->m_PropertyName;
    m_PropertyName += _T( "." );
    m_PropertyName += a_PropertyName;
  }

  CLPBaseProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
	m_Object( NULL ),
    m_control( a_control ),
    m_PropertyName( a_PropertyName ),
    m_Parent( a_control )
  {
  }

  CLPBaseProperty( VCLHANDLE handle, ELPHandleMode owns_handle = hmNone ) :
	m_Object( new CVCLObject( handle, ( owns_handle == hmOwned ))),
    m_control( NULL ),
    m_Parent( NULL ),
    m_PropertyName( _VCL_TCHAR( "" ) )
  {
  }

  virtual ~CLPBaseProperty() 
  {
	  if( m_Object )
		  delete m_Object;
  }

  CLPBaseProperty *GetInstance()
  {
    return this;
  }
};
//---------------------------------------------------------------------------
class CLPClassProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

protected:
  CLPClassProperty *GetInstance()
  {
    return this;
  }

protected:
  VCLHANDLE VCL_CreateCall( VCLHANDLE Library, char *FunctionName, char *InstantiatorName )
  {
  static void *__0_FuncPtr_ = NULL;
  if( __0_FuncPtr_ == NULL )
    __0_FuncPtr_ = (void *)( VCL_GetFunction( Library, FunctionName ));

  static void *__0_InstPtr_ = NULL;
  if( __0_InstPtr_ == NULL )
    __0_InstPtr_ = (void *)( VCL_GetFunction( Library, InstantiatorName ));

  VCLHANDLE __0_RtnValue_ = (VCLHANDLE)0;

  if( __0_FuncPtr_ && __0_InstPtr_ )
    {
    _asm
      {
      push eax
	  push edx

      mov       dl,1
      mov  eax,dword ptr [ __0_FuncPtr_ ]

      call dword ptr [ __0_InstPtr_ ]

      mov  __0_RtnValue_,eax

	  pop  edx
      pop  eax
      }
    }

  return (VCLHANDLE)__0_RtnValue_;
  }

protected:
  CLPClassProperty( const CLPClassProperty &other ) : inherited( other ) {}
  __LP__CONSTRUCTORS__( CLPClassProperty );

  ~CLPClassProperty()
  {
  }


public:
	CLPClassProperty &operator = ( const CLPClassProperty &other )
	{
		m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ] = other.GetInternalHandle();

		return *this;
	}

/*
	void Assign( const CLPClassProperty &other )
	{
		m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ] = other.GetInternalHandle();
	}
*/

};
//---------------------------------------------------------------------------
typedef CLPClassProperty CLPComponentCollectionBase;
/*
class CLPComponentCollectionBase : public CLPClassProperty
{
protected:
  CLPComponentCollectionBase( const CLPComponentCollectionBase &other ) : inherited( other ) {}
  __LP__CONSTRUCTORS__( CLPComponentCollectionBase );

};
*/
//---------------------------------------------------------------------------
class CLPBaseEventProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  bool Get( void *&CallBackFunction, void *&UserData )
  {
    return m_control->Object->GetEvent( m_PropertyName.c_str(), CallBackFunction, UserData );
  }

  bool Clear()
  {
    return m_control->Object->ClearEvent( m_PropertyName.c_str() );
  }

protected:
  __LP__CONSTRUCTORS__( CLPBaseEventProperty );

};
//---------------------------------------------------------------------------
template< int FUNC_INDEX, class TR > class CLPEventProperty_0 : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

public:
  template< class T > bool Set( T *Instance, TR (__stdcall T::*CallBackFunction)() )
  {
    return m_control->Object->SetEvent( (_VCL_TCHAR *)m_PropertyName, CallBackFunction, Instance, FUNC_INDEX );
  }

public:
  __LP__CONSTRUCTORS__( CLPEventProperty_0 );

};
//---------------------------------------------------------------------------
template< int FUNC_INDEX, class TR, class T1 > class CLPEventProperty_1 : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

public:
  template< class T > bool Set( T *Instance, TR (__stdcall T::*CallBackFunction)( T1 ) )
  {
    return m_control->Object->SetEvent( (_VCL_TCHAR *)m_PropertyName, CallBackFunction, Instance, FUNC_INDEX );
  }
    
public:
  __LP__CONSTRUCTORS__( CLPEventProperty_1 );

};
//---------------------------------------------------------------------------
template< int FUNC_INDEX, class TR, class T1, class T2 > class CLPEventProperty_2 : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

public:
  template< class T > bool Set( T *Instance, TR (__stdcall T::*CallBackFunction)( T1, T2 ) )
  {
    return m_control->Object->SetEvent( (_VCL_TCHAR *)m_PropertyName, CallBackFunction, Instance, FUNC_INDEX );
  }

public:
  __LP__CONSTRUCTORS__( CLPEventProperty_2 );

};
//---------------------------------------------------------------------------
template< int FUNC_INDEX, class TR, class T1, class T2, class T3 > class CLPEventProperty_3 : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

public:
  template< class T > bool Set( T *Instance, TR (__stdcall T::*CallBackFunction)( T1, T2, T3 ) )
  {
    return m_control->Object->SetEvent( (_VCL_TCHAR *)m_PropertyName, CallBackFunction, Instance, FUNC_INDEX );
  }

public:
  __LP__CONSTRUCTORS__( CLPEventProperty_3 );

};
//---------------------------------------------------------------------------
template< int FUNC_INDEX, class TR, class T1, class T2, class T3, class T4 > class CLPEventProperty_4 : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

public:
  template< class T > bool Set( T *Instance, TR (__stdcall T::*CallBackFunction)( T1, T2, T3, T4 ) )
  {
    return m_control->Object->SetEvent( (_VCL_TCHAR *)m_PropertyName, CallBackFunction, Instance, FUNC_INDEX );
  }

public:
  __LP__CONSTRUCTORS__( CLPEventProperty_4 );

};
//---------------------------------------------------------------------------
template< int FUNC_INDEX, class TR, class T1, class T2, class T3, class T4, class T5 > class CLPEventProperty_5 : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

public:
  template< class T > bool Set( T *Instance, TR (__stdcall T::*CallBackFunction)( T1, T2, T3, T4, T5 ) )
  {
    return m_control->Object->SetEvent( (_VCL_TCHAR *)m_PropertyName, CallBackFunction, Instance, FUNC_INDEX );
  }

public:
  __LP__CONSTRUCTORS__( CLPEventProperty_5 );

};
//---------------------------------------------------------------------------
template< int FUNC_INDEX, class TR, class T1, class T2, class T3, class T4, class T5, class T6 > class CLPEventProperty_6 : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

public:
  template< class T > bool Set( T *Instance, TR (__stdcall T::*CallBackFunction)( T1, T2, T3, T4, T5, T6 ) )
  {
    return m_control->Object->SetEvent( (_VCL_TCHAR *)m_PropertyName, CallBackFunction, Instance, FUNC_INDEX );
  }

public:
  __LP__CONSTRUCTORS__( CLPEventProperty_6 );

};
//---------------------------------------------------------------------------
template<class T> class CLPProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  operator T()
    {
    return m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ];
    }

  CLPProperty &operator = ( const T &data )
    {
    m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ] = (const T)data;
    return *this;
    }
};
//---------------------------------------------------------------------------
template<class T> class CLPComponentProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPComponentProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPComponentProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  operator T()
    {
    return m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ];
    }

  CLPComponentProperty &operator = ( const T &data )
    {
    m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ] = *(CVCLObject*)&data;
    return *this;
    }
};
//---------------------------------------------------------------------------
class CLPControl : public CLPBaseComponent
{
public:
  mutable CVCLControl  Control;

public:    // Properties
  CLPProperty<CTColor> Color;
  CLPProperty<int>     Left;
  CLPProperty<int>     Top;
  CLPProperty<int>     Width;
  CLPProperty<int>     Height;

protected:
  virtual VCLHANDLE Get_VCL_Handle() const {   return Control.GetHandle(); }
  virtual VCLHANDLE Get_VCL_FunctionHandle() const { return Get_VCL_Handle(); }

protected:
  CLPControl() :
    Color( GetInstance(), _T( "Color" ) ),
	Left( GetInstance(), _T( "Left" ) ),
	Top( GetInstance(), _T( "Top" ) ),
	Width( GetInstance(), _T( "Width" ) ),
	Height( GetInstance(), _T( "Height" ) )
  {
    Object = &Control;
  }

  virtual ~CLPControl() {}

public:
  virtual void Invalidate();

public:
  void OpenControl( CTString component_name, HWND hParent )
  {
    Control.Open( hParent, component_name );
  }
};
//---------------------------------------------------------------------------
template<class T> class CLPEnumProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPEnumProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPEnumProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  operator T()
    {
	int tmp = m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ];
    return (T)tmp;
    }

  CLPBaseProperty &operator = ( T data )
    {
    m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ] = (int)data;
    return *this;
    }
};
//---------------------------------------------------------------------------
class CLPBaseCollectionProperty : public CLPClassProperty
{
  typedef CLPClassProperty inherited;

public:
  CLPProperty<int> Count;

//protected:
//	VCLHANDLE AddItem();

public:
  void Add();
  void Add( int num_items );
  void Insert( int index );
  void Delete( int index );
  void Clear();

protected:
//  void SetCount( int value );
//  int GetCount();

protected:
  CLPBaseCollectionProperty( CLPBaseComponent *a_component, const CLPString a_PropertyName ) : 
    inherited( a_component, a_PropertyName ),
    Count( GetInstance(), _T( "Count" ) )
  {
  }
									    
  CLPBaseCollectionProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :  
    inherited( a_property, a_PropertyName ),
    Count( GetInstance(), _T( "Count" ) )
  {
  }
									    
  CLPBaseCollectionProperty( VCLHANDLE handle, ELPHandleMode owns_handle = hmNone ) :
    inherited( handle, owns_handle ),
    Count( GetInstance(), _T( "Count" ) )
  {
  }

  CLPClassProperty *GetInstance()
  {
    return this;
  }
};
//---------------------------------------------------------------------------
class CTStrings : public CLPClassProperty
{
  typedef CLPClassProperty inherited;

protected:
  CTStrings *GetInstance()
  {
    return this;
  }

protected:
  int GetCount();

  CTString Get( int index );
  void    Put( int index, CTString value );

public:
  CLPReadAccessProperty<CTStrings, int> Count;
  CLPIndexProperty_1<CTStrings, int, CTString> Strings;

public:
  int  Add( CTString str );
  void Clear();
  void Delete( int index );

public:
  CTStrings();
  CTStrings( VCLHANDLE handle ) :
    inherited( handle ),
	Count( GetInstance(), &CTStrings::GetCount ),
	Strings( GetInstance(), &CTStrings::Get, &CTStrings::Put )
  {
  }

};
//---------------------------------------------------------------------------
template<class T> class CLPCollectionProperty : public CLPBaseCollectionProperty
{
  typedef CLPBaseCollectionProperty inherited;

protected:
  CLPCollectionProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPCollectionProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }

  CLPCollectionProperty( VCLHANDLE handle, ELPHandleMode owns_handle = hmNone ) :
    inherited( handle, owns_handle )
  {
  }

public:
/*
  T Add() 
  {  
	return inherited::AddItem();
  }

  void Add( int couns ) 
  {
	inherited::Add( couns );
  }
*/

public:
  T operator[]( int index ) 
  {
    CLPString Num = index;
    T Item( this, Num );
    T Item1( Item );
    return Item1;
  }

};
//---------------------------------------------------------------------------
template<class T> class CLPReadProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPReadProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPReadProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  operator T()
  {
    return m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ];
  }

};
//---------------------------------------------------------------------------
template<class T> class CLPComponentReadProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPComponentReadProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPComponentReadProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  operator T()
  {
    return m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ];
  }

};
//---------------------------------------------------------------------------
template<class T> class CLPEnumReadProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPEnumReadProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPEnumReadProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  operator T()
  {
	int tmp = m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ];
    return (T)tmp;
  }

};
//---------------------------------------------------------------------------
template<class T> class CLPWriteProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPWriteProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPWriteProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  CLPWriteProperty &operator = ( const T &data )
    {
    m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ] = (const T)data;
    return *this;
    }
};
//---------------------------------------------------------------------------
template<class T> class CLPComponentWriteProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPComponentWriteProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPComponentWriteProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  CLPWriteProperty &operator = ( const T &data )
    {
    m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ] = *(CVCLObject*)&data;
    return *this;
    }
};
//---------------------------------------------------------------------------
template<class T> class CLPEnumWriteProperty : public CLPBaseProperty
{
  typedef CLPBaseProperty inherited;

public:
  CLPEnumWriteProperty( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName )
  {
  }

  CLPEnumWriteProperty( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName )
  {
  }


public:
  CLPEnumWriteProperty &operator = ( const T &data )
    {
    m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ] = (const T)data;
    return *this;
    }
};
//---------------------------------------------------------------------------
class CTOWPinProperty
{
  friend class CTOWPinListBasicProperty;

protected:
  CLPBaseComponent *m_control;
  CLPString   m_PinName;
  
public:
  bool Connect( CTOWPinProperty &other )
  {
    return m_control->Object->ConnectPin( (_VCL_TCHAR *)m_PinName, *other.m_control->Object, (_VCL_TCHAR *)other.m_PinName );
  }

  bool ConnectAfter( CTOWPinProperty &other, CTOWPinProperty &after_pin )
  {
    return m_control->Object->ConnectAfterPin( (_VCL_TCHAR *)m_PinName, *other.m_control->Object, (_VCL_TCHAR *)other.m_PinName, *after_pin.m_control->Object, (_VCL_TCHAR *)after_pin.m_PinName );
  }

  void Disconnect()
  {
    m_control->Object->DisconnectPin( (_VCL_TCHAR *)m_PinName );
  }
/* Obsolete
  void Pulse()
  {
    m_control->Object->PulsePin( (char *)m_PinName );
  }
*/
public:
  CTOWPinProperty( CLPBaseComponent *a_control, const CLPString a_PinName ) :
    m_control( a_control ),
    m_PinName( a_PinName )
  {
  }

  CTOWPinProperty( CLPClassProperty *a_property, const CLPString a_PinName ) :
    m_control( a_property->m_control )
  {
    m_PinName = a_property->m_PropertyName;
    m_PinName += _T( "." );
    m_PinName += a_PinName;
  }

  virtual ~CTOWPinProperty() {}
};
//---------------------------------------------------------------------------
class CTOWPinListBasicProperty
{
  friend class CTOWPinListCountProperty;
  friend class CTOWPinListReadOnlyCountProperty;

protected:
  CLPBaseComponent *m_control;
  CLPString   m_PinListName;

protected:
  CTOWPinListBasicProperty *GetInstance() { return this; }

public:
  CTOWPinProperty operator[] ( int a_Index )
  {
    return CTOWPinProperty( m_control, m_PinListName + _T( "." ) + CLPString( a_Index ));
  }

protected:
  CTOWPinListBasicProperty( CLPBaseComponent *a_control, const CLPString a_PinListName ) :
    m_control( a_control ),
    m_PinListName( a_PinListName )
  {
  }

  CTOWPinListBasicProperty( CLPClassProperty *a_property, const CLPString a_PinListName ) :
    m_control( a_property->m_control )
  {
    m_PinListName = a_property->m_PropertyName;
    m_PinListName += _T( "." );
    m_PinListName += a_PinListName;
  }

  virtual ~CTOWPinListBasicProperty() {}
};
//---------------------------------------------------------------------------
class CTOWPinListReadOnlyCountProperty
{
protected:
  CTOWPinListBasicProperty *m_PinList;

public:
  CTOWPinListReadOnlyCountProperty( CTOWPinListBasicProperty *a_pin_list ) :
    m_PinList( a_pin_list )
  {
  }

public:
  operator int ()
  {
    return m_PinList->m_control->Object->Properties[ (_VCL_TCHAR *)( m_PinList->m_PinListName + _T( ".Count" )) ];
  }
};
//---------------------------------------------------------------------------
class CTOWPinListCountProperty : public CTOWPinListReadOnlyCountProperty
{
  typedef CTOWPinListReadOnlyCountProperty inherited;

public:
  CTOWPinListCountProperty( CTOWPinListBasicProperty *a_pin_list ) :
    inherited( a_pin_list )
  {
  }

public:
  CTOWPinListCountProperty &operator = ( const int &data )
  {
    m_PinList->m_control->Object->Properties[ (_VCL_TCHAR *)( m_PinList->m_PinListName + _T( ".Count" ) ) ] = (const int)data;
    return *this;
  }

};
//---------------------------------------------------------------------------
class CTOWPinListProperty : public CTOWPinListBasicProperty
{
  typedef CTOWPinListBasicProperty inherited;

public:
  CTOWPinListReadOnlyCountProperty Count;
  
public:
  CTOWPinListProperty( CLPBaseComponent *a_control, const CLPString a_PinListName ) :
    inherited( a_control, a_PinListName ),
	Count( GetInstance() )
  {
  }

  CTOWPinListProperty( CLPClassProperty *a_property, const CLPString a_PinListName ) :
    inherited( a_property, a_PinListName ),
	Count( GetInstance() )
  {
  }

};
//---------------------------------------------------------------------------
class CTOWPinListOwnerProperty : public CTOWPinListBasicProperty
{
  typedef CTOWPinListBasicProperty inherited;

public:
  CTOWPinListCountProperty Count;
  
public:
  CTOWPinListOwnerProperty( CLPBaseComponent *a_control, const CLPString a_PinListName ) :
    inherited( a_control, a_PinListName ),
	Count( GetInstance() )
  {
  }

  CTOWPinListOwnerProperty( CLPClassProperty *a_property, const CLPString a_PinListName ) :
    inherited( a_property, a_PinListName ),
	Count( GetInstance() )
  {
  }

};
//---------------------------------------------------------------------------
class CTOWInputPinProperty : public CTOWPinProperty
{
  typedef CTOWPinProperty inherited;

public:
  CTOWInputPinProperty( CLPBaseComponent *a_control, const CLPString a_PinName ) :
    inherited( a_control, a_PinName )
  {
  }

  CTOWInputPinProperty( CLPClassProperty *a_property, const CLPString a_PinName ) :
    inherited( a_property, a_PinName )
  {
  }      
};
//---------------------------------------------------------------------------
class CTOWOutputPinProperty : public CTOWPinProperty
{
  typedef CTOWPinProperty inherited;

public:
  CTOWOutputPinProperty( CLPBaseComponent *a_control, const CLPString a_PinName ) :
    inherited( a_control, a_PinName )
  {
  }

  CTOWOutputPinProperty( CLPClassProperty *a_property, const CLPString a_PinName ) :
    inherited( a_property, a_PinName )
  {
  }
};
//---------------------------------------------------------------------------
class CTOWStatePinProperty : public CTOWPinProperty
{
  typedef CTOWPinProperty inherited;

public:
  CTOWStatePinProperty( CLPBaseComponent *a_control, const CLPString a_PinName ) :
    inherited( a_control, a_PinName )
  {
  }

  CTOWStatePinProperty( CLPClassProperty *a_property, const CLPString a_PinName ) :
    inherited( a_property, a_PinName )
  {
  }
};
//---------------------------------------------------------------------------
typedef CLPClassProperty CTLPLockedPersistent;
//---------------------------------------------------------------------------
class CTFont : public CLPClassProperty
{
  typedef CLPClassProperty inherited;

public:    // Properties
  CLPProperty<int>              Height;
  CLPProperty<int>              Size;
  CLPProperty<CTColor>          Color;
  CLPProperty<CTString>          Name;
  CLPProperty<CTFontCharset>    Charset;
  CLPProperty<CTFontPitch>      Pitch;
  CLPProperty<CTFontStyles>     Style;

public:
  CTFont( const CTFont &other ) : 
    inherited( other ),
    Height( GetInstance(), _T( "Height" ) ),
    Size( GetInstance(), _T( "Size" ) ),
    Color( GetInstance(), _T( "Color" ) ),
    Name( GetInstance(), _T( "Name" ) ),
    Charset( GetInstance(), _T( "Charset" ) ),
    Pitch( GetInstance(), _T( "Pitch" ) ),
    Style( GetInstance(), _T( "Style" ) )
  {
  }

  CTFont( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName ),
    Height( GetInstance(), _T( "Height" ) ),
    Size( GetInstance(), _T( "Size" ) ),
    Color( GetInstance(), _T( "Color" ) ),
    Name( GetInstance(), _T( "Name" ) ),
    Charset( GetInstance(), _T( "Charset" ) ),
    Pitch( GetInstance(), _T( "Pitch" ) ),
    Style( GetInstance(), _T( "Style" ) )
  {
  }

  CTFont( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName ),
    Height( GetInstance(), _T( "Height" ) ),
    Size( GetInstance(), _T( "Size" ) ),
    Color( GetInstance(), _T( "Color" ) ),
    Name( GetInstance(), _T( "Name" ) ),
    Charset( GetInstance(), _T( "Charset" ) ),
    Pitch( GetInstance(), _T( "Pitch" ) ),
    Style( GetInstance(), _T( "Style" ) )
  {
  }
};
//---------------------------------------------------------------------------
enum CTPenMode { pmBlack, pmWhite, pmNop, pmNot, pmCopy, pmNotCopy, pmMergePenNot, pmMaskPenNot, pmMergeNotPen, pmMaskNotPen, pmMerge, pmNotMerge, pmMask, pmNotMask, pmXor, pmNotXor };
enum CTPenStyle {psSolid, psDash, psDot, psDashDot, psDashDotDot, psClear, psInsideFrame};
//---------------------------------------------------------------------------
class CTPen : public CLPClassProperty
{
  typedef CLPClassProperty inherited;

public:    // Properties
  CLPProperty<int>              Width;
  CLPProperty<CTColor>          Color;
  CLPProperty<CTPenMode>		Mode;
  CLPProperty<CTPenStyle>		Style;

public:
  CTPen( const CTPen &other ) : 
    inherited( other ),
    Width( GetInstance(), _T( "Width" ) ),
    Color( GetInstance(), _T( "Color" ) ),
	Style( GetInstance(), _T( "Style" ) ),
    Mode( GetInstance(), _T( "Mode" ) )
  {
  }

  CTPen( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName ),
    Width( GetInstance(), _T( "Width" ) ),
    Color( GetInstance(), _T( "Color" ) ),
	Style( GetInstance(), _T( "Style" ) ),
    Mode( GetInstance(), _T( "Mode" ) )
  {
  }

  CTPen( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName ),
    Width( GetInstance(), _T( "Width" ) ),
    Color( GetInstance(), _T( "Color" ) ),
	Style( GetInstance(), _T( "Style" ) ),
    Mode( GetInstance(), _T( "Mode" ) )
  {
  }
};
//---------------------------------------------------------------------------
enum CTBrushStyle {bsSolid, bsClear, bsHorizontal, bsVertical, bsFDiagonal, bsBDiagonal, bsCross, bsDiagCross};
//---------------------------------------------------------------------------
class CTBrush : public CLPClassProperty
{
  typedef CLPClassProperty inherited;

public:    // Properties
  CLPProperty<CTColor>          Color;
  CLPProperty<CTBrushStyle>		Style;

public:
  CTBrush( const CTBrush &other ) : 
    inherited( other ),
    Color( GetInstance(), _T( "Color" ) ),
	Style( GetInstance(), _T( "Style" ) )
  {
  }

  CTBrush( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName ),
    Color( GetInstance(), _T( "Color" ) ),
	Style( GetInstance(), _T( "Style" ) )
  {
  }

  CTBrush( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName ),
    Color( GetInstance(), _T( "Color" ) ),
	Style( GetInstance(), _T( "Style" ) )
  {
  }
};
//---------------------------------------------------------------------------
class CTPicture : public CLPClassProperty
{
  typedef CLPClassProperty inherited;

protected:
  void *m_Handle;

public:
  VCLHANDLE GetHandle() const
  { 
	  if( m_Handle )
	      return m_Handle; 

	  else
		  return inherited::Get_VCL_Handle();
  }

public:
  CTPicture &operator = ( const CTPicture &data );

  operator VCLHANDLE() 
  { 
	  if( m_Handle )
	      return m_Handle; 

	  else
		  return inherited::Get_VCL_Handle();
  }

public:
  CTPicture();
  CTPicture( const CTPicture &picture );
  CTPicture( CLPBaseComponent *a_control, const CLPString a_PropertyName );
  CTPicture( CLPClassProperty *a_property, const CLPString a_PropertyName );
  CTPicture( HBITMAP bitmap );
  virtual ~CTPicture();

};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef _WAVEFORMATEXTENSIBLE_
#define _WAVEFORMATEXTENSIBLE_
typedef struct {
    WAVEFORMATEX    Format;
    union {
        WORD wValidBitsPerSample;       /* bits of precision  */
        WORD wSamplesPerBlock;          /* valid if wBitsPerSample==0 */
        WORD wReserved;                 /* If neither applies, set to zero. */
    } Samples;
    DWORD           dwChannelMask;      /* which channels are */
                                        /* present in stream  */
    GUID            SubFormat;
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;
#endif // !_WAVEFORMATEXTENSIBLE_
//---------------------------------------------------------------------------
typedef WAVEFORMATEXTENSIBLE CTWaveFormatExtensible;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
inline void *Get_rtl60()
{
  static void *_LibraryHandle = NULL;
  if( ! _LibraryHandle )
    _LibraryHandle = VCL_LoadLibrary( "rtl60.bpl" );

  return _LibraryHandle;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
inline CTStrings::CTStrings() :
  inherited( "TStringList" ),
  Count( GetInstance(), &CTStrings::GetCount ),
  Strings( GetInstance(), &CTStrings::Get, &CTStrings::Put )
{
}
//---------------------------------------------------------------------------
inline int CTStrings::Add( CTString str )
{
  static void *Func = NULL;
  if( ! Func )
	{
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TStringList@Add$qqrx17System@AnsiString" );
	}

  void *ThisPtr = Get_VCL_Handle();

  int __0_RtnValue_ = 0;

  if( Func )
    {
  #ifdef USE_STD_STRING
    const char * __1_Param1 = str.c_str();

  #else
    _VCL_TCHAR *__1_Param1 = str.LockBuffer();
  #endif
    void *StringPtr = VCL_CreateAnsiString( __1_Param1 );
  #ifndef USE_STD_STRING
    str.UnlockBuffer();
  #endif

    void *DataPtr = *(void **)StringPtr;

    _asm
      {
      push eax
      push edx
      mov  edx,DataPtr
	  mov  eax,dword ptr [ThisPtr]
      call dword ptr [ Func ]
      mov  __0_RtnValue_,eax
      pop  edx
      pop  eax
      }

	VCL_DestroyAnsiString( StringPtr );
    }

  return __0_RtnValue_;
}
//---------------------------------------------------------------------------
inline void CTStrings::Clear()
{
  static void *Func = NULL;
  if( ! Func )
	{
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TStringList@Clear$qqrv" );
	}

  void *ThisPtr = Get_VCL_Handle();
  if( Func )
	{
    _asm
	  {
	  push eax

	  mov  eax,dword ptr [ThisPtr]
	  call dword ptr [ Func ]

	  pop eax
	  }
	}		

}
//---------------------------------------------------------------------------
inline void CTStrings::Delete( int index )
{
  static void *Func = NULL;
  if( ! Func )
	{
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TStringList@Delete$qqri" );
	}

  void *ThisPtr = Get_VCL_Handle();

  if( Func )
    {
    _asm
      {
      push eax
      push edx
      mov  edx,index
      mov  eax,dword ptr [ ThisPtr ]
      call dword ptr [ Func ]
      pop  edx
      pop  eax
      }
    }

}
//---------------------------------------------------------------------------
inline int CTStrings::GetCount()
{
  static void *Func = NULL;
  if( ! Func )
	{
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TStringList@GetCount$qqrv" );
	}

  void *ThisPtr = Get_VCL_Handle();
  int __0_RtnValue_ = (int)0;

  if( Func )
    {
    _asm
      {
      push eax
      mov  eax,dword ptr [ ThisPtr ]
      call dword ptr [ Func ]
      mov  __0_RtnValue_,eax
      pop  eax
      }
    }

  return (int)__0_RtnValue_;
}
//---------------------------------------------------------------------------
inline CTString CTStrings::Get( int index )
{
  static void *Func = NULL;
  if( ! Func )
	{
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TStringList@Get$qqri" );
	}

#ifdef _UNICODE
  wchar_t wch[ 2000 ];
  char *__0_RtnValue_ch = VCL_ExecuteStringFunc( Get_VCL_Handle(), Func, "i", index );

#if _MSC_VER >= 1400
  size_t   i;
  mbstowcs_s( &i, wch, 2000, __0_RtnValue_ch, 2000 );
#else
  mbstowcs( wch, __0_RtnValue_ch, 2000 ); 
#endif      
  CTString Rtn = wch;
  VCL_DestroyString( __0_RtnValue_ch );
#else
  char *__0_RtnValue_ = VCL_ExecuteStringFunc( Get_VCL_Handle(), Func, "i", index );
  CTString Rtn = __0_RtnValue_;
  VCL_DestroyString( __0_RtnValue_ );
#endif      
  return Rtn;
}
//---------------------------------------------------------------------------
inline void CTStrings::Put( int index, CTString value )
{
  static void *Func = NULL;
  if( ! Func )
	{
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TStringList@Put$qqrix17System@AnsiString" );
	}

  void *ThisPtr = Get_VCL_Handle();

  if( Func )
    {
    int __1_Param1 = index;

  #ifdef USE_STD_STRING
	const char*__1_Param2 = value.c_str();
  #else
    _VCL_TCHAR *__1_Param2 = value.LockBuffer();
  #endif
    void *StringPtr = VCL_CreateAnsiString( __1_Param2 );

  #ifndef USE_STD_STRING
    value.UnlockBuffer();
  #endif

    void *DataPtr = *(void **)StringPtr;

    _asm
      {
      push eax
      push edx
      push ecx
      mov  edx,__1_Param1
      mov  ecx,DataPtr
	  mov  eax,dword ptr [ThisPtr]
      call dword ptr [ Func ]
      pop  ecx
      pop  edx
      pop  eax
      }

	VCL_DestroyAnsiString( StringPtr );
    }

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
inline void CLPControl::Invalidate()
{
  static void *Func = NULL;
  if( ! Func )
    {
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Controls@TControl@Invalidate$qqrv" );
    }

  void *ThisPtr = Get_VCL_Handle();

  if( Func )
    {
    _asm
      {
      push eax

      mov  eax,dword ptr [ThisPtr]
      call dword ptr [ Func ]

      pop eax
      }
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
inline void CLPBaseCollectionProperty::Add()
{
  static void *Func = NULL;
  if( ! Func )
    {
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TCollection@Add$qqrv" );
    }

  void *ThisPtr = Get_VCL_Handle();
//  VCLHANDLE __0_RtnValue_ = NULL;

  if( Func )
    {
    _asm
      {
      push eax

      mov  eax,dword ptr [ThisPtr]
      call dword ptr [ Func ]

//      mov  __0_RtnValue_,eax
      pop eax
      }
    }
    
//  return __0_RtnValue_;
}
//---------------------------------------------------------------------------
inline void CLPBaseCollectionProperty::Add( int num_items )
{
  for( int i = 0; i < num_items; ++ i )
	Add();
}
//---------------------------------------------------------------------------
inline void CLPBaseCollectionProperty::Clear()
{
  static void *Func = NULL;
  if( ! Func )
    {
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TCollection@Clear$qqrv" );
    }

  int Value = m_control->Object->Properties[ (_VCL_TCHAR *)m_PropertyName ];
  void *ThisPtr = *((void **)&Value );
//  void *ThisPtr = Get_VCL_Handle();
  if( Func )
    {
    _asm
      {
      push eax

      mov  eax,dword ptr [ThisPtr]
      call dword ptr [ Func ]

      pop eax
      }
    }
    
}
//---------------------------------------------------------------------------
inline void CLPBaseCollectionProperty::Delete( int index )
{
  static void *Func = NULL;
  if( Func == NULL )
	{
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TCollection@Delete$qqri" );
	}

  void *__0_ThisPtr_ = Get_VCL_Handle();

  if( Func )
    {
    _asm
      {
      push eax
      push edx
      mov  edx,index
      mov  eax,dword ptr [ __0_ThisPtr_ ]
      call dword ptr [ Func ]
      pop  edx
      pop  eax
      }
    }

}
//---------------------------------------------------------------------------
inline void CLPBaseCollectionProperty::Insert( int index )
{
  static void *Func = NULL;
  if( ! Func )
	{
    void *VCLHandle = Get_rtl60();
    Func = (void *)VCL_GetFunction( VCLHandle, "@Classes@TCollection@Insert$qqri" );
	}

  void *ThisPtr = Get_VCL_Handle();

  if( Func )
    {
    _asm
      {
      push eax
      push edx
      mov  edx,index
      mov  eax,dword ptr [ ThisPtr ]
      call dword ptr [ Func ]
      pop  edx
      pop  eax
      }
    }

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
inline CLPString::CLPString() :
  m_Buffer( NULL ),
  m_Size( 0 )
{
}
//---------------------------------------------------------------------------
inline CLPString::CLPString( int a_Value ) :
  m_Buffer( NULL )
{
  _VCL_TCHAR TempBuffer[ 15 ];

#ifdef _UNICODE
    #if _MSC_VER >= 1400
        _ltow_s( a_Value, TempBuffer, 15, 10 );
    #else
        _ltow( a_Value, TempBuffer, 10 );
    #endif
#else
  itoa( a_Value, TempBuffer, 10 );
#endif

  CopyFrom( TempBuffer );
}
//---------------------------------------------------------------------------
inline CLPString::CLPString( const _VCL_TCHAR *a_string ) :
  m_Buffer( NULL )
{
  CopyFrom( a_string );
}
//---------------------------------------------------------------------------
inline CLPString::CLPString( const CLPString &a_string ) :
  m_Buffer( NULL )
{
  CopyFrom( a_string );
}
//---------------------------------------------------------------------------
inline CLPString::~CLPString()
{
  if( m_Buffer )
    delete [] m_Buffer;

  m_Buffer = NULL;
}
//---------------------------------------------------------------------------
inline void CLPString::CopyFrom( const _VCL_TCHAR *a_string )
{
  if( m_Buffer )
    delete [] m_Buffer;

#ifdef _UNICODE
  m_Size = (int)wcslen( a_string );
#else
  m_Size = (int)strlen( a_string );
#endif
  if( m_Size == 0 )
    m_Buffer = NULL;

  else
    {
    m_Buffer = new _VCL_TCHAR [ m_Size + 1 ];
#ifdef _UNICODE
    memcpy( m_Buffer, a_string, 2 * ( m_Size + 1 ));
#else
    memcpy( m_Buffer, a_string, m_Size + 1 );
#endif
    }
}
//---------------------------------------------------------------------------
inline void CLPString::CopyFrom( const CLPString &a_string )
{
  if( m_Buffer )
    delete [] m_Buffer;

  m_Size = a_string.m_Size;
  if( m_Size == 0 )
    m_Buffer = NULL;

  else
    {
    m_Buffer = new _VCL_TCHAR [ m_Size + 1 ];
#ifdef _UNICODE
    memcpy( m_Buffer, a_string.m_Buffer, 2 * ( m_Size + 1 ));
#else
    memcpy( m_Buffer, a_string.m_Buffer, m_Size + 1 );
#endif
    }
}
//---------------------------------------------------------------------------
inline CLPString &CLPString::operator = ( const _VCL_TCHAR *a_string )
{
  CopyFrom( a_string );
  return *this;
}
//---------------------------------------------------------------------------
inline CLPString &CLPString::operator += ( const _VCL_TCHAR *a_string )
{
  if( m_Size == 0 )
    CopyFrom( a_string );

  else
    {
#ifdef _UNICODE
    int SizeOther = (int)wcslen( a_string );
#else
    int SizeOther = (int)strlen( a_string );
#endif
    _VCL_TCHAR *NewBuffer = new _VCL_TCHAR[ m_Size + SizeOther + 1 ];

#ifdef _UNICODE
    memcpy( NewBuffer, m_Buffer, 2 * ( m_Size ));
    memcpy( NewBuffer + m_Size, a_string, 2 * ( SizeOther + 1 ));
#else
    memcpy( NewBuffer, m_Buffer, m_Size );
    memcpy( NewBuffer + m_Size, a_string, SizeOther + 1 );
#endif

    delete [] m_Buffer;
    m_Buffer = NewBuffer;
    m_Size += SizeOther;
    }

  return *this;
}
//---------------------------------------------------------------------------
inline CLPString CLPString::operator + ( const _VCL_TCHAR *a_string )
{
  CLPString Result( *this );
  Result += a_string;
  return Result;
}
//---------------------------------------------------------------------------
inline CLPString &CLPString::operator = ( const CLPString &a_string )
{
  CopyFrom( a_string );
  return *this;
}
//---------------------------------------------------------------------------
inline CLPString &CLPString::operator += ( const CLPString &a_string )
{
  if( m_Size == 0 )
    CopyFrom( a_string );

  else
    {
    _VCL_TCHAR *NewBuffer = new _VCL_TCHAR[ m_Size + a_string.m_Size + 1 ];

#ifdef _UNICODE
    memcpy( NewBuffer, m_Buffer, 2 * ( m_Size ));
    memcpy( NewBuffer + m_Size, a_string.m_Buffer, 2 * ( a_string.m_Size + 1 ));
#else
    memcpy( NewBuffer, m_Buffer, m_Size );
    memcpy( NewBuffer + m_Size, a_string.m_Buffer, a_string.m_Size + 1 );
#endif

    delete [] m_Buffer;
    m_Buffer = NewBuffer;
    m_Size += a_string.m_Size;
    }

  return *this;
}
//---------------------------------------------------------------------------
inline CLPString CLPString::operator + ( const CLPString &a_string )
{
  CLPString Result( *this );
  Result += a_string;
  return Result;
}
//---------------------------------------------------------------------------
inline void *Get_VCSignalLabPkgCB6()
{
	static void *_LibraryHandle = NULL;
	if( ! _LibraryHandle )
		_LibraryHandle = VCL_LoadLibrary( "VCSignalLabPkgCB6.bpl" );

	return _LibraryHandle;
}
//---------------------------------------------------------------------------
inline CTPicture::CTPicture() :
	inherited( NULL, hmNone )
{
  void  *VCLHandle = Get_VCSignalLabPkgCB6();

  typedef void *( *PFunc )();

  static PFunc Func = NULL;
  if( ! Func )
    Func = (PFunc)VCL_GetFunction( VCLHandle, "@LPCreatePictureProxy$qv" );

  if( Func )
	  m_Handle = Func();

  else	
	m_Handle = NULL;
  
}
//---------------------------------------------------------------------------
inline CTPicture::CTPicture( const CTPicture &picture ) :
	inherited( picture )
{
  void  *VCLHandle = Get_VCSignalLabPkgCB6();

  typedef void *( *PFunc )( void *APicture );

  static PFunc Func = NULL;
  if( ! Func )
    Func = (PFunc)VCL_GetFunction( VCLHandle, "@LPCreatePictureCopyProxy$qpv" );

  if( Func )
	  m_Handle = Func( picture.m_Handle );

  else	
	m_Handle = NULL;
  
}
//---------------------------------------------------------------------------
inline CTPicture::CTPicture( HBITMAP bitmap ) :
	inherited( NULL, hmNone )
{
  void  *VCLHandle = Get_VCSignalLabPkgCB6();

  typedef void *( *PFunc )( HBITMAP ABitmap );

  static PFunc Func = NULL;
  if( ! Func )
    Func = (PFunc)VCL_GetFunction( VCLHandle, "@LPCreatePictureBitmapProxy$qpv" );

  if( Func )
	  m_Handle = Func( bitmap );

  else	
	m_Handle = NULL;
  
}
//---------------------------------------------------------------------------
inline CTPicture::CTPicture( CLPBaseComponent *a_control, const CLPString a_PropertyName ) :
    inherited( a_control, a_PropertyName ),
    m_Handle( NULL )
{
}
//---------------------------------------------------------------------------
inline CTPicture::CTPicture( CLPClassProperty *a_property, const CLPString a_PropertyName ) :
    inherited( a_property, a_PropertyName ),
    m_Handle( NULL )
{
}
//---------------------------------------------------------------------------
inline CTPicture::~CTPicture()
{
  if( ! m_Handle )
	  return;

  void  *VCLHandle = Get_VCSignalLabPkgCB6();

  typedef void *( *PFunc )( void *AProxy );

  static PFunc Func = NULL;
  if( ! Func )
    Func = (PFunc)VCL_GetFunction( VCLHandle, "@LPDestroyObjectProxy$qpvt1" );

  if( Func )
	Func( m_Handle );
  
}
//---------------------------------------------------------------------------
inline CTPicture &CTPicture::operator = ( const CTPicture &data )
{
	void  *VCLHandle = Get_VCSignalLabPkgCB6();

	typedef void *( *PFunc )( void *AProxy, void *AOtherProxy );

	static PFunc Func = NULL;
	if( ! Func )
		Func = (PFunc)VCL_GetFunction( VCLHandle, "@LPAssignObjectProxy$qpvt1" );

	if( Func )
		Func( GetHandle(), data.GetHandle() );
  
	return *this;
  }
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class T > CLPIndexProperty_1_Item<TObject,TIndex1,T> CLPIndexProperty_1<TObject,TIndex1,T>::operator[]( TIndex1 index1 )
{
	  return CLPIndexProperty_1_Item<TObject,TIndex1,T>( this, index1 );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > CLPIndexProperty_2_ArrayItem<TObject,TIndex1,TIndex2,T> CLPIndexProperty_2<TObject,TIndex1,TIndex2,T>::operator[]( TIndex1 index1 )
{
	  return CLPIndexProperty_2_ArrayItem<TObject,TIndex1, TIndex2,T>( this, index1 );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template< class TObject, class TIndex1, class TIndex2, class T > CLPReadIndexProperty_2_ArrayItem<TObject,TIndex1,TIndex2,T> CLPReadIndexProperty_2<TObject,TIndex1,TIndex2,T>::operator[]( TIndex1 index1 )
{
	  return CLPReadIndexProperty_2_ArrayItem<TObject,TIndex1, TIndex2,T>( this, index1 );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
