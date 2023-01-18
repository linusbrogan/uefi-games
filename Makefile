CFLAGS = \
	-I/usr/include/efi \
	-fpic \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fshort-wchar \
	-mno-red-zone \
	-maccumulate-outgoing-args

LDFLAGS = \
	-shared \
	-Bsymbolic \
	-L/usr/lib \
	-T/usr/lib/elf_x86_64_efi.lds \
	/usr/lib/crt0-efi-x86_64.o \
	-lefi \
	-lgnuefi

OBJCOPYFLAGS = \
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
default: blackjack.efi tic_tac_toe.efi

%.o: src/%.c
	gcc $(CFLAGS) -c -o $@ $^

%.so: %.o rand.o time.o
	ld -o $@ $^ $(LDFLAGS)

%.efi: %.so
	objcopy $(OBJCOPYFLAGS) $^ $@

.PHONY: clean
clean:
	-rm *.o *.so *.efi
