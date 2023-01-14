#ifdef LB_EFI

#include <efi.h>
#include <efilib.h>

typedef CHAR16 LB_char_t;
#define LB_print(...) Print(__VA_ARGS__)
#define TEXT(text) (L##text)

extern int main();

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	main();
	return EFI_SUCCESS;
}

#else

#include <stdio.h>

typedef char LB_char_t;
#define LB_print(...) printf(__VA_ARGS__)
#define TEXT(text) (text)

#endif

LB_char_t LB_readChar() {
#ifdef LB_EFI
	EFI_STATUS Status = uefi_call_wrapper(ST->ConIn->Reset, 2, ST->ConIn, FALSE);
	if (EFI_ERROR(Status)) return 0;
	EFI_INPUT_KEY Key;
	while ((Status = uefi_call_wrapper(ST->ConIn->ReadKeyStroke, 2, ST->ConIn, &Key)) == EFI_NOT_READY);
	return Key.UnicodeChar;
#else
	char key = 0;
	scanf(" %c", &key);
	return key;
#endif
}

int LB_readDigit() {
	LB_char_t c = LB_readChar();
	return c - '0';
}
