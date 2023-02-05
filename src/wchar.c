#include <wchar.h>

wchar_t *lwcschr(const wchar_t *_s, wchar_t c) {
	wchar_t *s = (wchar_t *) _s;
	while (*s != '\0') {
		if (*s == c) return s;
		s++;
	}
	if (*s == c) return s;
	return NULL;
}

int lwcscmp(const wchar_t *s1, const wchar_t *s2) {
	while (*s1 != '\0' && *s2 != '\0') {
		if (*s1 < *s2) return -1;
		if (*s1 > *s2) return 1;
		s1++;
		s2++;
	}
	if (*s1 < *s2) return -1;
	if (*s1 > *s2) return 1;
	return 0;
}

size_t lwcslen(const wchar_t *s) {
	size_t length = 0;
	while (*s != '\0') {
		s++;
		length++;
	}
	return length;
}
