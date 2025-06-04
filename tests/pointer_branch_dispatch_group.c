
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>

typedef struct BC BC;
struct BC {
	HccRwBuffer(uint32_t) buffer;
};

typedef struct Dg Dg;
struct Dg {
	uint32_t a;
	uint32_t b;
};

HCC_COMPUTE(8, 8, 1)
void pointer_branch_dispatch_group(HccComputeSV const* const sv, BC const* addrsp(BC) const bc, Dg* addrsp(DG) const dg) {
	uint32_t* addrsp(DG) p = sv->dispatch_idx.x < 16 ? &dg->a : &dg->b;
	*p = 1;

	if (sv->dispatch_idx.y < 16) {
		p = &dg->a;
	} else {
		p = &dg->b;
	}
	*p += 2;
}
