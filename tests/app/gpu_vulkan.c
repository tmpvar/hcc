#include <vulkan/vulkan_core.h>

#include "app.h"
#include "platform_backend_api.h"

#define APP_VK_ASSERT(expr) APP_ASSERT((vk_result = (expr)) >= VK_SUCCESS, "vulkan error '%s' returned from: %s at %s:%u", app_vk_result_string(vk_result), #expr, __FILE__, __LINE__)

#include <hcc_interop_vulkan.h>
#include <hcc_interop_vulkan.c>

typedef struct GpuVk GpuVk;
struct GpuVk {
	uint32_t              queue_family_idx;
	uint32_t              swapchain_width;
	uint32_t              swapchain_height;

	VkInstance            instance;
	VkPhysicalDevice      physical_device;
	VkPhysicalDeviceMemoryProperties memory_properties;
	VkDevice              device;
	VkQueue               queue;

	VkShaderStageFlags    push_constants_stage_flags;
	VkDescriptorSet       descriptor_sets[1];
	HccInteropVulkan      interop;
};

GpuVk gpu;

const char* app_vk_result_string(VkResult result) {
	switch (result) {
		case VK_SUCCESS: return "VK_SUCCESS";
		case VK_NOT_READY: return "VK_NOT_READY";
		case VK_TIMEOUT: return "VK_TIMEOUT";
		case VK_EVENT_SET: return "VK_EVENT_SET";
		case VK_EVENT_RESET: return "VK_EVENT_RESET";
		case VK_INCOMPLETE: return "VK_INCOMPLETE";
		case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
		case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
		case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED";
		case VK_ERROR_DEVICE_LOST: return "VK_ERROR_DEVICE_LOST";
		case VK_ERROR_MEMORY_MAP_FAILED: return "VK_ERROR_MEMORY_MAP_FAILED";
		case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT";
		case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT";
		case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT";
		case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER";
		case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS";
		case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
		case VK_ERROR_FRAGMENTED_POOL: return "VK_ERROR_FRAGMENTED_POOL";
		case VK_ERROR_UNKNOWN: return "VK_ERROR_UNKNOWN";
		case VK_ERROR_OUT_OF_POOL_MEMORY: return "VK_ERROR_OUT_OF_POOL_MEMORY";
		case VK_ERROR_INVALID_EXTERNAL_HANDLE: return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
		case VK_ERROR_FRAGMENTATION: return "VK_ERROR_FRAGMENTATION";
		case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
		case VK_PIPELINE_COMPILE_REQUIRED: return "VK_PIPELINE_COMPILE_REQUIRED";
		case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR";
		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
		case VK_SUBOPTIMAL_KHR: return "VK_SUBOPTIMAL_KHR";
		case VK_ERROR_OUT_OF_DATE_KHR: return "VK_ERROR_OUT_OF_DATE_KHR";
		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
		case VK_ERROR_VALIDATION_FAILED_EXT: return "VK_ERROR_VALIDATION_FAILED_EXT";
		case VK_ERROR_INVALID_SHADER_NV: return "VK_ERROR_INVALID_SHADER_NV";
		case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
		case VK_ERROR_NOT_PERMITTED_KHR: return "VK_ERROR_NOT_PERMITTED_KHR";
		case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
		case VK_THREAD_IDLE_KHR: return "VK_THREAD_IDLE_KHR";
		case VK_THREAD_DONE_KHR: return "VK_THREAD_DONE_KHR";
		case VK_OPERATION_DEFERRED_KHR: return "VK_OPERATION_DEFERRED_KHR";
		case VK_OPERATION_NOT_DEFERRED_KHR: return "VK_OPERATION_NOT_DEFERRED_KHR";
		case VK_ERROR_COMPRESSION_EXHAUSTED_EXT: return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
		case VK_RESULT_MAX_ENUM: return "VK_RESULT_MAX_ENUM";
		default: return "??????";
	}
}

VkBool32 gpu_vk_handle_validation_error(
	VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
	void*                                            pUserData
) {
	APP_UNUSED(messageSeverity);
	APP_UNUSED(messageTypes);
	APP_UNUSED(pUserData);

	FILE* f;
#if defined(_WIN32)
	fopen_s(&f, "vk_validation_log.txt", "w");
#else
	f = fopen("vk_validation_log.txt", "w");
#endif
	fprintf(f, "Error Name: %s\n\n%s\n\n", pCallbackData->pMessageIdName, pCallbackData->pMessage);
	fflush(f);
	printf("Error Name: %s\n\n%s\n\n", pCallbackData->pMessageIdName, pCallbackData->pMessage);
	fflush(stdout);

	char* stacktrace = b_stacktrace_get_string();
	fprintf(f, "Stacktrace:\n%s\n\n", stacktrace);
	fflush(f);
	printf("Stacktrace:\n%s\n\n", stacktrace);
	fflush(stdout);
	platform_message_box("Vulkan Validation Error Detected.\nThe error has been logged to the vk_validation_log.txt file.\nPlease report this error and the log file on the HCC github issue tracker");

#if defined(_WIN32)
	DebugBreak();
#else
	__builtin_debugtrap();
#endif

	return VK_FALSE;
}

void gpu_init(void) {
	VkResult vk_result;

	//
	// create instance
	//
	{
		VkLayerProperties layer_props[512];
		uint32_t layer_props_count = APP_ARRAY_COUNT(layer_props);
		APP_VK_ASSERT(vkEnumerateInstanceLayerProperties(&layer_props_count, layer_props));
		bool has_khronos_validation = false;
		for (uint32_t idx = 0; idx < layer_props_count; idx += 1) {
			if (strcmp(layer_props[idx].layerName, "VK_LAYER_KHRONOS_validation") == 0) {
				has_khronos_validation = true;
			}
		}

		VkExtensionProperties extension_props[512];
		uint32_t extension_props_count = APP_ARRAY_COUNT(extension_props);
		APP_VK_ASSERT(vkEnumerateInstanceExtensionProperties(NULL, &extension_props_count, extension_props));
		bool has_debug_utils = false;
		for (uint32_t idx = 0; idx < extension_props_count; idx += 1) {
			if (strcmp(extension_props[idx].extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0) {
				has_debug_utils = true;
			}
		}

		static const char* layers[2];
		uint32_t layers_count = 0;
		if (has_khronos_validation) {
			layers[layers_count] = "VK_LAYER_KHRONOS_validation";
			layers_count += 1;
		};

#if GPU_VK_DEBUG
		layers[layers_count] = "VK_LAYER_LUNARG_api_dump";
		layers_count += 1;
#endif

		uint32_t extensions_count = 0;
		const char* extensions[1];
		if (has_debug_utils) {
			extensions[extensions_count] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
			extensions_count += 1;
		}

		VkApplicationInfo app = {
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pNext = NULL,
			.pApplicationName = APP_NAME,
			.applicationVersion = 0,
			.pEngineName = "none",
			.engineVersion = 0,
			.apiVersion = VK_API_VERSION_1_3,
		};
		VkInstanceCreateInfo create_info = {
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = NULL,
			.pApplicationInfo = &app,
			.enabledLayerCount = layers_count,
			.ppEnabledLayerNames = layers,
			.enabledExtensionCount = extensions_count,
			.ppEnabledExtensionNames = extensions,
		};

		APP_VK_ASSERT(vkCreateInstance(&create_info, NULL, &gpu.instance));
	}

	{
		VkDebugUtilsMessengerCreateInfoEXT create_info = {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			.pNext = NULL,
			.flags = 0,
			.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
			.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
			.pfnUserCallback = gpu_vk_handle_validation_error,
			.pUserData = NULL,
		};
		VkDebugUtilsMessengerEXT messenger;
		PFN_vkCreateDebugUtilsMessengerEXT fn = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(gpu.instance, "vkCreateDebugUtilsMessengerEXT");
		APP_VK_ASSERT(fn(gpu.instance, &create_info, NULL, &messenger));
	}

	{
#define PHYSICAL_DEVICES_CAP 128
		uint32_t physical_devices_count = PHYSICAL_DEVICES_CAP;
		VkPhysicalDevice physical_devices[PHYSICAL_DEVICES_CAP];
		APP_VK_ASSERT(vkEnumeratePhysicalDevices(gpu.instance, &physical_devices_count, physical_devices));

		gpu.physical_device = physical_devices[0];

		vkGetPhysicalDeviceMemoryProperties(gpu.physical_device, &gpu.memory_properties);
	}

	{
#define QUEUE_FAMILIES_CAP 128
		uint32_t queue_families_count = QUEUE_FAMILIES_CAP;
		VkQueueFamilyProperties queue_families[QUEUE_FAMILIES_CAP];
		vkGetPhysicalDeviceQueueFamilyProperties(gpu.physical_device, &queue_families_count, queue_families);

		gpu.queue_family_idx = UINT32_MAX;
		for_range(queue_family_idx, 0, queue_families_count) {
			if (queue_families[queue_family_idx].queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)) {
				gpu.queue_family_idx = queue_family_idx;
				break;
			}
		}

		APP_ASSERT(gpu.queue_family_idx != UINT32_MAX, "could not find graphics and compute queue");

		float queue_priorities[1] = {0.0};
		VkDeviceQueueCreateInfo queue = {
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.pNext = NULL,
			.queueFamilyIndex = gpu.queue_family_idx,
			.queueCount = 1,
			.pQueuePriorities = queue_priorities
		};

		VkPhysicalDeviceVulkan13Features features_1_3 = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
			.pNext = NULL,
			.dynamicRendering = VK_TRUE,
			.synchronization2 = VK_TRUE,
			.shaderDemoteToHelperInvocation = VK_TRUE,
			.maintenance4 = VK_TRUE,
		};
		VkPhysicalDeviceVulkan12Features features_1_2 = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
			.pNext = &features_1_3,
			.vulkanMemoryModel = VK_TRUE,
			.vulkanMemoryModelDeviceScope = VK_TRUE,
			.shaderSampledImageArrayNonUniformIndexing = VK_TRUE,
			.shaderStorageBufferArrayNonUniformIndexing = VK_TRUE,
			.shaderStorageImageArrayNonUniformIndexing = VK_TRUE,
			.shaderStorageTexelBufferArrayNonUniformIndexing = VK_TRUE,
			.descriptorBindingSampledImageUpdateAfterBind = VK_TRUE,
			.descriptorBindingStorageImageUpdateAfterBind = VK_TRUE,
			.descriptorBindingStorageBufferUpdateAfterBind = VK_TRUE,
			.descriptorBindingStorageTexelBufferUpdateAfterBind = VK_TRUE,
			.descriptorBindingPartiallyBound = VK_TRUE,
			.scalarBlockLayout = VK_TRUE,
		};
		VkPhysicalDeviceVulkan11Features features_1_1 = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
			.pNext = &features_1_2,
			.variablePointers = VK_TRUE,
			.variablePointersStorageBuffer = VK_TRUE,
		};
		VkPhysicalDeviceFeatures2 features = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
			.pNext = &features_1_1,
			.features.fragmentStoresAndAtomics = VK_TRUE,
		};

		VkDeviceCreateInfo create_info = {
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.pNext = &features,
			.queueCreateInfoCount = 1,
			.pQueueCreateInfos = &queue,
			.enabledLayerCount = 0,
			.ppEnabledLayerNames = NULL,
			.enabledExtensionCount = 0,
			.ppEnabledExtensionNames = NULL,
			.pEnabledFeatures = NULL,
		};

		APP_VK_ASSERT(vkCreateDevice(gpu.physical_device, &create_info, NULL, &gpu.device));

		vkGetDeviceQueue(gpu.device, gpu.queue_family_idx, 0, &gpu.queue);
	}

	HccInteropVulkanSetup interop_setup = {
		.device = gpu.device,
		.descriptor_sets = gpu.descriptor_sets,
		.descriptor_sets_count = APP_ARRAY_COUNT(gpu.descriptor_sets),
		.shader_stages = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT,
		.resource_descriptors_max = 1024,
		.bundled_constants_size_max = 64,
		.vkCreateDescriptorSetLayout = vkCreateDescriptorSetLayout,
		.vkCreateDescriptorPool = vkCreateDescriptorPool,
		.vkAllocateDescriptorSets = vkAllocateDescriptorSets,
		.vkCreatePipelineLayout = vkCreatePipelineLayout,
	};
	hcc_interop_vulkan_init(&gpu.interop, &interop_setup);
}

static void gpu_shader_compile(const char* name) {
	const char* exe =
#ifdef __linux__
		"./build/hcc"
#elif defined(_WIN32)
		"build\\hcc.exe"
#else
#error "unsupported platform"
#endif
		;

	char cmd[256];
	snprintf(cmd, sizeof(cmd), "%s -O -fo tests/%s.spirv -fi tests/%s.c --enable-unordered-swizzling", exe, name, name);
	APP_ASSERT(system(cmd) == 0, "compile error!\ncmd: %s\ndis: spirv-dis tests/%s.spirv", cmd, name);
}

static VkShaderModule gpu_shader_module_create(const char* name) {
	gpu_shader_compile(name);

	char path[256];
	snprintf(path, sizeof(path), "tests/%s.spirv", name);

	void* code;
	uintptr_t code_size;
	APP_ASSERT(platform_file_read_all(path, &code, &code_size), "failed to read shader file from disk: %s", path);

	VkShaderModuleCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext = NULL,
		.codeSize = code_size,
		.pCode = code,
		.flags = 0,
	};


	VkShaderModule vk_shader_module;
	VkResult vk_result;
	APP_VK_ASSERT(vkCreateShaderModule(gpu.device, &create_info, NULL, &vk_shader_module));
	return vk_shader_module;
}

void gpu_compile_pipeline_render(const char* vertex, const char* pixel) {
	VkShaderModule vertex_shader_module = gpu_shader_module_create(vertex);
	VkShaderModule pixel_shader_module = gpu_shader_module_create(pixel);

	VkPipelineShaderStageCreateInfo shader_stages[] = {
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.stage = VK_SHADER_STAGE_VERTEX_BIT,
			.module = vertex_shader_module,
			.pName = vertex,
			.pSpecializationInfo = NULL,
		},
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
			.module = pixel_shader_module,
			.pName = pixel,
			.pSpecializationInfo = NULL,
		},
	};

	VkPipelineVertexInputStateCreateInfo vertex_input_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.vertexBindingDescriptionCount = 0,
		.pVertexBindingDescriptions = NULL,
		.vertexAttributeDescriptionCount = 0,
		.pVertexAttributeDescriptions = NULL,
	};

	VkPipelineInputAssemblyStateCreateInfo input_assembly_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = false,
	};

	VkPipelineTessellationStateCreateInfo tessellation_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.patchControlPoints = 0,
	};

	VkPipelineViewportStateCreateInfo viewport_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.viewportCount = 1,
		.pViewports = NULL,
		.scissorCount = 1,
		.pScissors = NULL
	};

	VkPipelineRasterizationStateCreateInfo rasterization_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.depthClampEnable = false,
		.rasterizerDiscardEnable = false,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.cullMode = VK_CULL_MODE_NONE,
		.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
		.depthBiasEnable = false,
		.depthBiasConstantFactor = 0.f,
		.depthBiasClamp = 0.f,
		.depthBiasSlopeFactor = 0.f,
		.lineWidth = 1.f,
	};

	VkPipelineMultisampleStateCreateInfo multisample_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.sampleShadingEnable = false,
		.minSampleShading = 0.f,
		.pSampleMask = NULL,
		.alphaToCoverageEnable = false,
		.alphaToOneEnable = false,
	};

	VkPipelineDepthStencilStateCreateInfo depth_stencil_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.depthTestEnable = true,
		.depthWriteEnable = true,
		.depthCompareOp = VK_COMPARE_OP_GREATER_OR_EQUAL,
		.depthBoundsTestEnable = false,
		.stencilTestEnable = false,
		.front = {0},
		.back = {0},
		.minDepthBounds = 0.f,
		.maxDepthBounds = 1.f,
	};

	VkPipelineColorBlendAttachmentState color_blend_attachment = {
		.blendEnable = true,
		.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
		.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		.colorBlendOp = VK_BLEND_OP_ADD,
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		.alphaBlendOp = VK_BLEND_OP_ADD,
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
	};

	VkPipelineColorBlendStateCreateInfo color_blend_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.logicOpEnable = false,
		.logicOp = 0,
		.attachmentCount = 1,
		.pAttachments = &color_blend_attachment,
		.blendConstants = {0},
	};

	VkDynamicState vk_dynamic_states[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
	};

	VkPipelineDynamicStateCreateInfo dynamic_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.dynamicStateCount = APP_ARRAY_COUNT(vk_dynamic_states),
		.pDynamicStates = vk_dynamic_states,
	};

	VkFormat image_format = VK_FORMAT_R8G8B8A8_UNORM;
	VkPipelineRenderingCreateInfo rendering_create_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
		.pNext = NULL,
		.colorAttachmentCount = 1,
		.pColorAttachmentFormats = &image_format,
		.depthAttachmentFormat = VK_FORMAT_D32_SFLOAT,
		.stencilAttachmentFormat = VK_FORMAT_UNDEFINED,
	};

	VkGraphicsPipelineCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = &rendering_create_info,
		.flags = 0,
		.stageCount = APP_ARRAY_COUNT(shader_stages),
		.pStages = shader_stages,
		.pVertexInputState = &vertex_input_state,
		.pInputAssemblyState = &input_assembly_state,
		.pTessellationState = &tessellation_state,
		.pViewportState = &viewport_state,
		.pRasterizationState = &rasterization_state,
		.pMultisampleState = &multisample_state,
		.pDepthStencilState = &depth_stencil_state,
		.pColorBlendState = &color_blend_state,
		.pDynamicState = &dynamic_state,
		.layout = gpu.interop.pipeline_layout,
		.renderPass = VK_NULL_HANDLE,
		.subpass = 0,
		.basePipelineHandle = NULL,
		.basePipelineIndex = 0,
	};

	VkResult vk_result;
	VkPipeline pipeline;
	APP_VK_ASSERT(vkCreateGraphicsPipelines(gpu.device, VK_NULL_HANDLE, 1, &create_info, NULL, &pipeline));
}

void gpu_compile_pipeline_compute(const char* compute) {
	VkShaderModule compute_shader_module = gpu_shader_module_create(compute);

	VkComputePipelineCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
		.layout = gpu.interop.pipeline_layout,
		.stage = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage = VK_SHADER_STAGE_COMPUTE_BIT,
			.module = compute_shader_module,
			.pName = compute,
		},
	};

	VkResult vk_result;
	VkPipeline pipeline;
	APP_VK_ASSERT(vkCreateComputePipelines(gpu.device, NULL, 1, &create_info, NULL, &pipeline));
}
