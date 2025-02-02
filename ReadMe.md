# Flipper Zero Firmware (Wetox fork, unofficial!)

![Show me the code](https://habrastorage.org/webt/eo/m0/e4/eom0e4btudte7nrhnyic-laiog0.png)

Welcome to the [Wetox Flipper Zero](https://wetox.team/)'s Firmware repo!
This is a modified unofficial version of the Flipper Zero firmware with some additional features.

# If you want to incorporate our features into your firmware fork, please contact us beforehand!

# Feature list

* Removing T5577 passwords via the cli command `rfid clear_pass_t5577` using a dictionary attack
* Support for inverted screens via a toggle in the desktop settings

# Clone the Repository

You should clone with 
```shell
$ git clone --recursive https://github.com/flipperdevices/flipperzero-firmware.git
```

# Update firmware

Flipper Zero's firmware consists of two components:

- Core2 firmware set - proprietary components by ST: FUS + radio stack. FUS is flashed at factory and you should never update it.
- Core1 Firmware - HAL + OS + Drivers + Applications.

They both must be flashed in the order described.

## With offline update package

With Flipper attached over USB:

`./fbt flash_usb`

Just building the package:

`./fbt updater_package`

To update, copy the resulting directory to Flipper's SD card and navigate to `update.fuf` file in Archive app. 

## With STLink

### Core1 Firmware

Prerequisites:

- Linux / macOS
- Terminal
- [arm-gcc-none-eabi](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
- openocd


One liner: `./fbt firmware_flash`


## With USB DFU 

1. Download latest [Firmware](https://github.com/wetox-team/flipperzero-firmware/releases)

2. Reboot Flipper to Bootloader
 - Press and hold `← Left` + `↩ Back` for reset 
 - Release `↩ Back` and keep holding `← Left` until blue LED lights up
 - Release `← Left`

3. Run `dfu-util -D full.dfu -a 0`

# Build with Docker

## Prerequisites

1. Install [Docker Engine and Docker Compose](https://www.docker.com/get-started)
2. Prepare the container:

 ```sh
 docker-compose up -d
 ```

## Compile everything

```sh
docker-compose exec dev ./fbt
```

Check `dist/` for build outputs.

Use **`flipper-z-{target}-full-{suffix}.dfu`** to flash your device.

If compilation fails, make sure all submodules are all initialized. Either clone with `--recursive` or use `git submodule update --init --recursive`.

# Build on Linux/macOS

Check out `documentation/fbt.md` for details on building and flashing firmware. 

## macOS Prerequisites

Make sure you have [brew](https://brew.sh) and install all the dependencies:
```sh
brew bundle --verbose
```

## Linux Prerequisites

### gcc-arm-none-eabi

```sh
toolchain="gcc-arm-none-eabi-10.3-2021.10"
toolchain_package="$toolchain-$(uname -m)-linux"

wget -P /opt "https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/$toolchain_package.tar.bz2"

tar xjf /opt/$toolchain_package.tar.bz2 -C /opt
rm /opt/$toolchain_package.tar.bz2

for file in /opt/$toolchain/bin/* ; do ln -s "${file}" "/usr/bin/$(basename ${file})" ; done
```

### Optional dependencies

- openocd (debugging/flashing over SWD)
- heatshrink (compiling image assets)
- clang-format (code formatting)
- dfu-util (flashing over USB DFU)
- protobuf (compiling proto sources)

For example, to install them on Debian, use:
```sh
apt update
apt install openocd clang-format-13 dfu-util protobuf-compiler
```

heatshrink has to be compiled [from sources](https://github.com/atomicobject/heatshrink).

## Compile everything

```sh
./fbt
```

Check `dist/` for build outputs.

Use **`flipper-z-{target}-full-{suffix}.dfu`** to flash your device.

## Flash everything

Connect your device via ST-Link and run:
```sh
./fbt firmware_flash
```
Or connect via the blackmagic board and run:
```sh
BLACKMAGIC=<board's IP>:2345 make blackmagic_load
```

# Links

* Telegram: [@wetox_flipper](https://t.me/wetox_flipper)

# Project structure

- `applications`    - Applications and services used in firmware
- `assets`          - Assets used by applications and services
- `furi`            - Furi Core: os level primitives and helpers
- `debug`           - Debug tool: GDB-plugins, SVD-file and etc
- `docker`          - Docker image sources (used for firmware build automation)
- `documentation`   - Documentation generation system configs and input files
- `firmware`        - Firmware source code
- `lib`             - Our and 3rd party libraries, drivers and etc...
- `scripts`         - Supplementary scripts and python libraries home

Also pay attention to `ReadMe.md` files inside of those directories.
