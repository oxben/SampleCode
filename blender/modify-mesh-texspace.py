import bpy

# Modify mesh texture space

obj = bpy.context.object

if obj.type == 'MESH':
	obj.draw_texture_space = True
	mesh = obj.data
	mesh.auto_texspace = False
	mesh.texspace_size = (0.001, 0.05, 0.05)

