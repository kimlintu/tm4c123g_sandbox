import sys

BOOTLOADER_FILE = sys.argv[1]
BOOTLOADER_SIZE = int(sys.argv[2], 16)

with open(BOOTLOADER_FILE, "rb") as boot_file:
    bootloader_data = boot_file.read()

bytes_to_pad = BOOTLOADER_SIZE - len(bootloader_data)
padding      = bytes([0xFF for _ in range(bytes_to_pad)])

print(f"padding {bytes_to_pad} bytes...")

with open(BOOTLOADER_FILE, "wb") as boot_file:
    boot_file.write(bootloader_data + padding)