#include <efi.h>
#include <efilib.h>
#include "time.h"

time_t time(time_t *timer) {
	EFI_TIME Time;
	EFI_STATUS status = uefi_call_wrapper(ST->RuntimeServices->GetTime, 2, &Time, NULL);

	time_t timestamp = -1;
	if (!EFI_ERROR(status)) {
		timestamp = Time.Year;
		timestamp = (timestamp << sizeof(Time.Month)) | Time.Month;
		timestamp = (timestamp << sizeof(Time.Day)) | Time.Day;
		timestamp = (timestamp << sizeof(Time.Hour)) | Time.Hour;
		timestamp = (timestamp << sizeof(Time.Minute)) | Time.Minute;
		timestamp = (timestamp << sizeof(Time.Second)) | Time.Second;
	}

	if (timer != NULL) *timer = timestamp;
	return timestamp;
}
