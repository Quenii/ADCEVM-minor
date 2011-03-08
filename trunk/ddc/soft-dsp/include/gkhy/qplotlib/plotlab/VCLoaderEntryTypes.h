//---------------------------------------------------------------------------

#ifndef VCLoaderEntryTypesH
#define VCLoaderEntryTypesH
//---------------------------------------------------------------------------
enum EVCL_COLLECTION_ACTION { caAdded, caRemoved };
enum EVCL_PIN_ACTION { paAdded, paRemoved, paChanged };
enum EVCL_PINLIST_ACTION { plaAdded, plaRemoved, plaSwapped };
enum PIN_TYPE { ptError, ptSource, ptSink, ptState };
enum DESIGN_NOTIFY { dnModified, dnShowPropertyDialog };
enum PROPERTY_ATTRIBUTE { vpaValueList, vpaSubProperties, vpaDialog, vpaMultiSelect, vpaAutoUpdate, vpaSortList, vpaReadOnly, vpaRevertable, vpaFullWidthName, vpaVolatileSubProperties, vpaVCL, vpaNotNestable };

#ifdef __cplusplus_cli
  typedef int VCLHANDLE;
#else
  typedef void * VCLHANDLE;
#endif

typedef int ( __stdcall *FUNC_ENTRY)();
typedef void ( __stdcall *FUNC_PIN_NOTIFY)( EVCL_PIN_ACTION Action, VCLHANDLE PinOwner, const char *PinName, VCLHANDLE PinHandle, void *CustomData );
typedef void ( __stdcall *FUNC_DISP_NOTIFY)( EVCL_PIN_ACTION Action, VCLHANDLE Dispatcher, void *CustomData );
typedef void ( __stdcall *FUNC_PINLIST_NOTIFY)( EVCL_PINLIST_ACTION Action, VCLHANDLE PinOwner, int PinIndex1, int PinIndex2, void *CustomData );
typedef void ( __stdcall *FUNC_COLLECTION_NOTIFY)( EVCL_COLLECTION_ACTION Action, VCLHANDLE Collection, VCLHANDLE CollectionItem, void *CustomData );
typedef void ( __stdcall *FUNC_REGISTER_COMPONENT_NOTIFY)( const char *ComponentName, void *CustomData );
typedef void ( __stdcall *FUNC_DESIGN_NOTIFY)( DESIGN_NOTIFY Action, VCLHANDLE Component, VCLHANDLE PropertyOwner, char *String, void *CustomData );
typedef int ( __stdcall *FUNC_EXCEPTION)( void *CustomData, char *EexceptionMessage );
//---------------------------------------------------------------------------
#endif
