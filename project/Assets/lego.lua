
mat = gr.material({0.7,0.7,0.7},{0.5,0.5,0.5},0.5)

scene_root = gr.node('root')

brick = gr.lego('1x1',1,1,false)
scene_root:add_child(brick)
brick:rotate('X',90)
brick:set_material(mat)



lights = {
    gr.light({15, 30.0, 15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-15, 30.0, 15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({15, 30.0, -15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-15, 30.0, -15}, {0.9, 0.9, 0.9}, {1, 0, 0})
}

gr.render(scene_root, 'lego.png', 500, 500,
    {0, 7,-15}, {0, 0, 0}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, lights)
