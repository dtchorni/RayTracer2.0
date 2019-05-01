
mat = gr.material({0.7,0.7,0.7},{0.5,0.5,0.5},0.5)

scene_root = gr.node('root')

brick = gr.node('1x1')
scene_root:add_child(brick)
brick:rotate('X',90)

diff = gr.boolean('diff',2)
brick:add_child(diff)

uni = gr.boolean('union',0)
diff:add_child(uni)

body = gr.nh_box('body',{-3,-3,-3},6.0)
uni:add_child(body)
body:scale(5/6,1.0,5/6)
body:set_material(mat)

top = gr.nh_cylinder('top',{0,0,0},1.5,-1,0.4)
uni:add_child(top)
top:rotate('X',90)
top:translate(0,3.0,0)
top:set_material(mat)

inside = gr.nh_box('inside',{-2.5,-2.5,-2.5},5.0)
diff:add_child(inside)
inside:scale(3/5,1.0,3/5)
inside:translate(0,-1,-0.1)
inside:set_material(mat)

lights = {
    gr.light({15, 30.0, 15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-15, 30.0, 15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({15, 30.0, -15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-15, 30.0, -15}, {0.9, 0.9, 0.9}, {1, 0, 0})
}

gr.render(scene_root, '1x1.png', 500, 500,
    {0, 7,-15}, {0, 0, 0}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, lights)
