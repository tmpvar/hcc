
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>
#include <hcc_texture_intrinsics.h>

typedef struct BC BC;
struct BC {
	HccRwTexture2D(FMT_32_UINT) texture;
};

HCC_COMPUTE(8, 8, 1)
void store_texture_atomic(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	// TODO bug in AMD driver pipeline compiler, needs reporting to MESA
	//uint32_t* addrsp(TEXTURE) addr = addr_rw_texture_2d_fmt_32_uint(bc->texture, sv->dispatch_idx.xy);
	//atomic_store_u32(addr, 1);
	atomic_store_u32(addr_rw_texture_2d_fmt_32_uint(bc->texture, sv->dispatch_idx.xy), 1);
}

