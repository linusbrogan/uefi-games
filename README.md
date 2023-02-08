# UEFI Games
I wrote these games for Windows years ago.
Here they are ported them to UEFI, so they do not need an operating system to run.
Older versions in tag [`linux-games`](https://github.com/linusbrogan/uefi-games/releases/tag/linux-games) run under Linux and can be built with `make`.

## Games
- Blackjack, at least mostly
- Hangman, the best of these four games
- RPG, a text-based adventure
- Tic-Tac-Toe, for two players

Download the games from the [latest release](https://github.com/linusbrogan/uefi-games/releases/latest).

## Dependencies
Building these games requires `gcc`, `gnu-efi`, and `make` to be installed.

## Running the games
These games run under UEFI on a x64 platform.
You may need to sign them with appropriate secure boot keys.

You could also run them in a virtual machine.
For example, use QEMU.
Install `qemu-system-x86`.
Load the games into a virtual hard drive file.
Then run `qemu-system-x86_64 -bios /usr/share/OVMF/OVMF_CODE.fd -hda [path to virtual hard drive] -nographic -net none`.
