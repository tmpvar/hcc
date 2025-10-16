#!/bin/sh
set -euo pipefail
set -x

# Platform detection
OS="$(uname -s)"
case "${OS}" in
	Linux*)
		PLATFORM_FLAGS="-ldl"
		PLATFORM_LIBS="-lX11 -lvulkan"
		;;
	Darwin*)
		PLATFORM_FLAGS=""
		PLATFORM_LIBS="-lvulkan"
		;;
	*)
		echo "Unsupported platform: ${OS}"
		exit 1
		;;
esac

FLAGS="-pedantic -Ilibhmaths -Ilibhccintrinsics -Iinterop -D_GNU_SOURCE -std=gnu11 -Werror -Wfloat-conversion -Wimplicit-fallthrough -Wextra -g -lm ${PLATFORM_FLAGS} -pthread -Wno-unused-parameter -Wno-gnu-pointer-arith -Wno-format"
if [ "${1-default}" = "release" ]; then
	FLAGS="$FLAGS -O2"
fi

mkdir -p build

cd build
ln -snf ../libc libc
ln -snf ../libhmaths libhmaths
ln -snf ../libhccintrinsics libhccintrinsics
cd ..\

clang $FLAGS -o build/hcc src/hcc_main.c && \
build/hcc -O -g -fi samples/shaders.c -fo samples/shaders.spirv -fomc samples/shaders-metadata.h --enable-unordered-swizzling

EXIT_CODE=$?
if [ $EXIT_CODE -ne 0 ]; then
	exit $EXIT_CODE
fi

if [ "${1}" = "release" ]; then
	echo "=========== Building Release Package ==========="
	cd build
	tar -cvzf "hcc-0.4.0-linux.tar.gz" hcc ../libc ../libhmaths ../libhccintrinsics ../interop ../samples ../playground ../docs ../README.md ../LICENSE
fi

