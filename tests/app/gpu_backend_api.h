#pragma once

void gpu_init(void);
void gpu_compile_pipeline_render(const char* vertex, const char* pixel);
void gpu_compile_pipeline_compute(const char* compute);
