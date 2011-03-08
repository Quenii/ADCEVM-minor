//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( __int64 Value )
{
    if( ! VCL_SetInteger64Property( Object.GetHandle(), PropertyName, Value ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( int Value )
{
    if( ! VCL_SetIntegerProperty( Object.GetHandle(), PropertyName, Value ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( unsigned int Value )
{
    if( ! VCL_SetIntegerProperty( Object.GetHandle(), PropertyName, Value ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( long Value )
{
    if( ! VCL_SetIntegerProperty( Object.GetHandle(), PropertyName, Value ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( unsigned long Value )
{
    if( ! VCL_SetIntegerProperty( Object.GetHandle(), PropertyName, Value ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( float Value )
{
    if( ! VCL_SetFloatProperty( Object.GetHandle(), PropertyName, Value ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( double Value )
{
    if( ! VCL_SetDoubleProperty( Object.GetHandle(), PropertyName, Value ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( CTString Value )
{
  #ifdef USE_STD_STRING
    if( ! VCL_SetStringProperty( Object.GetHandle(), PropertyName, Value.c_str() ))
		{
  #else
    if( ! VCL_SetStringProperty( Object.GetHandle(), PropertyName, Value.LockBuffer() ))
		{
		Value.UnlockBuffer();
  #endif
        throw CTString( "Unable to set property : " ) + PropertyName;
		}

  #ifndef USE_STD_STRING
	Value.UnlockBuffer();
  #endif

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( TObject &Value )
{
    if( ! VCL_SetObjectProperty( Object.GetHandle(), PropertyName, Value.GetHandle() ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject> & CVCLProperty<TObject>::operator = ( void *Value )
{
    if( ! VCL_SetObjectProperty( Object.GetHandle(), PropertyName, Value ))
        throw CTString( "Unable to set property : " ) + PropertyName;

	return *this;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( __int64 Value )
{
	return ((__int64) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( int Value )
{
	return ((int) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( unsigned int Value )
{
	return ((unsigned int) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( long Value )
{
	return ((long) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( unsigned long Value )
{
	return ((unsigned long) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( float Value )
{
	return ((float) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( double Value )
{
	return ((double) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( CTString Value )
{
	return ((CTString) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator == ( TObject &Value )
{
	return ((TObject) *this ) == Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator != ( long Value )
{
	return ((long) *this ) != Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator != ( int Value )
{
	return ((int) *this ) != Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator != ( unsigned int Value )
{
	return ((unsigned int) *this ) != Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator != ( __int64 Value )
{
	return ((__int64) *this ) != Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator != ( float Value )
{
	return ((float) *this ) != Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator != ( double Value )
{
	return ((double) *this ) != Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator != ( CTString Value )
{
	return ((CTString) *this ) != Value;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::operator != ( TObject &Value )
{
	return ((TObject) *this ) != Value;
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator CTString ()
{
	return AsString();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator int ()
{
    return AsInt();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator unsigned int ()
{
    return AsUnsignedInt();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator long ()
{
    return AsInt();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator unsigned long ()
{
    return AsUnsignedInt();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator __int64 ()
{
    return AsInt64();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator bool ()
{
    return AsBool();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator float ()
{
    return AsFloat();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator double ()
{
    return AsDouble();
}
//---------------------------------------------------------------------------
template <class TObject> CVCLProperty<TObject>::operator TObject ()
{
    return AsObject();
}
//---------------------------------------------------------------------------
template <class TObject> CTString CVCLProperty<TObject>::AsString()
{
	void *StringHandle;
	_VCL_TCHAR *Buff = VCL_GetStringProperty( Object.GetHandle(), PropertyName, &StringHandle );
    if( !Buff )
        throw CTString( "Unable to set property : " ) + PropertyName;

	CTString Result = Buff;

	VCL_DestroyAnsiString( StringHandle );

  #ifdef _UNICODE
    delete [] Buff;
  #endif

	return Result;
}
//---------------------------------------------------------------------------
template <class TObject> int CVCLProperty<TObject>::AsInt()
{
    int Result;
    if( ! VCL_GetIntegerProperty( Object.GetHandle(), PropertyName, &Result ))
        throw CTString( "Unable to get property : " ) + PropertyName;

    return Result;
}
//---------------------------------------------------------------------------
template <class TObject> unsigned int CVCLProperty<TObject>::AsUnsignedInt()
{
    int Result;
    if( ! VCL_GetIntegerProperty( Object.GetHandle(), PropertyName, &Result ))
        throw CTString( "Unable to get property : " ) + PropertyName;

    return ( unsigned int )Result;
}
//---------------------------------------------------------------------------
template <class TObject> __int64 CVCLProperty<TObject>::AsInt64()
{
    __int64 Result;
    if( ! VCL_GetInteger64Property( Object.GetHandle(), PropertyName, &Result ))
        throw CTString( "Unable to get property : " ) + PropertyName;

    return Result;
}
//---------------------------------------------------------------------------
template <class TObject> bool CVCLProperty<TObject>::AsBool()
{
    int Result;
    if( ! VCL_GetIntegerProperty( Object.GetHandle(), PropertyName, &Result ))
        throw CTString( "Unable to get property : " ) + PropertyName;

    return Result != 0;
}
//---------------------------------------------------------------------------
template <class TObject> float CVCLProperty<TObject>::AsFloat()
{
    float Result;
    if( ! VCL_GetFloatProperty( Object.GetHandle(), PropertyName, &Result ))
        throw CTString( "Unable to get property : " ) + PropertyName;
    
    return Result;
}
//---------------------------------------------------------------------------
template <class TObject> double CVCLProperty<TObject>::AsDouble()
{
    double Result;
    if( ! VCL_GetDoubleProperty( Object.GetHandle(), PropertyName, &Result ))
        throw CTString( "Unable to get property : " ) + PropertyName;
    
    return Result;
}
//---------------------------------------------------------------------------
template <class TObject> TObject CVCLProperty<TObject>::AsObject()
{
    VCLHANDLE Result;
    if( ! VCL_GetObjectProperty( Object.GetHandle(), PropertyName, &Result ))
        throw CTString( "Unable to get property : " ) + PropertyName;
    
    return TObject( Result );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
