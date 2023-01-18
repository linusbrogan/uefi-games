#include <efi.h>
#include <efilib.h>

int main();

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	main();
	return EFI_SUCCESS;
}
