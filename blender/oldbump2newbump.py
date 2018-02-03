import bpy


materials = bpy.data.materials

for m in materials:
    textures = m.textures
    try:
        for t in textures:
            t.new_bump = True
    except:
        continue

print('done')

