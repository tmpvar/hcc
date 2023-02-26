#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int DataType;
enum DataType {
	DATA_TYPE_BOOL,
	DATA_TYPE_HALF,
	DATA_TYPE_FLOAT,
	DATA_TYPE_DOUBLE,
	DATA_TYPE_S8,
	DATA_TYPE_S16,
	DATA_TYPE_S32,
	DATA_TYPE_S64,
	DATA_TYPE_U8,
	DATA_TYPE_U16,
	DATA_TYPE_U32,
	DATA_TYPE_U64,

	DATA_TYPE_COUNT,
};

typedef int Vector;
enum Vector {
	VECTOR_1,
	VECTOR_2,
	VECTOR_3,
	VECTOR_4,

	VECTOR_COUNT,
};

typedef int Texture;
enum Texture {
	TEXTURE_1D,
	TEXTURE_1D_ARRAY,
	TEXTURE_2D,
	TEXTURE_2D_ARRAY,
	TEXTURE_2D_MS,
	TEXTURE_2D_MS_ARRAY,
	TEXTURE_CUBE,
	TEXTURE_CUBE_ARRAY,
	TEXTURE_3D,

	TEXTURE_COUNT,
};

static const char* data_type_identifiers[DATA_TYPE_COUNT] = {
	[DATA_TYPE_BOOL] = "bool",
	[DATA_TYPE_HALF] = "half",
	[DATA_TYPE_FLOAT] = "float",
	[DATA_TYPE_DOUBLE] = "double",
	[DATA_TYPE_S8] = "int8_t",
	[DATA_TYPE_S16] = "int16_t",
	[DATA_TYPE_S32] = "int32_t",
	[DATA_TYPE_S64] = "int64_t",
	[DATA_TYPE_U8] = "uint8_t",
	[DATA_TYPE_U16] = "uint16_t",
	[DATA_TYPE_U32] = "uint32_t",
	[DATA_TYPE_U64] = "uint64_t",
};

static const char* data_type_suffixes[DATA_TYPE_COUNT] = {
	[DATA_TYPE_BOOL] = "bool",
	[DATA_TYPE_HALF] = "f16",
	[DATA_TYPE_FLOAT] = "f32",
	[DATA_TYPE_DOUBLE] = "f64",
	[DATA_TYPE_S8] = "s8",
	[DATA_TYPE_S16] = "s16",
	[DATA_TYPE_S32] = "s32",
	[DATA_TYPE_S64] = "s64",
	[DATA_TYPE_U8] = "u8",
	[DATA_TYPE_U16] = "u16",
	[DATA_TYPE_U32] = "u32",
	[DATA_TYPE_U64] = "u64",
};

static bool data_type_is_texture_compatible[DATA_TYPE_COUNT] = {
	[DATA_TYPE_BOOL] = false,
	[DATA_TYPE_HALF] = false,
	[DATA_TYPE_FLOAT] = true,
	[DATA_TYPE_DOUBLE] = false,
	[DATA_TYPE_S8] = false,
	[DATA_TYPE_S16] = false,
	[DATA_TYPE_S32] = true,
	[DATA_TYPE_S64] = false,
	[DATA_TYPE_U8] = false,
	[DATA_TYPE_U16] = false,
	[DATA_TYPE_U32] = true,
	[DATA_TYPE_U64] = false,
};

static const char* vector_suffixes[] = {
	[VECTOR_1] = "",
	[VECTOR_2] = "x2",
	[VECTOR_3] = "x3",
	[VECTOR_4] = "x4",
};

static const char* texture_names_snake_case[TEXTURE_COUNT] = {
	[TEXTURE_1D] = "texture_1d",
	[TEXTURE_1D_ARRAY] = "texture_1d_array",
	[TEXTURE_2D] = "texture_2d",
	[TEXTURE_2D_ARRAY] = "texture_2d_array",
	[TEXTURE_2D_MS] = "texture_2d_ms",
	[TEXTURE_2D_MS_ARRAY] = "texture_2d_ms_array",
	[TEXTURE_CUBE] = "texture_cube",
	[TEXTURE_CUBE_ARRAY] = "texture_cube_array",
	[TEXTURE_3D] = "texture_3d",
};

static const char* texture_names_title_case[TEXTURE_COUNT] = {
	[TEXTURE_1D] = "HccRoTexture1D",
	[TEXTURE_1D_ARRAY] = "HccRoTexture1DArray",
	[TEXTURE_2D] = "HccRoTexture2D",
	[TEXTURE_2D_ARRAY] = "HccRoTexture2DArray",
	[TEXTURE_2D_MS] = "HccRoTexture2DMS",
	[TEXTURE_2D_MS_ARRAY] = "HccRoTexture2DMSArray",
	[TEXTURE_CUBE] = "HccRoTextureCube",
	[TEXTURE_CUBE_ARRAY] = "HccRoTextureCubeArray",
	[TEXTURE_3D] = "HccRoTexture3D",
};

static const char* texture_names_title_case_rw[TEXTURE_COUNT] = {
	[TEXTURE_1D] = "HccRwTexture1D",
	[TEXTURE_1D_ARRAY] = "HccRwTexture1DArray",
	[TEXTURE_2D] = "HccRwTexture2D",
	[TEXTURE_2D_ARRAY] = "HccRwTexture2DArray",
	[TEXTURE_2D_MS] = "HccRwTexture2DMS",
	[TEXTURE_2D_MS_ARRAY] = "HccRwTexture2DMSArray",
	[TEXTURE_CUBE] = "HccRwTextureCube",
	[TEXTURE_CUBE_ARRAY] = "HccRwTextureCubeArray",
	[TEXTURE_3D] = "HccRwTexture3D",
};

static const char* texture_names_title_case_wo[TEXTURE_COUNT] = {
	[TEXTURE_1D] = "HccWoTexture1D",
	[TEXTURE_1D_ARRAY] = "HccWoTexture1DArray",
	[TEXTURE_2D] = "HccWoTexture2D",
	[TEXTURE_2D_ARRAY] = "HccWoTexture2DArray",
	[TEXTURE_2D_MS] = "HccWoTexture2DMS",
	[TEXTURE_2D_MS_ARRAY] = "HccWoTexture2DMSArray",
	[TEXTURE_CUBE] = "HccWoTextureCube",
	[TEXTURE_CUBE_ARRAY] = "HccWoTextureCubeArray",
	[TEXTURE_3D] = "HccWoTexture3D",
};

static const char* texture_names_title_case_sample[TEXTURE_COUNT] = {
	[TEXTURE_1D] = "HccSampleTexture1D",
	[TEXTURE_1D_ARRAY] = "HccSampleTexture1DArray",
	[TEXTURE_2D] = "HccSampleTexture2D",
	[TEXTURE_2D_ARRAY] = "HccSampleTexture2DArray",
	[TEXTURE_2D_MS] = "HccSampleTexture2DMS",
	[TEXTURE_2D_MS_ARRAY] = "HccSampleTexture2DMSArray",
	[TEXTURE_CUBE] = "HccSampleTextureCube",
	[TEXTURE_CUBE_ARRAY] = "HccSampleTextureCubeArray",
	[TEXTURE_3D] = "HccSampleTexture3D",
};

static const char* texture_index_type[TEXTURE_COUNT] = {
	[TEXTURE_1D] = "uint32_t",
	[TEXTURE_1D_ARRAY] = "u32x2",
	[TEXTURE_2D] = "u32x2",
	[TEXTURE_2D_ARRAY] = "u32x3",
	[TEXTURE_2D_MS] = "u32x3",
	[TEXTURE_2D_MS_ARRAY] = "u32x4",
	[TEXTURE_CUBE] = NULL,
	[TEXTURE_CUBE_ARRAY] = NULL,
	[TEXTURE_3D] = "u32x3",
};

static const char* texture_coord_type[TEXTURE_COUNT] = {
	[TEXTURE_1D] = "float",
	[TEXTURE_1D_ARRAY] = "f32x2",
	[TEXTURE_2D] = "f32x2",
	[TEXTURE_2D_ARRAY] = "f32x3",
	[TEXTURE_2D_MS] = "f32x2",
	[TEXTURE_2D_MS_ARRAY] = "f32x3",
	[TEXTURE_CUBE] = "f32x3",
	[TEXTURE_CUBE_ARRAY] = "f32x4",
	[TEXTURE_3D] = "f32x3",
};

static bool texture_is_ms[TEXTURE_COUNT] = {
	[TEXTURE_1D] = false,
	[TEXTURE_1D_ARRAY] = false,
	[TEXTURE_2D] = false,
	[TEXTURE_2D_ARRAY] = false,
	[TEXTURE_2D_MS] = true,
	[TEXTURE_2D_MS_ARRAY] = true,
	[TEXTURE_CUBE] = false,
	[TEXTURE_CUBE_ARRAY] = false,
	[TEXTURE_3D] = false,
};

static bool texture_can_gather[TEXTURE_COUNT] = {
	[TEXTURE_1D] = false,
	[TEXTURE_1D_ARRAY] = false,
	[TEXTURE_2D] = true,
	[TEXTURE_2D_ARRAY] = false,
	[TEXTURE_2D_MS] = false,
	[TEXTURE_2D_MS_ARRAY] = false,
	[TEXTURE_CUBE] = true,
	[TEXTURE_CUBE_ARRAY] = true,
	[TEXTURE_3D] = false,
};

typedef struct Ctx Ctx;
struct Ctx {
	FILE* f;
	DataType data_type;
	Vector vector;
	Texture texture;
	bool use_rw;
};

Ctx ctx;

void print_entry(const char* string) {
	const char* prev_special = string, *next_special = string;
	while ((next_special = strchr(next_special, '$'))) {
		unsigned size = next_special - prev_special;
		fprintf(ctx.f, "%.*s", size, prev_special);
		next_special += 1; // skip '$'
		switch (*next_special) {
		case 'd':
			next_special += 1; // skip 'd'
			switch (*next_special) {
			case 'i':
				fprintf(ctx.f, "%s", data_type_identifiers[ctx.data_type]);
				break;
			case 'x':
				fprintf(ctx.f, "%s", data_type_suffixes[ctx.data_type]);
				break;
			}
			break;
		case 'v':
			next_special += 1; // skip 'v'
			switch (*next_special) {
				case 'i':
					if (ctx.vector == VECTOR_1) {
						fprintf(ctx.f, "%s", data_type_identifiers[ctx.data_type]);
					} else {
						fprintf(ctx.f, "%s", data_type_suffixes[ctx.data_type]);
						fprintf(ctx.f, "%s", vector_suffixes[ctx.vector]);
					}
					break;
				case 'x':
					fprintf(ctx.f, "%s", data_type_suffixes[ctx.data_type]);
					fprintf(ctx.f, "%s", vector_suffixes[ctx.vector]);
					break;
			}
			break;
		case 't':
			next_special += 1; // skip 't'
			switch (*next_special) {
				case 'r':
					fprintf(ctx.f, "%s", texture_names_snake_case[ctx.texture]);
					break;
				case 'R':
					if (ctx.vector == VECTOR_1) {
						fprintf(ctx.f, "%s(%s)", (ctx.use_rw ? texture_names_title_case_rw : texture_names_title_case)[ctx.texture], data_type_identifiers[ctx.data_type]);
					} else {
						fprintf(ctx.f, "%s(%s%s)", (ctx.use_rw ? texture_names_title_case_rw : texture_names_title_case)[ctx.texture], data_type_suffixes[ctx.data_type], vector_suffixes[ctx.vector]);
					}
					break;
				case 'w':
					fprintf(ctx.f, "%s", texture_names_snake_case[ctx.texture]);
					break;
				case 'W':
					if (ctx.vector == VECTOR_1) {
						fprintf(ctx.f, "%s(%s)", (ctx.use_rw ? texture_names_title_case_rw : texture_names_title_case_wo)[ctx.texture], data_type_identifiers[ctx.data_type]);
					} else {
						fprintf(ctx.f, "%s(%s%s)", (ctx.use_rw ? texture_names_title_case_rw : texture_names_title_case_wo)[ctx.texture], data_type_suffixes[ctx.data_type], vector_suffixes[ctx.vector]);
					}
					break;
				case 's':
					fprintf(ctx.f, "%s", texture_names_snake_case[ctx.texture]);
					break;
				case 'S':
					if (ctx.vector == VECTOR_1) {
						fprintf(ctx.f, "%s(%s)", texture_names_title_case_sample[ctx.texture], data_type_identifiers[ctx.data_type]);
					} else {
						fprintf(ctx.f, "%s(%s%s)", texture_names_title_case_sample[ctx.texture], data_type_suffixes[ctx.data_type], vector_suffixes[ctx.vector]);
					}
					break;
				case 'i':
					fprintf(ctx.f, "%s", texture_index_type[ctx.texture]);
					break;
				case 'c':
					fprintf(ctx.f, "%s", texture_coord_type[ctx.texture]);
					break;
			}
			break;
		}
		next_special += 1;
		prev_special = next_special;
	}
	fprintf(ctx.f, "%s", prev_special);
}

void print_texture_functions(const char* comment, const char* fmt, const char* generic_ident, const char* generic_args, const char* generic_fmt, bool has_index_type, bool is_sample, bool is_gather, bool want_rw, Vector vector_min) {
	ctx.use_rw = false;
	fprintf(ctx.f, "//\n");
	fprintf(ctx.f, "// %s\n", comment);
	for (Texture texture = 0; texture < TEXTURE_COUNT; texture += 1) {
		ctx.texture = texture;
		if (has_index_type && !texture_index_type[texture]) {
			continue;
		}

		if (is_sample && texture_is_ms[texture]) {
			continue;
		}

		if (is_gather && !texture_can_gather[texture]) {
			continue;
		}

		for (Vector vector = vector_min; vector < VECTOR_COUNT; vector += 1) {
			for (DataType data_type = 0; data_type < DATA_TYPE_COUNT; data_type += 1) {
				ctx.data_type = data_type;
				if (!data_type_is_texture_compatible[data_type]) {
					continue;
				}

				ctx.vector = vector;
				print_entry(fmt);
				fprintf(ctx.f, ";\n");
			}
		}
	}
	fprintf(ctx.f, "#ifdef HCC_HAS_C_GENERIC_SUPPORT\n");
	fprintf(ctx.f, "#define %s(%s) \\\n", generic_ident, generic_args);
	fprintf(ctx.f, "\t_Generic((texture)");
	bool has_been_again = false;
AGAIN: {}
	for (Texture texture = 0; texture < TEXTURE_COUNT; texture += 1) {
		ctx.texture = texture;
		if (has_index_type && !texture_index_type[texture]) {
			continue;
		}

		if (is_sample && texture_is_ms[texture]) {
			continue;
		}

		if (is_gather && !texture_can_gather[texture]) {
			continue;
		}

		for (Vector vector = vector_min; vector < VECTOR_COUNT; vector += 1) {
			for (DataType data_type = 0; data_type < DATA_TYPE_COUNT; data_type += 1) {
				ctx.data_type = data_type;
				if (!data_type_is_texture_compatible[data_type]) {
					continue;
				}

				ctx.vector = vector;
				fprintf(ctx.f, ", \\\n\t\t");
				print_entry(generic_fmt);
			}
		}
	}
	if (!has_been_again && want_rw) {
		has_been_again = true;
		ctx.use_rw = true;
		goto AGAIN;
	}
	fprintf(ctx.f, " \\\n\t)(%s)\n", generic_args);
	fprintf(ctx.f, "#endif // HCC_HAS_C_GENERIC_SUPPORT\n");
	fprintf(ctx.f, "\n");
}

FILE* open_file_write(const char* path) {
	FILE* f = fopen(path, "w");
	if (f == NULL) {
		fprintf(stderr, "failed to open file at '%s'\n", path);
		exit(1);
	}
	return f;
}

void print_file_header() {
	fprintf(ctx.f,
		"// !?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!\n"
		"// !?!?!? WARNING CONTRIBUTOR ?!?!?!\n"
		"// !?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!\n"
		"// this file is generated by tools/generator.c\n"
		"// please edit that file and regenerate this one if you want to make edits\n"
		"\n"
	);
}

void print_header_file_header(const char* guard) {
	print_file_header();
	fprintf(ctx.f,
		"#ifndef %s\n"
		"#define %s\n"
		"\n", guard, guard
	);
}

void print_header_file_footer(const char* guard) {
	fprintf(ctx.f, "\n#endif // %s\n" , guard);
}

void generate_texture_intrinsics_file(void) {
	ctx.f = open_file_write("shader-include/hcc_texture_intrinsics.h");
	print_header_file_header("_HCC_TEXTURE_INTRINSICS_H_");

	print_texture_functions(
		"load a texel from 'texture' at 'idx'",
		"$vi load_$tr_$vx($tR texture, $ti idx)",
		"load_textureG",
		"texture, idx",
		"$tR: load_$tr_$vx",
		true,
		false,
		false,
		true,
		VECTOR_1
	);

	print_texture_functions(
		"fetch a texel from 'texture' at 'idx'",
		"$vi fetch_$tr_$vx($tS texture, $ti idx)",
		"fetch_textureG",
		"texture, idx",
		"$tS: fetch_$tr_$vx",
		true,
		true,
		false,
		false,
		VECTOR_1
	);

	print_texture_functions(
		"sample a texel from 'texture' at 'coord' using 'sampler'",
		"$vi sample_$tr_$vx($tS texture, HccRoSampler sampler, $tc coord)",
		"sample_textureG",
		"texture, sampler, coord",
		"$tS: sample_$tr_$vx",
		false,
		false,
		true,
		false,
		VECTOR_1
	);

	print_texture_functions(
		"sample a texel from 'texture' at 'coord' using 'sampler' with a 'mip_bias'",
		"$vi sample_mip_bias_$tr_$vx($tS texture, HccRoSampler sampler, $tc coord, float mip_bias)",
		"sample_mip_bias_textureG",
		"texture, sampler, coord, mip_bias",
		"$tS: sample_mip_bias_$tr_$vx",
		false,
		false,
		true,
		false,
		VECTOR_1
	);

	print_texture_functions(
		"sample a texel from 'texture' at 'coord' using 'sampler' using a custom 'ddx' and 'ddy' to select the mip level",
		"$vi sample_mip_gradient_$tr_$vx($tS texture, HccRoSampler sampler, $tc coord, $tc ddx, $tc ddy)",
		"sample_mip_gradient_textureG",
		"texture, sampler, coord, ddx, ddy",
		"$tS: sample_mip_gradient_$tr_$vx",
		false,
		false,
		true,
		false,
		VECTOR_1
	);

	print_texture_functions(
		"sample a texel from 'texture' at 'coord' using 'sampler' using mip 'level'",
		"$vi sample_mip_level_$tr_$vx($tS texture, HccRoSampler sampler, $tc coord, float level)",
		"sample_mip_level_textureG",
		"texture, sampler, coord, level",
		"$tS: sample_mip_level_$tr_$vx",
		false,
		false,
		true,
		false,
		VECTOR_1
	);

	print_texture_functions(
		"gather the four texels used by sample_* but extract the _red_ channel before interpolation",
		"$vi gather_red_$tr_$vx($tS texture, HccRoSampler sampler, $tc coord)",
		"gather_red_textureG",
		"texture, sampler, coord",
		"$tS: gather_red_$tr_$vx",
		false,
		true,
		true,
		false,
		VECTOR_1
	);

	print_texture_functions(
		"gather the four texels used by sample_* but extract the _green_ channel before interpolation",
		"$vi gather_green_$tr_$vx($tS texture, HccRoSampler sampler, $tc coord)",
		"gather_green_textureG",
		"texture, sampler, coord",
		"$tS: gather_green_$tr_$vx",
		false,
		true,
		true,
		false,
		VECTOR_2
	);

	print_texture_functions(
		"gather the four texels used by sample_* but extract the _blue_ channel before interpolation",
		"$vi gather_blue_$tr_$vx($tS texture, HccRoSampler sampler, $tc coord)",
		"gather_blue_textureG",
		"texture, sampler, coord",
		"$tS: gather_blue_$tr_$vx",
		false,
		true,
		true,
		false,
		VECTOR_3
	);

	print_texture_functions(
		"gather the four texels used by sample_* but extract the _alpha_ channel before interpolation",
		"$vi gather_alpha_$tr_$vx($tS texture, HccRoSampler sampler, $tc coord)",
		"gather_alpha_textureG",
		"texture, sampler, coord",
		"$tS: gather_alpha_$tr_$vx",
		false,
		true,
		true,
		false,
		VECTOR_4
	);

	print_texture_functions(
		"store a 'value' in 'texture' at 'idx'",
		"void store_$tw_$vx($tW texture, $ti idx, $vi value)",
		"store_textureG",
		"texture, idx, value",
		"$tW: store_$tw_$vx",
		true,
		false,
		false,
		true,
		VECTOR_1
	);

	print_header_file_footer("_HCC_TEXTURE_INTRINSICS_H_");
}

int main(int argc, char** argv) {
	generate_texture_intrinsics_file();
}

