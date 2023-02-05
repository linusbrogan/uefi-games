#include <efi.h>

unsigned int scanChar();
int scanDigit();
int scanNumber();
void scanString(CHAR16 *buffer);
UINT64 FileSize(EFI_FILE_HANDLE FileHandle);
EFI_FILE_HANDLE openFile(const CHAR16 *filename, UINTN mode);
