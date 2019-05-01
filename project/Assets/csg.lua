-- A simple scene with some miscellaneous geometry.

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({1.0, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.2, 0.2}, {1.0, 0.6, 0.3}, 50)
mat4 = gr.material({0.2, 0.2, 1.0}, {1.0, 0.6, 0.3}, 75)

scene_root = gr.node('root')

uni = gr.boolean('union',0)
scene_root:add_child(uni)

diff = gr.boolean('diff',2)
diff:translate(5.0,-2.5,-1)
scene_root:add_child(diff)

inter = gr.boolean('inter',1)
inter:translate(0,5.5,1)
scene_root:add_child(inter)


cone0 = gr.nh_cone('cone0',{0,0,0},0.0,1.0)
cone0:scale(2,2,4)
cone0:rotate('X',90)
cone0:translate(-8,3,2)
uni:add_child(cone0)
cone0:set_material(mat1)


cyl0 = gr.nh_cylinder('cyl0',{0,0,0},1.75,-1.0,1.0)
uni:add_child(cyl0)
cyl0:set_material(mat2)
cyl0:scale(1,1,3)
cyl0:rotate('X',90)
cyl0:translate(-8,-3.6,2)

sph0 = gr.nh_sphere('sph0',{0,0,0},3)
diff:add_child(sph0)
sph0:set_material(mat3)

sph1 = gr.nh_sphere('sph1',{0,0,0},2.75)
diff:add_child(sph1)
sph1:translate(0.5,0.1,-0.5)
sph1:set_material(mat4)


sph2 = gr.nh_sphere('sph2',{0,0,0},3)
inter:add_child(sph2)
sph2:set_material(mat3)

sph3 = gr.nh_sphere('sph3',{1.5,0,0},3)
inter:add_child(sph3)
--sph3:translate(2.5,0.1,-0.5)
sph3:set_material(mat4)



white_light = gr.light({2.0, 35.0, -2}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, 'csg.png', 500, 500,
    {0, 2,-25}, {0, 0, -1}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, {white_light})
