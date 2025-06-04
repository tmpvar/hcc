
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
void store_texture(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	store_texture_2d_fmt_32_uint(bc->texture, sv->dispatch_idx.xy, 1);
}

