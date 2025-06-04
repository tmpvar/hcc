
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>
#include <hcc_texture_intrinsics.h>

typedef struct Bc Bc;
struct Bc {
	uint32_t placeholder;
};

typedef struct Struct Struct;
struct Struct {
	uint32_t v;
};

typedef struct Lds Lds;
struct Lds {
	Struct v;
};

HCC_COMPUTE(8, 8, 1)
void store_dispatch_group_struct(HccComputeSV const* const sv, Bc const* addrsp(BC) const bc, Lds* addrsp(DG) const lds) {
	lds->v = (Struct){0};
}


