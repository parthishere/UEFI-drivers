#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Protocol/LoadedImage.h>
#include <Library/DevicePathLib.h>


#define offsetof(a,b) ((INTN)(&(((a*)(0))->b)))

#define container_of(ptr, type, member) ({                      \
		const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
		(type *)( (char *)__mptr - offsetof(type,member) );})


typedef struct {
	UINTN Signature;
	LIST_ENTRY AllHandles;
	LIST_ENTRY Protocols;
	UINTN LocateRequest;
	UINT64 Key;
} IHANDLE;

typedef struct {
	UINTN Signature;
	LIST_ENTRY AllEntries;
	EFI_GUID ProtocolID;
	LIST_ENTRY Protocols;
	LIST_ENTRY Notify;
} PROTOCOL_ENTRY;

typedef struct{
	UINTN Signature;
	LIST_ENTRY Link;
	IHANDLE *Handle;
	LIST_ENTRY ByProtocol;
	PROTOCOL_ENTRY *Protocol;
	VOID *Interface;
	LIST_ENTRY OpenList;
	UINTN OpenListCount;
} PROTOCOL_INTERFACE;

EFI_STATUS
	EFIAPI
UefiMain (
		IN EFI_HANDLE        ImageHandle,
		IN EFI_SYSTEM_TABLE  *SystemTable
	 )
{
	IHANDLE* MyHandle = ImageHandle;

	
	Print(L"Signature: %c %c %c %c\n", (MyHandle->Signature >>  0) & 0xff,
			(MyHandle->Signature >>  8) & 0xff,
			(MyHandle->Signature >> 16) & 0xff,
			(MyHandle->Signature >> 24) & 0xff);

	Print(L"Back Protocol Interface Link %p\n", MyHandle->Protocols.BackLink);
	Print(L"Forward Protocol Interface Link %p\n", MyHandle->Protocols.ForwardLink);

	LIST_ENTRY *FirstLink = MyHandle->Protocols.ForwardLink;
	LIST_ENTRY *CurrentLink = FirstLink;

	do{

		PROTOCOL_INTERFACE *MyProtocolInterface = container_of(CurrentLink, PROTOCOL_INTERFACE, Link);

		Print(L"\n");
		Print(L"Current Link : %p \n", CurrentLink);
		Print(L"Signature: %c %c %c %c\n", (MyProtocolInterface->Signature >>  0) & 0xff,
				(MyProtocolInterface->Signature >>  8) & 0xff,
				(MyProtocolInterface->Signature >> 16) & 0xff,
				(MyProtocolInterface->Signature >> 24) & 0xff);
		Print(L"Back Link: %p\n", MyProtocolInterface->Link.BackLink);
		Print(L"Forward Link: %p\n", MyProtocolInterface->Link.ForwardLink);
		Print(L"GUID=%g\n", MyProtocolInterface->Protocol->ProtocolID);
		CurrentLink = MyProtocolInterface->Link.ForwardLink;

	} while(CurrentLink != FirstLink && CurrentLink != NULL);

	Print(L"\n");
	return EFI_SUCCESS;
}
