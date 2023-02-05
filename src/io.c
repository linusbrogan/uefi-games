#include <efi.h>
#include <efilib.h>
#include "efistub.h"
#include "io.h"

unsigned int scanChar() {
	EFI_STATUS Status = uefi_call_wrapper(ST->ConIn->Reset, 2, ST->ConIn, FALSE);
	if (EFI_ERROR(Status)) return 0;
	EFI_INPUT_KEY Key;
	while ((Status = uefi_call_wrapper(ST->ConIn->ReadKeyStroke, 2, ST->ConIn, &Key)) == EFI_NOT_READY);
	Print(L"%c", Key.UnicodeChar);
	return Key.UnicodeChar;
}

int scanDigit() {
	unsigned int c = scanChar();
	Print(L"\n");
	return c - '0';
}

int scanNumber() {
	char cr = '\r';
	char lf = '\n';
	char c = scanChar();
	int n = 0;
	while (c == ' ' || c == cr || c == lf) c = scanChar();
	while (c >= '0' && c <= '9') {
		n *= 10;
		n += c - '0';
		c = scanChar();
	}
	return n;
}

void scanString(CHAR16 *buffer) {
	char cr = '\r';
	char lf = '\n';
	char c = scanChar();
	while (c == ' ' || c == cr || c == lf) c = scanChar();
	while (c != cr && c != lf) {
		*buffer = c;
		buffer++;
		c = scanChar();
	}
	*buffer  = '\0';
}

UINT64 FileSize(EFI_FILE_HANDLE FileHandle) {
	EFI_FILE_INFO *FileInfo = LibFileInfo(FileHandle);
	UINT64 size = FileInfo->FileSize;
	FreePool(FileInfo);
	return size;
}

EFI_FILE_HANDLE GetVolume(EFI_HANDLE image) {
	EFI_LOADED_IMAGE *loadedImage = NULL;
	EFI_GUID lipGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
	EFI_FILE_IO_INTERFACE *IOVolume;
	EFI_GUID fsGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EFI_FILE_HANDLE Volume;
	uefi_call_wrapper(BS->HandleProtocol, 3, image, &lipGuid, (void **) &loadedImage);
	uefi_call_wrapper(BS->HandleProtocol, 3, loadedImage->DeviceHandle, &fsGuid, (void *) &IOVolume);
	uefi_call_wrapper(IOVolume->OpenVolume, 2, IOVolume, &Volume);
	return Volume;
}

EFI_FILE_HANDLE openFile(const CHAR16 *filename, UINT64 mode) {
	EFI_FILE_HANDLE Volume = GetVolume(IH);
	EFI_FILE_HANDLE FileHandle;
	EFI_STATUS status = uefi_call_wrapper(Volume->Open, 5, Volume, &FileHandle, filename, mode, 0);
	if (EFI_ERROR(status)) return NULL;
	return FileHandle;
}
