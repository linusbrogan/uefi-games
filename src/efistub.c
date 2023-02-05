#include <efi.h>
#include <efilib.h>
#include "efistub.h"

int main();

EFI_HANDLE IH;

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	IH = ImageHandle;
	main();
	return EFI_SUCCESS;
}
