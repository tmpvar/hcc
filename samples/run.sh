#!/bin/sh

# Platform detection
OS="$(uname -s)"
case "${OS}" in
	Linux*)
		PLATFORM_LIBS="-lX11 -lvulkan"
		PLATFORM_LDFLAGS=""
		PLATFORM_CFLAGS=""
		PLATFORM_DEFINES="-D_GNU_SOURCE"
		;;
	Darwin*)
		PLATFORM_LIBS="-framework Cocoa -framework QuartzCore -lvulkan"
		PLATFORM_LDFLAGS="-L/opt/homebrew/lib -L/usr/local/lib"
		PLATFORM_CFLAGS="-I/opt/homebrew/include -I/usr/local/include"
		PLATFORM_DEFINES=""
		;;
	*)
		echo "Unsupported platform: ${OS}"
		exit 1
		;;
esac

ScriptDir="$(cd -- "$(dirname -- "$0")" && pwd)"

$ScriptDir/../build/hcc --enable-unordered-swizzling -O -fi $ScriptDir/shaders.c -fo $ScriptDir/shaders.spirv -fomc $ScriptDir/shaders-metadata.h && \
if [ "${OS}" = "Darwin" ]; then
	clang ${PLATFORM_CFLAGS} -xobjective-c ${PLATFORM_DEFINES} -I$ScriptDir/../libhmaths -I$ScriptDir/../libhccintrinsics -I$ScriptDir/../interop -lm -std=gnu11 -Wfloat-conversion -Wextra ${PLATFORM_LDFLAGS} ${PLATFORM_LIBS} -g -o $ScriptDir/samples $ScriptDir/app/main.c
else
	clang -pedantic ${PLATFORM_DEFINES} -I$ScriptDir/../libhmaths -I$ScriptDir/../libhccintrinsics -I$ScriptDir/../interop -lm -std=gnu11 -Werror -Wfloat-conversion -Wextra ${PLATFORM_LDFLAGS} ${PLATFORM_LIBS} -g -o $ScriptDir/samples $ScriptDir/app/main.c
fi

if [ $? -ne 0 ]; then
	exit
fi

$ScriptDir/samples

