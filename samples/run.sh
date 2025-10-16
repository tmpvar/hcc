#!/bin/sh

# Platform detection
OS="$(uname -s)"
case "${OS}" in
	Linux*)
		PLATFORM_LIBS="-lX11 -lvulkan"
		;;
	Darwin*)
		PLATFORM_LIBS="-framework Cocoa -framework QuartzCore -lvulkan"
		;;
	*)
		echo "Unsupported platform: ${OS}"
		exit 1
		;;
esac

../hcc -O -fi shaders.c -fo shaders.spirv -fomc shaders-metadata.h && \
if [ "${OS}" = "Darwin" ]; then
	clang -xobjective-c -D_GNU_SOURCE -I../libhmaths -I../libhccintrinsics -I../interop -lm -std=gnu11 -Wfloat-conversion -Wextra ${PLATFORM_LIBS} -g -o ./samples ./app/main.c
else
	clang -pedantic -D_GNU_SOURCE -I../libhmaths -I../libhccintrinsics -I../interop -lm -std=gnu11 -Werror -Wfloat-conversion -Wextra ${PLATFORM_LIBS} -g -o ./samples ./app/main.c
fi

if [ $? -ne 0 ]; then
	exit
fi

./samples

