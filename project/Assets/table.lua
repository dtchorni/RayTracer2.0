
mat1 = gr.material({0.7,0.7,0.7},{0.5,0.5,0.5},0.5)
mat2 = gr.material({0.5,0.5,0.5},{0.3,0.3,0.3},0.3)
mat3 = gr.material({0.3,0.3,0.3},{0.1,0.1,0.1},0.1)

scene_root = gr.node('root')

table = gr.node('table')
scene_root:add_child(table)

legs = gr.node('legs')
table:add_child(legs)

t = gr.node('table')
table:add_child(t)

flat = gr.node('flat')
table:add_child(flat)

t0 = gr.nh_cylinder('t0',{0,0,0},1.0,-3.0,3.0)
t:add_child(t0)
t0:scale(4,0.7,1.0)
t0:set_material(mat1)


surface = gr.nh_box('surface', {-0.5,0.5,0.5},1.0)
flat:add_child(surface)
surface:scale(5.5,1.0,5.5)
surface:translate(0,-0.5,-5.5)
surface:set_material(mat2)

lb = gr.nh_cylinder('lb',{0,0,0},0.5,-2,2)
legs:add_child(lb)
lb:rotate('X',90)
lb:translate(3,-2,-2.5)
lb:set_material(mat3)

rb = gr.nh_cylinder('rb',{0,0,0},0.5,-2,2)
legs:add_child(rb)
rb:rotate('X',90)
rb:translate(-3,-2,-2.5)
rb:set_material(mat3)

lf = gr.nh_cylinder('lf',{0,0,0},0.5,-2,2)
legs:add_child(lf)
lf:rotate('X',90)
lf:translate(3,-2,2.5)
lf:set_material(mat3)

rf = gr.nh_cylinder('rf',{0,0,0},0.5,-2,2)
legs:add_child(rf)
rf:rotate('X',90)
rf:translate(-3,-2,2.5)
rf:set_material(mat3)



lights = {
    gr.light({10, 30.0, 10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-10, 30.0, 10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({10, 30.0, -10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-10, 30.0, -10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
}

gr.render(scene_root, 'table.png', 500, 500,
    {0, 7,-15}, {0, 0, 0}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, lights)
