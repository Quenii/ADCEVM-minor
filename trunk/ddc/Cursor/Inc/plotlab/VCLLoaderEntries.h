//---------------------------------------------------------------------------

#ifndef VCLLoaderEntriesH
#define VCLLoaderEntriesH
//---------------------------------------------------------------------------
#ifdef __VCLLOADER_DLL
  #define  MODE __declspec(dllexport)
#else
  #define  MODE __declspec(dllimport)
#endif
//---------------------------------------------------------------------------
#include <VCLoaderEntryTypes.h>

#ifndef _WINDOWS_
  #include <windows.h>
#endif
//---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif
//---------------------------------------------------------------------------
FUNC_ENTRY      MODE    __stdcall VCL_GetFunction( VCLHANDLE LibraryHandle, const char * FunctionName );
void            MODE  * __stdcall VCL_LoadLibrary( const char * LibraryFileName );
void            MODE    __stdcall VCL_UnloadLibrary( VCLHANDLE handle );

int             MODE    __stdcall VCL_InitControls( HWND ApplicationHandle );
HWND            MODE    __stdcall VCL_GetApplicationHandle();
void            MODE    __stdcall VCL_SetApplicationHandle( HWND ApplicationHandle );
void            MODE    __stdcall VCL_Shutdown();
int             MODE    __stdcall VCL_Loaded();
int             MODE    __stdcall VCL_ComponentLoaded( VCLHANDLE Object, BOOL DesignTime );
int             MODE    __stdcall VCL_BeginLoading( VCLHANDLE Object );
int             MODE    __stdcall VCL_EndLoading( VCLHANDLE Object, BOOL DesignTime );

VCLHANDLE       MODE    __stdcall VCL_NewObject( const char * ComponentType );
VCLHANDLE       MODE    __stdcall VCL_NewComponent( const char * ComponentType, VCLHANDLE OwnerHandle, BOOL DesignTime );
VCLHANDLE       MODE    __stdcall VCL_NewControl( HWND ParentWindow, const char * ControlType, VCLHANDLE OwnerHandle, BOOL DesignTime );
VCLHANDLE       MODE    __stdcall VCL_NewControlSize( HWND ParentWindow, const char * type, int Left, int Top, int Width, int Height, VCLHANDLE OwnerHandle, BOOL DesignTime );

void            MODE    __stdcall VCL_AssignToObject( VCLHANDLE FromObject, VCLHANDLE ToObject );

int             MODE    __stdcall VCL_SetComponentList( VCLHANDLE Object, VCLHANDLE ComponentList );

int             MODE    __stdcall VCL_GetBinaryData( VCLHANDLE Object, void **Buffer, int *Size );
int             MODE    __stdcall VCL_SetBinaryData( VCLHANDLE Object, void *Buffer, int Size );
void            MODE    __stdcall VCL_ReleaseBinaryData( void *Buffer );

VCLHANDLE       MODE    __stdcall VCL_GetControlHandle( VCLHANDLE AHandle );
VCLHANDLE       MODE    __stdcall VCL_GetRootOwnerHandle( VCLHANDLE Component );

int             MODE    __stdcall VCL_SetComponentName( VCLHANDLE AHandle, const char * Name );

int             MODE    __stdcall VCL_Delete( VCLHANDLE Object );

int             MODE    __stdcall VCL_ErrorNotification( int Enable );
int             MODE    __stdcall VCL_SetExceptionCallback( FUNC_EXCEPTION Function, void *CustomData );

int             MODE    __stdcall VCL_SetStringProperty( VCLHANDLE Object, const char * PropertyName, const char * PropertyValue );
int             MODE    __stdcall VCL_SetIntegerProperty( VCLHANDLE Object, const char * PropertyName, int PropertyValue );
int             MODE    __stdcall VCL_SetCardinalProperty( VCLHANDLE Object, const char * PropertyName, unsigned int PropertyValue );
int             MODE    __stdcall VCL_SetInteger64Property( VCLHANDLE Object, const char * PropertyName, __int64 PropertyValue );
int             MODE    __stdcall VCL_SetFloatProperty( VCLHANDLE Object, const char * PropertyName, float PropertyValue );
int             MODE    __stdcall VCL_SetDoubleProperty( VCLHANDLE Object, const char * PropertyName, double PropertyValue );
int             MODE    __stdcall VCL_SetObjectProperty( VCLHANDLE Object, const char * PropertyName, VCLHANDLE PropertyValue );
int             MODE    __stdcall VCL_SetMethodProperty( VCLHANDLE Object, const char * PropertyName,  void *Function, void *Data );
int             MODE    __stdcall VCL_SetMethodPropertyAndType( VCLHANDLE Object, const char * PropertyName,  void *Function, void *Data, int FunctionIndex );

int             MODE    __stdcall VCL_GetMethodProperty( VCLHANDLE Object, const char * PropertyName,  void **Function, void **Data );
char            MODE  * __stdcall VCL_GetStringProperty( VCLHANDLE Object, const char * PropertyName, VCLHANDLE *StringHandler );
int             MODE    __stdcall VCL_GetIntegerProperty( VCLHANDLE Object, const char * PropertyName, int *ReturnValue );
int             MODE    __stdcall VCL_GetCardinalProperty( VCLHANDLE Object, const char * PropertyName, unsigned int *ReturnValue );
int             MODE    __stdcall VCL_GetInteger64Property( VCLHANDLE Object, const char * PropertyName, __int64 *ReturnValue );
int             MODE    __stdcall VCL_GetFloatProperty( VCLHANDLE Object, const char * PropertyName, float *ReturnValue );
int             MODE    __stdcall VCL_GetDoubleProperty( VCLHANDLE Object, const char * PropertyName, double *ReturnValue );
int             MODE    __stdcall VCL_GetObjectProperty( VCLHANDLE Object, const char * PropertyName,  VCLHANDLE *ReturnValue );

VCLHANDLE       MODE    __stdcall VCL_CreateAnsiString( const char *str );
void            MODE    __stdcall VCL_DestroyAnsiString( VCLHANDLE AString );
VCLHANDLE       MODE    __stdcall VCL_CallAnsiStringGetMember( VCLHANDLE Instance, VCLHANDLE Function );
char            MODE  * __stdcall VCL_GetCString( VCLHANDLE AString );

VCLHANDLE       MODE    __stdcall VCL_CreateStringList();
int             MODE    __stdcall VCL_GetStringsCount( VCLHANDLE AStrings );
VCLHANDLE       MODE    __stdcall VCL_GetStringsItem( VCLHANDLE AStrings, int AIndex );
void            MODE    __stdcall VCL_SetStringsItem( VCLHANDLE AStrings, int AIndex, char *AString );

char            MODE  * __stdcall VCL_ExecuteStringFunc( VCLHANDLE Object, VCLHANDLE Function, char *Format, ... );
void            MODE    __stdcall VCL_DestroyString( char *str );

int             MODE    __stdcall VCL_ConnectPins( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Object2, const char * Pin2Name );
int             MODE    __stdcall VCL_ConnectAfterPins( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Object2, const char * Pin2Name, VCLHANDLE AfterObject, const char * AfterPinName );
int             MODE    __stdcall VCL_ConnectPinsByState( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Object2, const char * Pin2Name );
int             MODE    __stdcall VCL_ConnectPinsByStateAfter( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Object2, const char * Pin2Name, VCLHANDLE AfterObject, const char * AfterPinName );
int             MODE    __stdcall VCL_DisconnectPin( VCLHANDLE Object, const char * PinName );
int             MODE    __stdcall VCL_CanConnectToPin( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Object2, const char * Pin2Name );
int             MODE    __stdcall VCL_CanConnectAfterPin( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Object2, const char * Pin2Name, VCLHANDLE AfterObject, const char * AfterPinName );
int             MODE    __stdcall VCL_CanConnectToState( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Dispatcher );
int             MODE    __stdcall VCL_ConnectToState( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Dispatcher );
int             MODE    __stdcall VCL_ConnectToStateAfterPin( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Dispatcher, VCLHANDLE AfterObject, const char * AfterPinName );
int             MODE    __stdcall VCL_IsConnectedToPin( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Object2, const char * Pin2Name );
int             MODE    __stdcall VCL_IsConnectedToPinByState( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Object2, const char * Pin2Name );
int             MODE    __stdcall VCL_IsConnectedToState( VCLHANDLE Object1, const char * Pin1Name, VCLHANDLE Dispatcher );
int             MODE    __stdcall VCL_IsConnectedPin( VCLHANDLE Object, const char * PinName );
int             MODE    __stdcall VCL_IsStateConnectedPin( VCLHANDLE Object, const char * PinName );
int             MODE    __stdcall VCL_GetConnectedPinCount( VCLHANDLE Object, const char * PinName );
VCLHANDLE       MODE    __stdcall VCL_GetConnectedPin( VCLHANDLE Object, const char * PinName, int PinIndex );
VCLHANDLE       MODE    __stdcall VCL_GetConnectedAfterPin( VCLHANDLE Object, const char * PinName, int PinIndex );
int             MODE    __stdcall VCL_GetConnectedDispatcherCount( VCLHANDLE Object, const char * PinName );
VCLHANDLE       MODE    __stdcall VCL_GetConnectedDispatcher( VCLHANDLE Object, const char * PinName, int DispatcherIndex );

int             MODE    __stdcall VCL_GetDispatcherPinCount( VCLHANDLE Dispatcher );
VCLHANDLE       MODE    __stdcall VCL_GetDispatcherPin( VCLHANDLE Dispatcher, int PinIndex );
VCLHANDLE       MODE    __stdcall VCL_GetDispatcherAfterPin( VCLHANDLE Dispatcher, int PinIndex );
VCLHANDLE       MODE    __stdcall VCL_GetDispatcherName( VCLHANDLE Dispatcher );
int             MODE    __stdcall VCL_SetDispatcherName( VCLHANDLE Dispatcher, char * Name );

char            MODE  * __stdcall VCL_GetConnectionTypeString( VCLHANDLE Object, const char * PinName, int PinIndex, VCLHANDLE *StringHandler );
char            MODE  * __stdcall VCL_GetPinDisplayName( VCLHANDLE Object, const char * PinName, VCLHANDLE *StringHandler );
PIN_TYPE        MODE    __stdcall VCL_GetPinType( VCLHANDLE Object, const char * PinName ); 
PIN_TYPE        MODE    __stdcall VCL_GetPinListPinType( VCLHANDLE Object, const char * PinName, int PinIndex ); 

int             MODE    __stdcall VCL_PulsePin( VCLHANDLE Object, const char * PinName ); // Obsolete!

int             MODE    __stdcall VCL_GetDispatcherCount();
VCLHANDLE       MODE    __stdcall VCL_GetDispatcher( int DispatcherIndex );

int             MODE    __stdcall VCL_AddDispatcherNotifier( FUNC_DISP_NOTIFY NotifyFunction, void *CustomData ); // returns NotifierID
void            MODE    __stdcall VCL_RemoveDispatcherNotifier( int NotifierID );

int             MODE    __stdcall VCL_AddPinNotifier( FUNC_PIN_NOTIFY NotifyFunction, void *CustomData ); // returns NotifierID
void            MODE    __stdcall VCL_RemovePinNotifier( int NotifierID );

int             MODE    __stdcall VCL_AddPinListNotifier( FUNC_PINLIST_NOTIFY NotifyFunction, void *CustomData ); // returns NotifierID
void            MODE    __stdcall VCL_RemovePinListNotifier( int NotifierID );

int             MODE    __stdcall VCL_AddCollectionNotifier( VCLHANDLE CollectionObject, FUNC_COLLECTION_NOTIFY NotifyFunction, void *CustomData ); // returns NotifierID
void            MODE    __stdcall VCL_RemoveCollectionNotifier( int NotifierID );

int             MODE    __stdcall VCL_AddComponentRegisterNotifier( FUNC_REGISTER_COMPONENT_NOTIFY NotifyFunction, void *CustomData ); // returns NotifierID
void            MODE    __stdcall VCL_RemoveComponentRegisterNotifier( int NotifierID );

VCLHANDLE       MODE    __stdcall VCL_GetComponentEditor( VCLHANDLE Component );
int             MODE    __stdcall VCL_ComponetEditorGetVerbCount( VCLHANDLE Editor );
VCLHANDLE       MODE    __stdcall VCL_ComponetEditorGetVerb( VCLHANDLE Editor, int Index );
void            MODE    __stdcall VCL_ComponetEditorExecuteVerb( VCLHANDLE Editor, int Index );
int             MODE    __stdcall VCL_ComponetEditorEdit( VCLHANDLE Editor );

VCLHANDLE       MODE    __stdcall VCL_GetPropertyEditor( VCLHANDLE Owner, const char * PropertyName );
int             MODE    __stdcall VCL_GetPropertyEditorAttributes( VCLHANDLE Editor );
int             MODE    __stdcall VCL_GetPropertyEditorValuesCount( VCLHANDLE Editor );
VCLHANDLE       MODE    __stdcall VCL_GetPropertyEditorValueItem( VCLHANDLE Editor, int Index );
int             MODE    __stdcall VCL_PropertyEditorEdit( VCLHANDLE Editor );
VCLHANDLE       MODE    __stdcall VCL_GetPropertyEditorValueString( VCLHANDLE Editor );
void            MODE    __stdcall VCL_SetPropertyEditorValueString( VCLHANDLE Editor, char *Value );

void            MODE    __stdcall VCL_SetDesignerNotifier( FUNC_DESIGN_NOTIFY Function, void *CustomData );

//---------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
//---------------------------------------------------------------------------
#endif
