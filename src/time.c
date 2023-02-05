#include <efi.h>
#include <efilib.h>
#include "time.h"

UINT16 daysUntilMonth(UINT8 month) {
	if (month < 0 || month > 12) return -1;
	UINT16 cumulativeDays[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
	return cumulativeDays[month];
}

time_t time(time_t *timer) {
	EFI_TIME Time;
	EFI_STATUS status = uefi_call_wrapper(ST->RuntimeServices->GetTime, 2, &Time, NULL);

	time_t timestamp = -1;
	if (!EFI_ERROR(status)) {
		// Convert to the approximate Unix time.
		// It is not accurate, but it is good enough.
		timestamp = (Time.Year - 1970) * 365;
		timestamp += daysUntilMonth(Time.Month);
		timestamp += Time.Day - 1;
		timestamp = timestamp * 24 + Time.Hour;
		timestamp = timestamp * 60 + Time.Minute;
		timestamp = timestamp * 60 + Time.Second;
	}

	if (timer != NULL) *timer = timestamp;
	return timestamp;
}
