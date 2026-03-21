#pragma once

#include <fstream>
#include <streambuf>

#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

#include <iostream>
#include <optional>
#include <set>


#include "./core/error/logger.h"
#include "core/performance/timer.h"
#include "core/event/event.h"
#include "core/event/event_category.h"
#include "core/event/event_dispatcher.h"
#include "core/event/event_type.h"
#include "core/event/window/window_resize_event.h"
#include "core/event/input/key_down_event.h"
#include "core/event/input/key_up_event.h"
#include "core/event/input/mouse_left_down_event.h"
#include "core/event/input/mouse_left_up_event.h"
#include "core/event/input/mouse_move_event.h"
#include "core/event/input/mouse_right_down_event.h"
#include "core/event/input/mouse_right_up_event.h"
#include "core/window/window.h"


#include "core/system/file_system.h"

#include "graphics/RHI_api/RHI_graphics_api.h"
#include "graphics/RHI/RHI_debug_mode.h"
#include "graphics/RHI/RHI_render_device.h"
#include "graphics/RHI/RHI_render_device_descriptor.h"

#include "graphics/RHI/object/command/RHI_command_queue_type.h"
#include "graphics/RHI/object/command/RHI_command_pool_descriptor.h"
#include "graphics/RHI/object/command/RHI_command_pool.h"
#include "graphics/RHI/object/command/RHI_command_buffer_type.h"
#include "graphics/RHI/object/command/RHI_command_buffer_descriptor.h"
#include "graphics/RHI/object/command/RHI_command_buffer.h"
#include "graphics/RHI/object/command/command_queue_support_bit.h"
#include "graphics/RHI/object/command/RHI_command_queue_descriptor.h"
#include "graphics/RHI/object/command/RHI_command_queue.h"

#include "graphics/RHI/resource/sampler/RHI_address_mode.h"
#include "graphics/RHI/resource/sampler/RHI_filter_mode.h"
#include "graphics/RHI/resource/sampler/RHI_sampler2D_descriptor.h"
#include "graphics/RHI/resource/RHI_resource_format.h"


#include "graphics/RHI/object/swapchain/RHI_swapchain_descriptor.h"
#include "graphics/RHI/object/swapchain/RHI_swapchain.h"

#include "graphics/RHI/object/sync/RHI_FenceCPU_descriptor.h"
#include "graphics/RHI/object/sync/RHI_FenceCPU.h"


#include "graphics/RHI/pipeline/framebuffer/RHI_frame_buffer.h"
#include "graphics/RHI/pipeline/framebuffer/RHI_frame_buffer_attachment.h"
#include "graphics/RHI/pipeline/framebuffer/RHI_frame_buffer_attachment_type.h"
#include "graphics/RHI/pipeline/framebuffer/RHI_frame_buffer_descriptor.h"

#include "graphics/RHI/pipeline/graphics/RHI_graphics_pipeline.h"
#include "graphics/RHI/pipeline/graphics/RHI_graphics_pipeline_descriptor.h"
#include "graphics/RHI/pipeline/graphics/rasterizer/RHI_cull_mode.h"
#include "graphics/RHI/pipeline/graphics/rasterizer/RHI_fill_mode.h"
#include "graphics/RHI/pipeline/graphics/rasterizer/RHI_winding_order.h"
#include "graphics/RHI/pipeline/graphics/topology/RHI_topology.h"
#include "graphics/RHI/pipeline/graphics/viewport/RHI_scissor_rect.h"
#include "graphics/RHI/pipeline/graphics/viewport/RHI_view_port.h"

#include "graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool.h"
#include "graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool_descriptor.h"
#include "graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool_size.h"
#include "graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set.h"
#include "graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set_descriptor.h"

#
#include "graphics/RHI/pipeline/layout/RHI_input_set.h"
#include "graphics/RHI/resource/shader/RHI_shader_type_flags.h"
#include "graphics/RHI/pipeline/layout/RHI_input_type.h"
#include "graphics/RHI/pipeline/layout/RHI_input_layout_descriptor.h"
#include "graphics/RHI/pipeline/layout/RHI_input_element.h"
#include "graphics/RHI/pipeline/layout/RHI_input_layout.h"

//#include "graphics/RHI/pipeline/layout/vertex_element.h"
//#include "graphics/RHI/pipeline/layout/vertex_layout.h"

#include "graphics/RHI/pipeline/renderpass/RHI_render_pass.h"
#include "graphics/RHI/pipeline/renderpass/RHI_render_pass_attachment.h"
#include "graphics/RHI/pipeline/renderpass/RHI_render_pass_attachment_type.h"
#include "graphics/RHI/pipeline/renderpass/RHI_render_pass_descriptor.h"
#include "graphics/RHI/pipeline/renderpass/RHI_render_pass_load_op.h"
#include "graphics/RHI/pipeline/renderpass/RHI_render_pass_store_op.h"

#include "graphics/RHI/resource/RHI_resource_memory_type.h"
#include "graphics/RHI/resource/buffer/RHI_buffer.h"
#include "graphics/RHI/resource/buffer/RHI_buffer_descriptor.h"
#include "graphics/RHI/resource/buffer/RHI_buffer_usage_flag.h"


#include "graphics/RHI/resource/RHI_resource_state.h"

#include "graphics/RHI/resource/shader/RHI_shader_type.h"

#include "graphics/RHI/resource/shader/RHI_shader_descriptor.h"
#include "graphics/RHI/resource/shader/RHI_shader.h"



#include "graphics/RHI/resource/texture/RHI_texture2D_descriptor.h"
#include "graphics/RHI/resource/texture/RHI_texture2D.h"



#include "graphics/RHI/RHI_render_device_descriptor.h"
#include "graphics/RHI/RHI_render_device.h"

#include "graphics/RHI_api/vk/RHI_VK_render_device.h"
#include "graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer_usage.h"
#include "graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"
#include "graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"

#include "graphics/RHI_api/vk/object/command/RHI_VK_command_buffer.h"
#include "graphics/RHI_api/vk/object/command/RHI_VK_command_pool.h"
#include "graphics/RHI_api/vk/object/command/RHI_VK_command_queue.h"

#include "graphics/RHI_api/vk/resource/RHI_VK_resource_format.h"
#include "graphics/RHI_api/vk/resource/RHI_VK_resource_state.h"
#include "graphics/RHI_api/vk/resource/RHI_VK_resource_memory_type.h"
#include "graphics/RHI_api/vk/object/swapchain/RHI_VK_swapchain.h"

#include "graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"

#include "graphics/RHI_api/vk/pipeline/framebuffer/RHI_VK_frame_buffer.h"

#include "graphics/RHI_api/vk/pipeline/graphics/rasterizer/RHI_VK_cull_mode.h"
#include "graphics/RHI_api/vk/pipeline/graphics/rasterizer/RHI_VK_fill_mode.h"
#include "graphics/RHI_api/vk/pipeline/graphics/rasterizer/RHI_VK_winding_order.h"

#include "graphics/RHI_api/vk/pipeline/graphics/topology/RHI_VK_topology.h"
#include "graphics/RHI_api/vk/resource/shader/RHI_VK_shader_type_flags.h"
#include "graphics/RHI_api/vk/resource/shader/RHI_VK_shader.h"
#include "graphics/RHI_api/vk/pipeline/graphics/RHI_VK_graphics_pipeline.h"

#include "graphics/RHI_api/vk/resource/sampler/RHI_VK_filter_mode.h"
#include "graphics/RHI_api/vk/resource/sampler/RHI_VK_address_mode.h"
#include "graphics/RHI_api/vk/resource/sampler/RHI_VK_sampler2D.h"

#include "graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_set.h"
#include "graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_pool.h"

#include "graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_layout.h"
#include "graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_type.h"

#include "graphics/RHI_api/vk/pipeline/renderpass/RHI_VK_render_pass.h"
#include "graphics/RHI_api/vk/pipeline/renderpass/RHI_VK_render_pass_load_op.h"
#include "graphics/RHI_api/vk/pipeline/renderpass/RHI_VK_render_pass_store_op.h"



#include "graphics/renderer/material/material.h"
#include "graphics/renderer/material/material_instance.h"

#include "graphics/renderer/model/sub_mesh.h"
#include "graphics/renderer/model/vertex.h"
#include "graphics/renderer/model/mesh.h"
#include "graphics/renderer/model/primitives/cube.h"
#include "graphics/renderer/model/primitives/quad.h"


#include "default_renderer.h"
#include "graphics/renderer/renderer3D.h"
#include "graphics/renderer/renderer_backend.h"

#include "utility/hash_utility.h"
#include "utility/string_utility.h"
#include "utility/version.h"

#include "graphics/renderer/camera/camera.h"
#include "graphics/renderer/camera/perspective.h"
#include "graphics/renderer/camera/orthographic.h"


#include "./application.h"
#include "./core/event/event_dispatcher.h"

#include <./glm/glm.hpp>
#include <./glm/gtc/matrix_transform.hpp>
