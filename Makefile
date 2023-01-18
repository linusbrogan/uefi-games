CFLAGS_EFI = \
	-I/usr/include/efi \
	-fpic \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fshort-wchar \
	-mno-red-zone \
	-maccumulate-outgoing-args \
	-c

LDFLAGS_EFI = \
	-shared \
	-Bsymbolic \
	-L/usr/lib \
	-T/usr/lib/elf_x86_64_efi.lds \
	/usr/lib/crt0-efi-x86_64.o \
	-lefi \
	-lgnuefi

OBJCOPYFLAGS_EFI = \
	-j .text \
	-j .sdata \
	-j .data \
	-j .dynamic \
	-j .dynsym \
	-j .rel \
	-j .rela \
	-j .rel.* \
	-j .rela.* \
	-j .reloc \
	--target efi-app-x86_64 \
	--subsystem=10

.PHONY: default
default: tic_tac_toe.efi

%.o: src/%.c
	gcc $(CFLAGS_EFI) -o $@ $^

%.so: %.o
	ld -o $@ $^ $(LDFLAGS_EFI)

%.efi: %.so
	objcopy $(OBJCOPYFLAGS_EFI) $^ $@

.PHONY: clean
clean:
	-rm *.o *.so *.efi
