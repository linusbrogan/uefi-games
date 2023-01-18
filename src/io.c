#include <efi.h>
#include <efilib.h>

unsigned int readChar() {
	EFI_STATUS Status = uefi_call_wrapper(ST->ConIn->Reset, 2, ST->ConIn, FALSE);
	if (EFI_ERROR(Status)) return 0;
	EFI_INPUT_KEY Key;
	while ((Status = uefi_call_wrapper(ST->ConIn->ReadKeyStroke, 2, ST->ConIn, &Key)) == EFI_NOT_READY);
	return Key.UnicodeChar;
}

int readDigit() {
	unsigned int c = readChar();
	return c - '0';
}
