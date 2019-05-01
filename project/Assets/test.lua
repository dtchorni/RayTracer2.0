-- A simple scene with some miscellaneous geometry.

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({1.0, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

obj = gr.mesh('dodeca','dodeca.obj',false)
scene_root:add_child(obj)
obj:set_material(mat1)





white_light = gr.light({2.0, 5.0, 0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, 'test.png', 500, 500,
    {0, 2,-10}, {0, 0, -1}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, {white_light})
