
grey = gr.material({0.4,0.4,0.4},{0.0,0.0,0.0},0)
beige = gr.material({0.5,0.5,0.7},{0,0,0},0)
white = gr.material({1.0,1.0,1.0},{0,0,0},0)

red = gr.material({1.0,0.0,0.0},{1.0,0.5,0.5},88)
purple = gr.material({1.0,0.0,1.0},{0.5,0.5,0.5},100)
blue = gr.material({0,0.0,1.0},{0.2,0.2,0.5},75)

scene = gr.node('scene')


floor = gr.mesh('floor','plane.obj')
scene:scale(3.0,1.0,3.0)
scene:add_child(floor)
floor:set_material(grey)

mickey = gr.mesh('mickey', 'mickey.obj')
mickey:set_material(purple)
mickey:rotate('Y',-90)
mickey:rotate('Z',-90)
mickey:rotate('X',20)
mickey:translate(-0.489,1.0,-0.955)
mickey:scale(1/3,1,1/3)
scene:add_child(mickey)

cow = gr.mesh('cow1','cow.obj')
scene:add_child(cow)
cow:scale(1/3,1,1/3)
cow:set_material(blue)
cow:scale(1/8,1/8,1/8)
cow:rotate('Y',-90)
cow:translate(0,0.45,-0.35)
cow:rotate('Y',55)

cow = gr.mesh('cow1','cow.obj')
scene:add_child(cow)
cow:scale(1/3,1,1/3)
cow:set_material(blue)
cow:scale(1/8,1/8,1/8)
cow:rotate('Y',-90)
cow:translate(0,0.45,-0.35)
cow:rotate('Y',-55)

cow = gr.mesh('cow1','cow.obj')
scene:add_child(cow)
cow:scale(1/3,1,1/3)
cow:set_material(blue)
cow:scale(1/8,1/8,1/8)
cow:rotate('Y',-90)
cow:translate(0,0.45,-0.35)
--cow:rotate('Y',30)

ceil = gr.mesh('ceil','plane.obj')
floor:add_child(ceil)
ceil:rotate('X',180)
ceil:translate(0,2,0)
ceil:set_material(white)


light_housing= gr.mesh('ceil light','cylinder.obj')
ceil:add_child(light_housing)
light_housing:scale(1/3,1.0,1/3)
light_housing:scale(1/4,1/8,1/4)
light_housing:translate(0,1.9,0)
light_housing:set_material(red)

l1 = gr.nh_sphere('l1',{0,0,0},0.1)
l1:scale(1/3,1.0,1/3)
l1:scale(1/2,1/2,1/2)
l1:translate(0,1.8,0.0)
--light_housing:add_child(l1)
l1:set_material(purple)


wall = gr.mesh('back wall','plane.obj')
floor:add_child(wall)
wall:rotate('X', 90)
wall:translate(0,1,-1)
wall:set_material(beige)

wall2 = gr.mesh('side wall','plane.obj')
floor:add_child(wall2)
wall2:rotate('X', 90)
wall2:rotate('Y',90)
wall2:translate(-1,1,0)
wall2:set_material(beige)

wall3 = gr.mesh('side wall','plane.obj')
floor:add_child(wall3)
wall3:rotate('X', 90)
wall3:rotate('Y',270)
wall3:translate(1,1,0)
wall3:set_material(beige)

gr.render(scene,
    'sample.png', 1000, 1000,
    {-1.2, 1, 4.2}, {0, 0.5, 0.5}, {0, 1, 0}, 50,
    {0.4, 0.4, 0.4}, {gr.light({0, 1.89, 0}, {0.8, 0.3, 0.3}, {1, 0, 0.})})