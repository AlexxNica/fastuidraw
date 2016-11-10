# Begin standard header
sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)
# End standard header


dir:= $(d)/private
include $(dir)/Rules.mk

dir:= $(d)/shaders
include $(dir)/Rules.mk

LIBRARY_SOURCES += $(call filelist, shader_source.cpp shader_code.cpp \
	painter_item_shader_glsl.cpp painter_blend_shader_glsl.cpp \
	painter_brush_shader_glsl.cpp painter_backend_glsl.cpp)


# Begin standard footer
d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
# End standard footer
