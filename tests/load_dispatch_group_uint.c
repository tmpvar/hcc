
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

typedef struct Lds Lds;
struct Lds {
	uint32_t v;
};

HCC_COMPUTE(8, 8, 1)
void load_dispatch_group_uint(HccComputeSV const* const sv, Bc const* addrsp(BC) const bc, Lds* addrsp(DG) const lds) {
	uint32_t a = lds->v;
}

