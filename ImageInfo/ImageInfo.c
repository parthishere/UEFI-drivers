#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Protocol/LoadedImage.h>
#include <Library/DevicePathLib.h> // For ConvertDevicePathToText
#include <Library/MemoryAllocationLib.h> // For FreePool function

EFI_STATUS
	EFIAPI
UefiMain (
		IN EFI_HANDLE        ImageHandle,
		IN EFI_SYSTEM_TABLE  *SystemTable
	 )
{
	EFI_STATUS Status;
	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;


	// typedef
	// EFI_STATUS
	// (EFIAPI *EFI_HANDLE_PROTOCOL) (
	//  IN EFI_HANDLE Handle,
	//  IN EFI_GUID *Protocol,
	//  OUT VOID **Interface
	// );
	// 
	// Parameters:
	// Handle       The handle being queried. If Handle isNULL, then EFI_INVALID_PARAMETER is returned.
	// Protocol     The published unique identifier of the protocol. It is the caller’s responsibility to pass in a valid GUID. 
	// Interface    Supplies the address where a pointer to the corresponding Protocol Interface is returned.
	//              NULL will be returned in *Interface if a structure is not associated with Protocol.
	// 
	// Description:
	// The HandleProtocol() function queries Handle to determine if it supports Protocol. If it does, then on return Interface points to a pointer to the corresponding Protocol Interface. Interface can then be passed to any protocol service to identify the context of the request.
	// 


	Status = gBS->HandleProtocol(
			ImageHandle,
			&gEfiLoadedImageProtocolGuid,
			(VOID **) &LoadedImage
			);

	if (Status == EFI_SUCCESS) {
		EFI_DEVICE_PATH_PROTOCOL* DevicePath;

		Status = gBS->HandleProtocol(
				ImageHandle,
				&gEfiLoadedImageDevicePathProtocolGuid,
				(VOID**) &DevicePath
				);

		if (Status == EFI_SUCCESS) {
			Print(L"Image device: %s\n", ConvertDevicePathToText(DevicePath, FALSE, TRUE));
			Print(L"Image file: %s\n",  ConvertDevicePathToText(LoadedImage->FilePath, FALSE, TRUE));
			Print(L"Image Base: %X\n", LoadedImage->ImageBase);
			Print(L"Image Size: %X\n", LoadedImage->ImageSize);
		} else {
			Print(L"Can't get EFI_LOADED_IMAGE_PROTOCOL, Status=%r\n", Status);
		}
	} else {
		Print(L"Can't get EFI_DEVICE_PATH_PROTOCOL, Status=%r\n", Status);
	}

	Print(L"________\n");
	EFI_GUID **ProtocolGuidArray;
	UINTN ArrayCount;

	Status = gBS->ProtocolsPerHandle(ImageHandle,
			&ProtocolGuidArray,
			&ArrayCount);

	if (Status == EFI_SUCCESS) {
		for (int i=0; i<ArrayCount; i++) {
			Print(L"%g\n", ProtocolGuidArray[i]);
		}
		FreePool(ProtocolGuidArray);
	}


	return EFI_SUCCESS;
}
