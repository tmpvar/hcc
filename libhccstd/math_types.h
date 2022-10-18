// !?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!
// !?!?!? WARNING CONTRIBUTOR ?!?!?!
// !?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!
// this file is generated by tools/std_math_gen.c
// please edit that file and regenerate this one if you want to make edits

#ifndef _HCC_STD_MATH_TYPES_H_
#define _HCC_STD_MATH_TYPES_H_
#include "../libc-gpu/stdbool.h"
#include "../libc-gpu/stdint.h"

// ===========================================
//
//
// Libc Math extensions
//
//
// ===========================================

#define INFINITYF INFINITY
#define INFINITYD INFINITY
#define NEGINFINITYF (-INFINITY)
#define NEGINFINITYD (-INFINITY)
#define NANF NAN
#define NAND NAN

// ===========================================
//
//
// Half type aka. float 16 bit
//
//
// ===========================================

HCC_INTRINSIC typedef struct half { uint16_t _bits; } half;
#define ZEROH ((half){ _bits = 0; })
#define INFINITYH ((half){ _bits = 0x7c00; })
#define NEGINFINITYH ((half){ _bits = 0xfc00; })
#define NANH ((half){ _bits = 0xffff; })

// ===========================================
//
//
// Packed Vector
//
//
// ===========================================
//
// these packed vectors have alignment of their component type.
// they should only be used to transport vectors between CPU and GPU if the native alignment adds too much padding
//

HCC_INTRINSIC typedef struct pboolx2 { bool     x; bool     y; } pboolx2;
HCC_INTRINSIC typedef struct pf16x2 { half     x; half     y; } pf16x2;
HCC_INTRINSIC typedef struct pf32x2 { float    x; float    y; } pf32x2;
HCC_INTRINSIC typedef struct pf64x2 { double   x; double   y; } pf64x2;
HCC_INTRINSIC typedef struct ps8x2 { int8_t   x; int8_t   y; } ps8x2;
HCC_INTRINSIC typedef struct ps16x2 { int16_t  x; int16_t  y; } ps16x2;
HCC_INTRINSIC typedef struct ps32x2 { int32_t  x; int32_t  y; } ps32x2;
HCC_INTRINSIC typedef struct ps64x2 { int64_t  x; int64_t  y; } ps64x2;
HCC_INTRINSIC typedef struct pu8x2 { uint8_t  x; uint8_t  y; } pu8x2;
HCC_INTRINSIC typedef struct pu16x2 { uint16_t x; uint16_t y; } pu16x2;
HCC_INTRINSIC typedef struct pu32x2 { uint32_t x; uint32_t y; } pu32x2;
HCC_INTRINSIC typedef struct pu64x2 { uint64_t x; uint64_t y; } pu64x2;

HCC_INTRINSIC typedef struct pboolx3 { bool     x; bool     y; bool     z; } pboolx3;
HCC_INTRINSIC typedef struct pf16x3 { half     x; half     y; half     z; } pf16x3;
HCC_INTRINSIC typedef struct pf32x3 { float    x; float    y; float    z; } pf32x3;
HCC_INTRINSIC typedef struct pf64x3 { double   x; double   y; double   z; } pf64x3;
HCC_INTRINSIC typedef struct ps8x3 { int8_t   x; int8_t   y; int8_t   z; } ps8x3;
HCC_INTRINSIC typedef struct ps16x3 { int16_t  x; int16_t  y; int16_t  z; } ps16x3;
HCC_INTRINSIC typedef struct ps32x3 { int32_t  x; int32_t  y; int32_t  z; } ps32x3;
HCC_INTRINSIC typedef struct ps64x3 { int64_t  x; int64_t  y; int64_t  z; } ps64x3;
HCC_INTRINSIC typedef struct pu8x3 { uint8_t  x; uint8_t  y; uint8_t  z; } pu8x3;
HCC_INTRINSIC typedef struct pu16x3 { uint16_t x; uint16_t y; uint16_t z; } pu16x3;
HCC_INTRINSIC typedef struct pu32x3 { uint32_t x; uint32_t y; uint32_t z; } pu32x3;
HCC_INTRINSIC typedef struct pu64x3 { uint64_t x; uint64_t y; uint64_t z; } pu64x3;

HCC_INTRINSIC typedef struct pboolx4 { bool     x; bool     y; bool     z; bool     w; } pboolx4;
HCC_INTRINSIC typedef struct pf16x4 { half     x; half     y; half     z; half     w; } pf16x4;
HCC_INTRINSIC typedef struct pf32x4 { float    x; float    y; float    z; float    w; } pf32x4;
HCC_INTRINSIC typedef struct pf64x4 { double   x; double   y; double   z; double   w; } pf64x4;
HCC_INTRINSIC typedef struct ps8x4 { int8_t   x; int8_t   y; int8_t   z; int8_t   w; } ps8x4;
HCC_INTRINSIC typedef struct ps16x4 { int16_t  x; int16_t  y; int16_t  z; int16_t  w; } ps16x4;
HCC_INTRINSIC typedef struct ps32x4 { int32_t  x; int32_t  y; int32_t  z; int32_t  w; } ps32x4;
HCC_INTRINSIC typedef struct ps64x4 { int64_t  x; int64_t  y; int64_t  z; int64_t  w; } ps64x4;
HCC_INTRINSIC typedef struct pu8x4 { uint8_t  x; uint8_t  y; uint8_t  z; uint8_t  w; } pu8x4;
HCC_INTRINSIC typedef struct pu16x4 { uint16_t x; uint16_t y; uint16_t z; uint16_t w; } pu16x4;
HCC_INTRINSIC typedef struct pu32x4 { uint32_t x; uint32_t y; uint32_t z; uint32_t w; } pu32x4;
HCC_INTRINSIC typedef struct pu64x4 { uint64_t x; uint64_t y; uint64_t z; uint64_t w; } pu64x4;

//
// initializes a new _packed_ vector with 2, 3 or 4 components of any of the following types:
//	bool, half, float, double, uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, or int64_t
#define pboolx2(x, y) ((pboolx2){ x, y })
#define pf16x2(x, y) ((pf16x2){ x, y })
#define pf32x2(x, y) ((pf32x2){ x, y })
#define pf64x2(x, y) ((pf64x2){ x, y })
#define ps8x2(x, y) ((ps8x2){ x, y })
#define ps16x2(x, y) ((ps16x2){ x, y })
#define ps32x2(x, y) ((ps32x2){ x, y })
#define ps64x2(x, y) ((ps64x2){ x, y })
#define pu8x2(x, y) ((pu8x2){ x, y })
#define pu16x2(x, y) ((pu16x2){ x, y })
#define pu32x2(x, y) ((pu32x2){ x, y })
#define pu64x2(x, y) ((pu64x2){ x, y })
#define pboolx3(x, y, z) ((pboolx3){ x, y, z })
#define pf16x3(x, y, z) ((pf16x3){ x, y, z })
#define pf32x3(x, y, z) ((pf32x3){ x, y, z })
#define pf64x3(x, y, z) ((pf64x3){ x, y, z })
#define ps8x3(x, y, z) ((ps8x3){ x, y, z })
#define ps16x3(x, y, z) ((ps16x3){ x, y, z })
#define ps32x3(x, y, z) ((ps32x3){ x, y, z })
#define ps64x3(x, y, z) ((ps64x3){ x, y, z })
#define pu8x3(x, y, z) ((pu8x3){ x, y, z })
#define pu16x3(x, y, z) ((pu16x3){ x, y, z })
#define pu32x3(x, y, z) ((pu32x3){ x, y, z })
#define pu64x3(x, y, z) ((pu64x3){ x, y, z })
#define pboolx4(x, y, z, w) ((pboolx4){ x, y, z, w })
#define pf16x4(x, y, z, w) ((pf16x4){ x, y, z, w })
#define pf32x4(x, y, z, w) ((pf32x4){ x, y, z, w })
#define pf64x4(x, y, z, w) ((pf64x4){ x, y, z, w })
#define ps8x4(x, y, z, w) ((ps8x4){ x, y, z, w })
#define ps16x4(x, y, z, w) ((ps16x4){ x, y, z, w })
#define ps32x4(x, y, z, w) ((ps32x4){ x, y, z, w })
#define ps64x4(x, y, z, w) ((ps64x4){ x, y, z, w })
#define pu8x4(x, y, z, w) ((pu8x4){ x, y, z, w })
#define pu16x4(x, y, z, w) ((pu16x4){ x, y, z, w })
#define pu32x4(x, y, z, w) ((pu32x4){ x, y, z, w })
#define pu64x4(x, y, z, w) ((pu64x4){ x, y, z, w })

// ===========================================
//
//
// Vector
//
//
// ===========================================
//
// these vectors have native alignment where their alignment is the same as their size
// these vectors should be used when performing maths operations
// the vec3 is rounded up to the size and align of a vec4 due to hardware limitations
//

HCC_INTRINSIC typedef union boolx2 boolx2;
HCC_INTRINSIC typedef union f16x2 f16x2;
HCC_INTRINSIC typedef union f32x2 f32x2;
HCC_INTRINSIC typedef union f64x2 f64x2;
HCC_INTRINSIC typedef union s8x2 s8x2;
HCC_INTRINSIC typedef union s16x2 s16x2;
HCC_INTRINSIC typedef union s32x2 s32x2;
HCC_INTRINSIC typedef union s64x2 s64x2;
HCC_INTRINSIC typedef union u8x2 u8x2;
HCC_INTRINSIC typedef union u16x2 u16x2;
HCC_INTRINSIC typedef union u32x2 u32x2;
HCC_INTRINSIC typedef union u64x2 u64x2;

HCC_INTRINSIC typedef union boolx3 boolx3;
HCC_INTRINSIC typedef union f16x3 f16x3;
HCC_INTRINSIC typedef union f32x3 f32x3;
HCC_INTRINSIC typedef union f64x3 f64x3;
HCC_INTRINSIC typedef union s8x3 s8x3;
HCC_INTRINSIC typedef union s16x3 s16x3;
HCC_INTRINSIC typedef union s32x3 s32x3;
HCC_INTRINSIC typedef union s64x3 s64x3;
HCC_INTRINSIC typedef union u8x3 u8x3;
HCC_INTRINSIC typedef union u16x3 u16x3;
HCC_INTRINSIC typedef union u32x3 u32x3;
HCC_INTRINSIC typedef union u64x3 u64x3;

HCC_INTRINSIC typedef union boolx4 boolx4;
HCC_INTRINSIC typedef union f16x4 f16x4;
HCC_INTRINSIC typedef union f32x4 f32x4;
HCC_INTRINSIC typedef union f64x4 f64x4;
HCC_INTRINSIC typedef union s8x4 s8x4;
HCC_INTRINSIC typedef union s16x4 s16x4;
HCC_INTRINSIC typedef union s32x4 s32x4;
HCC_INTRINSIC typedef union s64x4 s64x4;
HCC_INTRINSIC typedef union u8x4 u8x4;
HCC_INTRINSIC typedef union u16x4 u16x4;
HCC_INTRINSIC typedef union u32x4 u32x4;
HCC_INTRINSIC typedef union u64x4 u64x4;

HCC_INTRINSIC union boolx2 {
	_Alignas(2)
	struct { bool x; bool y; };
	struct { bool r; bool g; };
	struct { bool width; bool height; };
	bool array[2];
};

HCC_INTRINSIC union f16x2 {
	_Alignas(4)
	struct { half x; half y; };
	struct { half r; half g; };
	struct { half width; half height; };
	half array[2];
};

HCC_INTRINSIC union f32x2 {
	_Alignas(8)
	struct { float x; float y; };
	struct { float r; float g; };
	struct { float width; float height; };
	float array[2];
};

HCC_INTRINSIC union f64x2 {
	_Alignas(16)
	struct { double x; double y; };
	struct { double r; double g; };
	struct { double width; double height; };
	double array[2];
};

HCC_INTRINSIC union s8x2 {
	_Alignas(2)
	struct { int8_t x; int8_t y; };
	struct { int8_t r; int8_t g; };
	struct { int8_t width; int8_t height; };
	int8_t array[2];
};

HCC_INTRINSIC union s16x2 {
	_Alignas(4)
	struct { int16_t x; int16_t y; };
	struct { int16_t r; int16_t g; };
	struct { int16_t width; int16_t height; };
	int16_t array[2];
};

HCC_INTRINSIC union s32x2 {
	_Alignas(8)
	struct { int32_t x; int32_t y; };
	struct { int32_t r; int32_t g; };
	struct { int32_t width; int32_t height; };
	int32_t array[2];
};

HCC_INTRINSIC union s64x2 {
	_Alignas(16)
	struct { int64_t x; int64_t y; };
	struct { int64_t r; int64_t g; };
	struct { int64_t width; int64_t height; };
	int64_t array[2];
};

HCC_INTRINSIC union u8x2 {
	_Alignas(2)
	struct { uint8_t x; uint8_t y; };
	struct { uint8_t r; uint8_t g; };
	struct { uint8_t width; uint8_t height; };
	uint8_t array[2];
};

HCC_INTRINSIC union u16x2 {
	_Alignas(4)
	struct { uint16_t x; uint16_t y; };
	struct { uint16_t r; uint16_t g; };
	struct { uint16_t width; uint16_t height; };
	uint16_t array[2];
};

HCC_INTRINSIC union u32x2 {
	_Alignas(8)
	struct { uint32_t x; uint32_t y; };
	struct { uint32_t r; uint32_t g; };
	struct { uint32_t width; uint32_t height; };
	uint32_t array[2];
};

HCC_INTRINSIC union u64x2 {
	_Alignas(16)
	struct { uint64_t x; uint64_t y; };
	struct { uint64_t r; uint64_t g; };
	struct { uint64_t width; uint64_t height; };
	uint64_t array[2];
};

HCC_INTRINSIC union boolx3 {
	_Alignas(4)
	struct { bool x; bool y; bool z; bool _w; };
	struct { bool r; bool g; bool b; bool _a; };
	boolx2 xy;
	boolx2 rg;
	bool array[4];
};

HCC_INTRINSIC union f16x3 {
	_Alignas(8)
	struct { half x; half y; half z; half _w; };
	struct { half r; half g; half b; half _a; };
	f16x2 xy;
	f16x2 rg;
	half array[4];
};

HCC_INTRINSIC union f32x3 {
	_Alignas(16)
	struct { float x; float y; float z; float _w; };
	struct { float r; float g; float b; float _a; };
	f32x2 xy;
	f32x2 rg;
	float array[4];
};

HCC_INTRINSIC union f64x3 {
	_Alignas(32)
	struct { double x; double y; double z; double _w; };
	struct { double r; double g; double b; double _a; };
	f64x2 xy;
	f64x2 rg;
	double array[4];
};

HCC_INTRINSIC union s8x3 {
	_Alignas(4)
	struct { int8_t x; int8_t y; int8_t z; int8_t _w; };
	struct { int8_t r; int8_t g; int8_t b; int8_t _a; };
	s8x2 xy;
	s8x2 rg;
	int8_t array[4];
};

HCC_INTRINSIC union s16x3 {
	_Alignas(8)
	struct { int16_t x; int16_t y; int16_t z; int16_t _w; };
	struct { int16_t r; int16_t g; int16_t b; int16_t _a; };
	s16x2 xy;
	s16x2 rg;
	int16_t array[4];
};

HCC_INTRINSIC union s32x3 {
	_Alignas(16)
	struct { int32_t x; int32_t y; int32_t z; int32_t _w; };
	struct { int32_t r; int32_t g; int32_t b; int32_t _a; };
	s32x2 xy;
	s32x2 rg;
	int32_t array[4];
};

HCC_INTRINSIC union s64x3 {
	_Alignas(32)
	struct { int64_t x; int64_t y; int64_t z; int64_t _w; };
	struct { int64_t r; int64_t g; int64_t b; int64_t _a; };
	s64x2 xy;
	s64x2 rg;
	int64_t array[4];
};

HCC_INTRINSIC union u8x3 {
	_Alignas(4)
	struct { uint8_t x; uint8_t y; uint8_t z; uint8_t _w; };
	struct { uint8_t r; uint8_t g; uint8_t b; uint8_t _a; };
	u8x2 xy;
	u8x2 rg;
	uint8_t array[4];
};

HCC_INTRINSIC union u16x3 {
	_Alignas(8)
	struct { uint16_t x; uint16_t y; uint16_t z; uint16_t _w; };
	struct { uint16_t r; uint16_t g; uint16_t b; uint16_t _a; };
	u16x2 xy;
	u16x2 rg;
	uint16_t array[4];
};

HCC_INTRINSIC union u32x3 {
	_Alignas(16)
	struct { uint32_t x; uint32_t y; uint32_t z; uint32_t _w; };
	struct { uint32_t r; uint32_t g; uint32_t b; uint32_t _a; };
	u32x2 xy;
	u32x2 rg;
	uint32_t array[4];
};

HCC_INTRINSIC union u64x3 {
	_Alignas(32)
	struct { uint64_t x; uint64_t y; uint64_t z; uint64_t _w; };
	struct { uint64_t r; uint64_t g; uint64_t b; uint64_t _a; };
	u64x2 xy;
	u64x2 rg;
	uint64_t array[4];
};

HCC_INTRINSIC union boolx4 {
	_Alignas(4)
	struct { bool x; bool y; bool z; bool w; };
	struct { bool r; bool g; bool b; bool a; };
	struct { boolx2 top_left; boolx2 bottom_right; };
	struct { boolx2 bottom_left; boolx2 top_right; };
	struct { boolx2 xy; boolx2 zw; };
	struct { boolx2 rg; boolx2 ba; };
	struct { bool _; bool __; bool width; bool height; };
	boolx3 xyz;
	boolx3 rgb;
	bool array[4];
};
HCC_INTRINSIC union f16x4 {
	_Alignas(8)
	struct { half x; half y; half z; half w; };
	struct { half r; half g; half b; half a; };
	struct { f16x2 top_left; f16x2 bottom_right; };
	struct { f16x2 bottom_left; f16x2 top_right; };
	struct { f16x2 xy; f16x2 zw; };
	struct { f16x2 rg; f16x2 ba; };
	struct { half _; half __; half width; half height; };
	f16x3 xyz;
	f16x3 rgb;
	half array[4];
};
HCC_INTRINSIC union f32x4 {
	_Alignas(16)
	struct { float x; float y; float z; float w; };
	struct { float r; float g; float b; float a; };
	struct { f32x2 top_left; f32x2 bottom_right; };
	struct { f32x2 bottom_left; f32x2 top_right; };
	struct { f32x2 xy; f32x2 zw; };
	struct { f32x2 rg; f32x2 ba; };
	struct { float _; float __; float width; float height; };
	f32x3 xyz;
	f32x3 rgb;
	float array[4];
};
HCC_INTRINSIC union f64x4 {
	_Alignas(32)
	struct { double x; double y; double z; double w; };
	struct { double r; double g; double b; double a; };
	struct { f64x2 top_left; f64x2 bottom_right; };
	struct { f64x2 bottom_left; f64x2 top_right; };
	struct { f64x2 xy; f64x2 zw; };
	struct { f64x2 rg; f64x2 ba; };
	struct { double _; double __; double width; double height; };
	f64x3 xyz;
	f64x3 rgb;
	double array[4];
};
HCC_INTRINSIC union s8x4 {
	_Alignas(4)
	struct { int8_t x; int8_t y; int8_t z; int8_t w; };
	struct { int8_t r; int8_t g; int8_t b; int8_t a; };
	struct { s8x2 top_left; s8x2 bottom_right; };
	struct { s8x2 bottom_left; s8x2 top_right; };
	struct { s8x2 xy; s8x2 zw; };
	struct { s8x2 rg; s8x2 ba; };
	struct { int8_t _; int8_t __; int8_t width; int8_t height; };
	s8x3 xyz;
	s8x3 rgb;
	int8_t array[4];
};
HCC_INTRINSIC union s16x4 {
	_Alignas(8)
	struct { int16_t x; int16_t y; int16_t z; int16_t w; };
	struct { int16_t r; int16_t g; int16_t b; int16_t a; };
	struct { s16x2 top_left; s16x2 bottom_right; };
	struct { s16x2 bottom_left; s16x2 top_right; };
	struct { s16x2 xy; s16x2 zw; };
	struct { s16x2 rg; s16x2 ba; };
	struct { int16_t _; int16_t __; int16_t width; int16_t height; };
	s16x3 xyz;
	s16x3 rgb;
	int16_t array[4];
};
HCC_INTRINSIC union s32x4 {
	_Alignas(16)
	struct { int32_t x; int32_t y; int32_t z; int32_t w; };
	struct { int32_t r; int32_t g; int32_t b; int32_t a; };
	struct { s32x2 top_left; s32x2 bottom_right; };
	struct { s32x2 bottom_left; s32x2 top_right; };
	struct { s32x2 xy; s32x2 zw; };
	struct { s32x2 rg; s32x2 ba; };
	struct { int32_t _; int32_t __; int32_t width; int32_t height; };
	s32x3 xyz;
	s32x3 rgb;
	int32_t array[4];
};
HCC_INTRINSIC union s64x4 {
	_Alignas(32)
	struct { int64_t x; int64_t y; int64_t z; int64_t w; };
	struct { int64_t r; int64_t g; int64_t b; int64_t a; };
	struct { s64x2 top_left; s64x2 bottom_right; };
	struct { s64x2 bottom_left; s64x2 top_right; };
	struct { s64x2 xy; s64x2 zw; };
	struct { s64x2 rg; s64x2 ba; };
	struct { int64_t _; int64_t __; int64_t width; int64_t height; };
	s64x3 xyz;
	s64x3 rgb;
	int64_t array[4];
};
HCC_INTRINSIC union u8x4 {
	_Alignas(4)
	struct { uint8_t x; uint8_t y; uint8_t z; uint8_t w; };
	struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; };
	struct { u8x2 top_left; u8x2 bottom_right; };
	struct { u8x2 bottom_left; u8x2 top_right; };
	struct { u8x2 xy; u8x2 zw; };
	struct { u8x2 rg; u8x2 ba; };
	struct { uint8_t _; uint8_t __; uint8_t width; uint8_t height; };
	u8x3 xyz;
	u8x3 rgb;
	uint8_t array[4];
};
HCC_INTRINSIC union u16x4 {
	_Alignas(8)
	struct { uint16_t x; uint16_t y; uint16_t z; uint16_t w; };
	struct { uint16_t r; uint16_t g; uint16_t b; uint16_t a; };
	struct { u16x2 top_left; u16x2 bottom_right; };
	struct { u16x2 bottom_left; u16x2 top_right; };
	struct { u16x2 xy; u16x2 zw; };
	struct { u16x2 rg; u16x2 ba; };
	struct { uint16_t _; uint16_t __; uint16_t width; uint16_t height; };
	u16x3 xyz;
	u16x3 rgb;
	uint16_t array[4];
};
HCC_INTRINSIC union u32x4 {
	_Alignas(16)
	struct { uint32_t x; uint32_t y; uint32_t z; uint32_t w; };
	struct { uint32_t r; uint32_t g; uint32_t b; uint32_t a; };
	struct { u32x2 top_left; u32x2 bottom_right; };
	struct { u32x2 bottom_left; u32x2 top_right; };
	struct { u32x2 xy; u32x2 zw; };
	struct { u32x2 rg; u32x2 ba; };
	struct { uint32_t _; uint32_t __; uint32_t width; uint32_t height; };
	u32x3 xyz;
	u32x3 rgb;
	uint32_t array[4];
};
HCC_INTRINSIC union u64x4 {
	_Alignas(32)
	struct { uint64_t x; uint64_t y; uint64_t z; uint64_t w; };
	struct { uint64_t r; uint64_t g; uint64_t b; uint64_t a; };
	struct { u64x2 top_left; u64x2 bottom_right; };
	struct { u64x2 bottom_left; u64x2 top_right; };
	struct { u64x2 xy; u64x2 zw; };
	struct { u64x2 rg; u64x2 ba; };
	struct { uint64_t _; uint64_t __; uint64_t width; uint64_t height; };
	u64x3 xyz;
	u64x3 rgb;
	uint64_t array[4];
};

//
// initializes a new vector with 2, 3 or 4 components of any of the following types:
//	bool, half, float, double, uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, or int64_t
#define boolx2(x, y) ((boolx2){ { x, y } })
#define boolx2s(s) ((boolx2){ { s, s } })
#define f16x2(x, y) ((f16x2){ { x, y } })
#define f16x2s(s) ((f16x2){ { s, s } })
#define f32x2(x, y) ((f32x2){ { x, y } })
#define f32x2s(s) ((f32x2){ { s, s } })
#define f64x2(x, y) ((f64x2){ { x, y } })
#define f64x2s(s) ((f64x2){ { s, s } })
#define s8x2(x, y) ((s8x2){ { x, y } })
#define s8x2s(s) ((s8x2){ { s, s } })
#define s16x2(x, y) ((s16x2){ { x, y } })
#define s16x2s(s) ((s16x2){ { s, s } })
#define s32x2(x, y) ((s32x2){ { x, y } })
#define s32x2s(s) ((s32x2){ { s, s } })
#define s64x2(x, y) ((s64x2){ { x, y } })
#define s64x2s(s) ((s64x2){ { s, s } })
#define u8x2(x, y) ((u8x2){ { x, y } })
#define u8x2s(s) ((u8x2){ { s, s } })
#define u16x2(x, y) ((u16x2){ { x, y } })
#define u16x2s(s) ((u16x2){ { s, s } })
#define u32x2(x, y) ((u32x2){ { x, y } })
#define u32x2s(s) ((u32x2){ { s, s } })
#define u64x2(x, y) ((u64x2){ { x, y } })
#define u64x2s(s) ((u64x2){ { s, s } })

#define boolx3(x, y, z) ((boolx3){ { x, y, z } })
#define boolx3s(s) ((boolx3){ { s, s, s } })
#define boolx3sv2(x, v) ((boolx3){ { x, (v).x, (v).y } })
#define boolx3v2s(v, z) ((boolx3){ { (v).x, (v).y, z } })
#define f16x3(x, y, z) ((f16x3){ { x, y, z } })
#define f16x3s(s) ((f16x3){ { s, s, s } })
#define f16x3sv2(x, v) ((f16x3){ { x, (v).x, (v).y } })
#define f16x3v2s(v, z) ((f16x3){ { (v).x, (v).y, z } })
#define f32x3(x, y, z) ((f32x3){ { x, y, z } })
#define f32x3s(s) ((f32x3){ { s, s, s } })
#define f32x3sv2(x, v) ((f32x3){ { x, (v).x, (v).y } })
#define f32x3v2s(v, z) ((f32x3){ { (v).x, (v).y, z } })
#define f64x3(x, y, z) ((f64x3){ { x, y, z } })
#define f64x3s(s) ((f64x3){ { s, s, s } })
#define f64x3sv2(x, v) ((f64x3){ { x, (v).x, (v).y } })
#define f64x3v2s(v, z) ((f64x3){ { (v).x, (v).y, z } })
#define s8x3(x, y, z) ((s8x3){ { x, y, z } })
#define s8x3s(s) ((s8x3){ { s, s, s } })
#define s8x3sv2(x, v) ((s8x3){ { x, (v).x, (v).y } })
#define s8x3v2s(v, z) ((s8x3){ { (v).x, (v).y, z } })
#define s16x3(x, y, z) ((s16x3){ { x, y, z } })
#define s16x3s(s) ((s16x3){ { s, s, s } })
#define s16x3sv2(x, v) ((s16x3){ { x, (v).x, (v).y } })
#define s16x3v2s(v, z) ((s16x3){ { (v).x, (v).y, z } })
#define s32x3(x, y, z) ((s32x3){ { x, y, z } })
#define s32x3s(s) ((s32x3){ { s, s, s } })
#define s32x3sv2(x, v) ((s32x3){ { x, (v).x, (v).y } })
#define s32x3v2s(v, z) ((s32x3){ { (v).x, (v).y, z } })
#define s64x3(x, y, z) ((s64x3){ { x, y, z } })
#define s64x3s(s) ((s64x3){ { s, s, s } })
#define s64x3sv2(x, v) ((s64x3){ { x, (v).x, (v).y } })
#define s64x3v2s(v, z) ((s64x3){ { (v).x, (v).y, z } })
#define u8x3(x, y, z) ((u8x3){ { x, y, z } })
#define u8x3s(s) ((u8x3){ { s, s, s } })
#define u8x3sv2(x, v) ((u8x3){ { x, (v).x, (v).y } })
#define u8x3v2s(v, z) ((u8x3){ { (v).x, (v).y, z } })
#define u16x3(x, y, z) ((u16x3){ { x, y, z } })
#define u16x3s(s) ((u16x3){ { s, s, s } })
#define u16x3sv2(x, v) ((u16x3){ { x, (v).x, (v).y } })
#define u16x3v2s(v, z) ((u16x3){ { (v).x, (v).y, z } })
#define u32x3(x, y, z) ((u32x3){ { x, y, z } })
#define u32x3s(s) ((u32x3){ { s, s, s } })
#define u32x3sv2(x, v) ((u32x3){ { x, (v).x, (v).y } })
#define u32x3v2s(v, z) ((u32x3){ { (v).x, (v).y, z } })
#define u64x3(x, y, z) ((u64x3){ { x, y, z } })
#define u64x3s(s) ((u64x3){ { s, s, s } })
#define u64x3sv2(x, v) ((u64x3){ { x, (v).x, (v).y } })
#define u64x3v2s(v, z) ((u64x3){ { (v).x, (v).y, z } })

#define boolx4(x, y, z, w) ((boolx4){ { x, y, z, w } })
#define boolx4s(s) ((boolx4){ { s, s, s, s } })
#define boolx4sv2(x, y, v) ((boolx4){ { x, y, (v).x, (v).y } })
#define boolx4v2s(v, z, w) ((boolx4){ { (v).x, (v).y, z, w } })
#define boolx4sv2s(x, v, w) ((boolx4){ { x, (v).x, (v).y, w } })
#define boolx4sv3(x, v) ((boolx4){ { x, (v).x, (v).y, (v).z } })
#define boolx4v3s(v, w) ((boolx4){ { (v).x, (v).y, (v).z, w } })
#define f16x4(x, y, z, w) ((f16x4){ { x, y, z, w } })
#define f16x4s(s) ((f16x4){ { s, s, s, s } })
#define f16x4sv2(x, y, v) ((f16x4){ { x, y, (v).x, (v).y } })
#define f16x4v2s(v, z, w) ((f16x4){ { (v).x, (v).y, z, w } })
#define f16x4sv2s(x, v, w) ((f16x4){ { x, (v).x, (v).y, w } })
#define f16x4sv3(x, v) ((f16x4){ { x, (v).x, (v).y, (v).z } })
#define f16x4v3s(v, w) ((f16x4){ { (v).x, (v).y, (v).z, w } })
#define f32x4(x, y, z, w) ((f32x4){ { x, y, z, w } })
#define f32x4s(s) ((f32x4){ { s, s, s, s } })
#define f32x4sv2(x, y, v) ((f32x4){ { x, y, (v).x, (v).y } })
#define f32x4v2s(v, z, w) ((f32x4){ { (v).x, (v).y, z, w } })
#define f32x4sv2s(x, v, w) ((f32x4){ { x, (v).x, (v).y, w } })
#define f32x4sv3(x, v) ((f32x4){ { x, (v).x, (v).y, (v).z } })
#define f32x4v3s(v, w) ((f32x4){ { (v).x, (v).y, (v).z, w } })
#define f64x4(x, y, z, w) ((f64x4){ { x, y, z, w } })
#define f64x4s(s) ((f64x4){ { s, s, s, s } })
#define f64x4sv2(x, y, v) ((f64x4){ { x, y, (v).x, (v).y } })
#define f64x4v2s(v, z, w) ((f64x4){ { (v).x, (v).y, z, w } })
#define f64x4sv2s(x, v, w) ((f64x4){ { x, (v).x, (v).y, w } })
#define f64x4sv3(x, v) ((f64x4){ { x, (v).x, (v).y, (v).z } })
#define f64x4v3s(v, w) ((f64x4){ { (v).x, (v).y, (v).z, w } })
#define s8x4(x, y, z, w) ((s8x4){ { x, y, z, w } })
#define s8x4s(s) ((s8x4){ { s, s, s, s } })
#define s8x4sv2(x, y, v) ((s8x4){ { x, y, (v).x, (v).y } })
#define s8x4v2s(v, z, w) ((s8x4){ { (v).x, (v).y, z, w } })
#define s8x4sv2s(x, v, w) ((s8x4){ { x, (v).x, (v).y, w } })
#define s8x4sv3(x, v) ((s8x4){ { x, (v).x, (v).y, (v).z } })
#define s8x4v3s(v, w) ((s8x4){ { (v).x, (v).y, (v).z, w } })
#define s16x4(x, y, z, w) ((s16x4){ { x, y, z, w } })
#define s16x4s(s) ((s16x4){ { s, s, s, s } })
#define s16x4sv2(x, y, v) ((s16x4){ { x, y, (v).x, (v).y } })
#define s16x4v2s(v, z, w) ((s16x4){ { (v).x, (v).y, z, w } })
#define s16x4sv2s(x, v, w) ((s16x4){ { x, (v).x, (v).y, w } })
#define s16x4sv3(x, v) ((s16x4){ { x, (v).x, (v).y, (v).z } })
#define s16x4v3s(v, w) ((s16x4){ { (v).x, (v).y, (v).z, w } })
#define s32x4(x, y, z, w) ((s32x4){ { x, y, z, w } })
#define s32x4s(s) ((s32x4){ { s, s, s, s } })
#define s32x4sv2(x, y, v) ((s32x4){ { x, y, (v).x, (v).y } })
#define s32x4v2s(v, z, w) ((s32x4){ { (v).x, (v).y, z, w } })
#define s32x4sv2s(x, v, w) ((s32x4){ { x, (v).x, (v).y, w } })
#define s32x4sv3(x, v) ((s32x4){ { x, (v).x, (v).y, (v).z } })
#define s32x4v3s(v, w) ((s32x4){ { (v).x, (v).y, (v).z, w } })
#define s64x4(x, y, z, w) ((s64x4){ { x, y, z, w } })
#define s64x4s(s) ((s64x4){ { s, s, s, s } })
#define s64x4sv2(x, y, v) ((s64x4){ { x, y, (v).x, (v).y } })
#define s64x4v2s(v, z, w) ((s64x4){ { (v).x, (v).y, z, w } })
#define s64x4sv2s(x, v, w) ((s64x4){ { x, (v).x, (v).y, w } })
#define s64x4sv3(x, v) ((s64x4){ { x, (v).x, (v).y, (v).z } })
#define s64x4v3s(v, w) ((s64x4){ { (v).x, (v).y, (v).z, w } })
#define u8x4(x, y, z, w) ((u8x4){ { x, y, z, w } })
#define u8x4s(s) ((u8x4){ { s, s, s, s } })
#define u8x4sv2(x, y, v) ((u8x4){ { x, y, (v).x, (v).y } })
#define u8x4v2s(v, z, w) ((u8x4){ { (v).x, (v).y, z, w } })
#define u8x4sv2s(x, v, w) ((u8x4){ { x, (v).x, (v).y, w } })
#define u8x4sv3(x, v) ((u8x4){ { x, (v).x, (v).y, (v).z } })
#define u8x4v3s(v, w) ((u8x4){ { (v).x, (v).y, (v).z, w } })
#define u16x4(x, y, z, w) ((u16x4){ { x, y, z, w } })
#define u16x4s(s) ((u16x4){ { s, s, s, s } })
#define u16x4sv2(x, y, v) ((u16x4){ { x, y, (v).x, (v).y } })
#define u16x4v2s(v, z, w) ((u16x4){ { (v).x, (v).y, z, w } })
#define u16x4sv2s(x, v, w) ((u16x4){ { x, (v).x, (v).y, w } })
#define u16x4sv3(x, v) ((u16x4){ { x, (v).x, (v).y, (v).z } })
#define u16x4v3s(v, w) ((u16x4){ { (v).x, (v).y, (v).z, w } })
#define u32x4(x, y, z, w) ((u32x4){ { x, y, z, w } })
#define u32x4s(s) ((u32x4){ { s, s, s, s } })
#define u32x4sv2(x, y, v) ((u32x4){ { x, y, (v).x, (v).y } })
#define u32x4v2s(v, z, w) ((u32x4){ { (v).x, (v).y, z, w } })
#define u32x4sv2s(x, v, w) ((u32x4){ { x, (v).x, (v).y, w } })
#define u32x4sv3(x, v) ((u32x4){ { x, (v).x, (v).y, (v).z } })
#define u32x4v3s(v, w) ((u32x4){ { (v).x, (v).y, (v).z, w } })
#define u64x4(x, y, z, w) ((u64x4){ { x, y, z, w } })
#define u64x4s(s) ((u64x4){ { s, s, s, s } })
#define u64x4sv2(x, y, v) ((u64x4){ { x, y, (v).x, (v).y } })
#define u64x4v2s(v, z, w) ((u64x4){ { (v).x, (v).y, z, w } })
#define u64x4sv2s(x, v, w) ((u64x4){ { x, (v).x, (v).y, w } })
#define u64x4sv3(x, v) ((u64x4){ { x, (v).x, (v).y, (v).z } })
#define u64x4v3s(v, w) ((u64x4){ { (v).x, (v).y, (v).z, w } })

#define ZEROF16X2   ((f16x2){0})
#define ZEROF32X2   ((f32x2){0})
#define ZEROF64X2   ((f64x2){0})
#define ZEROS8X2   ((s8x2){0})
#define ZEROS16X2   ((s16x2){0})
#define ZEROS32X2   ((s32x2){0})
#define ZEROS64X2   ((s64x2){0})
#define ZEROU8X2   ((u8x2){0})
#define ZEROU16X2   ((u16x2){0})
#define ZEROU32X2   ((u32x2){0})
#define ZEROU64X2   ((u64x2){0})
#define ZEROF16X3   ((f16x3){0})
#define ZEROF32X3   ((f32x3){0})
#define ZEROF64X3   ((f64x3){0})
#define ZEROS8X3   ((s8x3){0})
#define ZEROS16X3   ((s16x3){0})
#define ZEROS32X3   ((s32x3){0})
#define ZEROS64X3   ((s64x3){0})
#define ZEROU8X3   ((u8x3){0})
#define ZEROU16X3   ((u16x3){0})
#define ZEROU32X3   ((u32x3){0})
#define ZEROU64X3   ((u64x3){0})
#define ZEROF16X4   ((f16x4){0})
#define ZEROF32X4   ((f32x4){0})
#define ZEROF64X4   ((f64x4){0})
#define ZEROS8X4   ((s8x4){0})
#define ZEROS16X4   ((s16x4){0})
#define ZEROS32X4   ((s32x4){0})
#define ZEROS64X4   ((s64x4){0})
#define ZEROU8X4   ((u8x4){0})
#define ZEROU16X4   ((u16x4){0})
#define ZEROU32X4   ((u32x4){0})
#define ZEROU64X4   ((u64x4){0})

#define INFINITYF16X2 f16x2(INFINITYF16, INFINITYF16)
#define INFINITYF32X2 f32x2(INFINITYF32, INFINITYF32)
#define INFINITYF64X2 f64x2(INFINITYF64, INFINITYF64)
#define INFINITYF16X3 f16x3(INFINITYF16, INFINITYF16, INFINITYF16)
#define INFINITYF32X3 f32x3(INFINITYF32, INFINITYF32, INFINITYF32)
#define INFINITYF64X3 f64x3(INFINITYF64, INFINITYF64, INFINITYF64)
#define INFINITYF16X4 f16x4(INFINITYF16, INFINITYF16, INFINITYF16, INFINITYF16)
#define INFINITYF32X4 f32x4(INFINITYF32, INFINITYF32, INFINITYF32, INFINITYF32)
#define INFINITYF64X4 f64x4(INFINITYF64, INFINITYF64, INFINITYF64, INFINITYF64)

#define NEGINFINITYF16X2 f16x2(NEGINFINITYF16, NEGINFINITYF16)
#define NEGINFINITYF32X2 f32x2(NEGINFINITYF32, NEGINFINITYF32)
#define NEGINFINITYF64X2 f64x2(NEGINFINITYF64, NEGINFINITYF64)
#define NEGINFINITYF16X3 f16x3(NEGINFINITYF16, NEGINFINITYF16, NEGINFINITYF16)
#define NEGINFINITYF32X3 f32x3(NEGINFINITYF32, NEGINFINITYF32, NEGINFINITYF32)
#define NEGINFINITYF64X3 f64x3(NEGINFINITYF64, NEGINFINITYF64, NEGINFINITYF64)
#define NEGINFINITYF16X4 f16x4(NEGINFINITYF16, NEGINFINITYF16, NEGINFINITYF16, NEGINFINITYF16)
#define NEGINFINITYF32X4 f32x4(NEGINFINITYF32, NEGINFINITYF32, NEGINFINITYF32, NEGINFINITYF32)
#define NEGINFINITYF64X4 f64x4(NEGINFINITYF64, NEGINFINITYF64, NEGINFINITYF64, NEGINFINITYF64)

#define NANF16X2 f16x2(NANF16, NANF16)
#define NANF32X2 f32x2(NANF32, NANF32)
#define NANF64X2 f64x2(NANF64, NANF64)
#define NANF16X3 f16x3(NANF16, NANF16, NANF16)
#define NANF32X3 f32x3(NANF32, NANF32, NANF32)
#define NANF64X3 f64x3(NANF64, NANF64, NANF64)
#define NANF16X4 f16x4(NANF16, NANF16, NANF16, NANF16)
#define NANF32X4 f32x4(NANF32, NANF32, NANF32, NANF32)
#define NANF64X4 f64x4(NANF64, NANF64, NANF64, NANF64)

// ===========================================
//
//
// Packed Matrix
//
//
// ===========================================

HCC_INTRINSIC typedef struct pf32x2x2 { float    scalars[4 ]; } pf32x2x2;
HCC_INTRINSIC typedef struct pf64x2x2 { double   scalars[4 ]; } pf64x2x2;
HCC_INTRINSIC typedef struct pf32x2x3 { float    scalars[6 ]; } pf32x2x3;
HCC_INTRINSIC typedef struct pf64x2x3 { double   scalars[6 ]; } pf64x2x3;
HCC_INTRINSIC typedef struct pf32x2x4 { float    scalars[8 ]; } pf32x2x4;
HCC_INTRINSIC typedef struct pf64x2x4 { double   scalars[8 ]; } pf64x2x4;
HCC_INTRINSIC typedef struct pf32x3x2 { float    scalars[6 ]; } pf32x3x2;
HCC_INTRINSIC typedef struct pf64x3x2 { double   scalars[6 ]; } pf64x3x2;
HCC_INTRINSIC typedef struct pf32x3x3 { float    scalars[9 ]; } pf32x3x3;
HCC_INTRINSIC typedef struct pf64x3x3 { double   scalars[9 ]; } pf64x3x3;
HCC_INTRINSIC typedef struct pf32x3x4 { float    scalars[12]; } pf32x3x4;
HCC_INTRINSIC typedef struct pf64x3x4 { double   scalars[12]; } pf64x3x4;
HCC_INTRINSIC typedef struct pf32x4x2 { float    scalars[8 ]; } pf32x4x2;
HCC_INTRINSIC typedef struct pf64x4x2 { double   scalars[8 ]; } pf64x4x2;
HCC_INTRINSIC typedef struct pf32x4x3 { float    scalars[12]; } pf32x4x3;
HCC_INTRINSIC typedef struct pf64x4x3 { double   scalars[12]; } pf64x4x3;
HCC_INTRINSIC typedef struct pf32x4x4 { float    scalars[16]; } pf32x4x4;
HCC_INTRINSIC typedef struct pf64x4x4 { double   scalars[16]; } pf64x4x4;

// ===========================================
//
//
// Matrix
//
//
// ===========================================

HCC_INTRINSIC typedef union f32x2x2 { float    cols[4][2]; vec4f32 vcols[2]; float    scalars[8 ]; } f32x2x2;
HCC_INTRINSIC typedef union f64x2x2 { double   cols[4][2]; vec4f64 vcols[2]; double   scalars[8 ]; } f64x2x2;
HCC_INTRINSIC typedef union f32x2x3 { float    cols[4][3]; vec4f32 vcols[3]; float    scalars[12]; } f32x2x3;
HCC_INTRINSIC typedef union f64x2x3 { double   cols[4][3]; vec4f64 vcols[3]; double   scalars[12]; } f64x2x3;
HCC_INTRINSIC typedef union f32x2x4 { float    cols[4][4]; vec4f32 vcols[4]; float    scalars[16]; } f32x2x4;
HCC_INTRINSIC typedef union f64x2x4 { double   cols[4][4]; vec4f64 vcols[4]; double   scalars[16]; } f64x2x4;
HCC_INTRINSIC typedef union f32x3x2 { float    cols[4][2]; vec4f32 vcols[2]; float    scalars[8 ]; } f32x3x2;
HCC_INTRINSIC typedef union f64x3x2 { double   cols[4][2]; vec4f64 vcols[2]; double   scalars[8 ]; } f64x3x2;
HCC_INTRINSIC typedef union f32x3x3 { float    cols[4][3]; vec4f32 vcols[3]; float    scalars[12]; } f32x3x3;
HCC_INTRINSIC typedef union f64x3x3 { double   cols[4][3]; vec4f64 vcols[3]; double   scalars[12]; } f64x3x3;
HCC_INTRINSIC typedef union f32x3x4 { float    cols[4][4]; vec4f32 vcols[4]; float    scalars[16]; } f32x3x4;
HCC_INTRINSIC typedef union f64x3x4 { double   cols[4][4]; vec4f64 vcols[4]; double   scalars[16]; } f64x3x4;
HCC_INTRINSIC typedef union f32x4x2 { float    cols[4][2]; vec4f32 vcols[2]; float    scalars[8 ]; } f32x4x2;
HCC_INTRINSIC typedef union f64x4x2 { double   cols[4][2]; vec4f64 vcols[2]; double   scalars[8 ]; } f64x4x2;
HCC_INTRINSIC typedef union f32x4x3 { float    cols[4][3]; vec4f32 vcols[3]; float    scalars[12]; } f32x4x3;
HCC_INTRINSIC typedef union f64x4x3 { double   cols[4][3]; vec4f64 vcols[3]; double   scalars[12]; } f64x4x3;
HCC_INTRINSIC typedef union f32x4x4 { float    cols[4][4]; vec4f32 vcols[4]; float    scalars[16]; } f32x4x4;
HCC_INTRINSIC typedef union f64x4x4 { double   cols[4][4]; vec4f64 vcols[4]; double   scalars[16]; } f64x4x4;

#define IDENTITYF32X2X2 ((f32x2x2) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF64X2X2 ((f64x2x2) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF32X2X3 ((f32x2x3) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF64X2X3 ((f64x2x3) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF32X2X4 ((f32x2x4) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF64X2X4 ((f64x2x4) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF32X3X2 ((f32x3x2) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF64X3X2 ((f64x3x2) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF32X3X3 ((f32x3x3) { .cols[0][0] = 1.0, .cols[1][1] = 1.0, .cols[2][2] = 1.0 })
#define IDENTITYF64X3X3 ((f64x3x3) { .cols[0][0] = 1.0, .cols[1][1] = 1.0, .cols[2][2] = 1.0 })
#define IDENTITYF32X3X4 ((f32x3x4) { .cols[0][0] = 1.0, .cols[1][1] = 1.0, .cols[2][2] = 1.0 })
#define IDENTITYF64X3X4 ((f64x3x4) { .cols[0][0] = 1.0, .cols[1][1] = 1.0, .cols[2][2] = 1.0 })
#define IDENTITYF32X4X2 ((f32x4x2) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF64X4X2 ((f64x4x2) { .cols[0][0] = 1.0, .cols[1][1] = 1.0 })
#define IDENTITYF32X4X3 ((f32x4x3) { .cols[0][0] = 1.0, .cols[1][1] = 1.0, .cols[2][2] = 1.0 })
#define IDENTITYF64X4X3 ((f64x4x3) { .cols[0][0] = 1.0, .cols[1][1] = 1.0, .cols[2][2] = 1.0 })
#define IDENTITYF32X4X4 ((f32x4x4) { .cols[0][0] = 1.0, .cols[1][1] = 1.0, .cols[2][2] = 1.0, .cols[3][3] = 1.0 })
#define IDENTITYF64X4X4 ((f64x4x4) { .cols[0][0] = 1.0, .cols[1][1] = 1.0, .cols[2][2] = 1.0, .cols[3][3] = 1.0 })

#endif // _HCC_STD_MATH_TYPES_H_
