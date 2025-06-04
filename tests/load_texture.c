
#include <stdbool.h>
#include <stdint.h>
#include <hmaths_types.h>
#include <hcc_shader.h>
#include <hmaths.h>
#include <hcc_texture_intrinsics.h>

typedef struct BC BC;
struct BC {
	HccRoTexture2D(FMT_32_UINT) texture;
};

HCC_COMPUTE(8, 8, 1)
void load_texture(HccComputeSV const* const sv, BC const* addrsp(BC) const bc) {
	uint32_t a = load_texture_2d_fmt_32_uint(bc->texture, sv->dispatch_idx.xy);
}

