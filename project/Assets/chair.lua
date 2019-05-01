
grey = gr.material({0.7,0.7,0.7},{0.5,0.5,0.5},0.5)

scene_root = gr.node('root')

chair = gr.node('chair')
scene_root:add_child(chair)

bottom = gr.node('bottom')
chair:add_child(bottom)

lf = gr.nh_cylinder('lf',{0,0,0},0.2,-2.3,2.3)
bottom:add_child(lf)
lf:rotate('X',90)
lf:translate(2.3,0,-2.6)
lf:set_material(grey)

rf = gr.nh_cylinder('rf',{0,0,0},0.2,-2.3,2.3)
bottom:add_child(rf)
rf:rotate('X',90)
rf:translate(-2.3,0,-2.6)
rf:set_material(grey)


rb = gr.nh_cylinder('rb',{0,0,0},0.2,-2.3,2.3)
bottom:add_child(rb)
rb:rotate('X',90)
rb:translate(-2.3,0,2.6)
rb:set_material(grey)

lb = gr.nh_cylinder('lb',{0,0,0},0.2,-2.3,2.3)
bottom:add_child(lb)
lb:rotate('X',90)
lb:translate(2.3,0,2.6)
lb:set_material(grey)


seat = gr.nh_cylinder('seat',{0,0,0},0.3,-2.5,2.5)
bottom:add_child(seat)
seat:set_material(grey)
seat:scale(10.6,1.0,1.0)
seat:rotate('Y',90)
seat:translate(0,2.3,0)

back=gr.node('back')
chair:add_child(back)
back:translate(0,5.8,2.6)

back0 = gr.nh_cylinder('back0',{0,0,0},0.2,-2.6,2.6)
back:add_child(back0)
back0:set_material(grey)
back0:rotate('X',90)
back0:translate(2.2,-0.85,0)

back1 = gr.nh_cylinder('back1',{0,0,0},0.2,-2.6,2.6)
back:add_child(back1)
back1:set_material(grey)
back1:rotate('X',90)
back1:translate(-2.2,-0.85,0)

flat = gr.nh_cylinder('flat',{0,0,0},0.3,-2.3,2.3)
back:add_child(flat)
flat:set_material(grey)
flat:scale(7.0,1.0,1.0)
flat:rotate('Y',90)
flat:rotate('X',90)
flat:translate(0,0,-0.29)

lights = {
    gr.light({10, 30.0, 10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-10, 30.0, 10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({10, 30.0, -10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-10, 30.0, -10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
}

gr.render(scene_root, 'chair.png', 500, 500,
    {9, 7,-10}, {0, 0, 0}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, lights)
