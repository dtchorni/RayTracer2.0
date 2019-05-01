

wall_col = gr.material({0.5,0.9,0.9},{0.4,0.8,0.8},15.0)
white = gr.material({1.0,1.0,1.0}, {1.0,1.0,1.0},5.1)
couch = gr.material({0.5,0.6,0.5},{0.4,0.5,0.4},5)
mat1 =  couch
mat2 = couch
leg_col = gr.material({0.1,0.8,0.1},{0.2,0.6,0.2},5.0)
top_col = gr.material({0.9,0.9,0.1},{0.8,0.8,0.2},2.5)
flat_col = gr.material({0,0.0,1.0},{0.1,0.1,0.9},10)
floor_col = gr.material({0.6,0.2,0.4},{0.4,0.2,0.4},15)
chair_col = gr.material({0.8,0.6,0.5},{0.6,0.5,0.4},1)

white = gr.material({1.0,1.0,1.0},{0.8,0.8,0.8},10)
green = gr.material({0,1.0,0},{0.1,0.8,0.1},10)
yellow = gr.material({1.0,1.0,0},{0.8,0.8,0.1},10)
red = gr.material({1.0,0,0},{0.8,0.1,0.1},10)
blue = gr.material({0,0,1.0},{0.1,0.1,0.8},10)



scene_root = gr.node('root')

walls = gr.node('walls')
walls:translate(-50,0,50)
scene_root:add_child(walls)

bwall = gr.nh_box('back',{0,0,0},50)
walls:add_child(bwall)
bwall:scale(2,1,1/10)
bwall:set_material(wall_col)

lwall = gr.nh_box('left',{0,0,0},50)
walls:add_child(lwall)
lwall:scale(2,1,1/10)
lwall:rotate('Y',90)
lwall:translate(0,0,5)
lwall:set_material(wall_col)

rwall = gr.nh_box('right',{0,0,0},50)
walls:add_child(rwall)
rwall:scale(2,1,1/10)
rwall:rotate('Y',90)
rwall:translate(100,0,5)
rwall:set_material(wall_col)

fwall = gr.nh_box('front',{0,0,0},50)
walls:add_child(fwall)
fwall:scale(2,1,1/10)
--fwall:rotate('Y',90)
fwall:translate(0,0,-100)
fwall:set_material(wall_col)

ceil = gr.nh_box('ceil',{0,0,0},50)
walls:add_child(ceil)
ceil:scale(2,2,1/10)
ceil:rotate('X',90)
ceil:translate(0,50,-100)
ceil:set_material(white)

floor = gr.nh_box('floor',{0,0,0},50)
walls:add_child(floor)
floor:scale(2,2,1/10)
floor:rotate('X',90)
floor:translate(0,0,-100)
floor:set_material(floor_col)


couch = gr.node('couch')
scene_root:add_child(couch)
couch:scale(5,5,5)
couch:translate(20,3.75,35)


bottom = gr.node('bottom')
couch:add_child(bottom)

cushions = gr.node('cushions')
couch:add_child(cushions)
cushions:scale(9/10,9/10,1.2)
cushions:translate(2.79,0.5,-0.5)

bottom0 = gr.nh_box('botttom0',{-4.2,-4.2,-4.2},8.4)
bottom:add_child(bottom0)
bottom0:scale(1.0,1/2.54,1/2.54)
bottom0:scale(1.0,1/3,1.0)
bottom0:set_material(mat1)

left = gr.nh_box('left',{-0.505,-0.505,0.505},1.1)
bottom:add_child(left)
left:scale(1.0,2,3.5)
left:translate(4.2,0.3,-3.7)
left:set_material(mat1)

right = gr.nh_box('right',{-0.505,-0.505,0.505},1.1)
bottom:add_child(right)
right:scale(1.0,2,3.5)
right:translate(-4.2,0.3,-3.7)
right:set_material(mat1)

back = gr.nh_box('back',{-4.2,-4.2,-4.2},8.4)
bottom:add_child(back)
back:scale(1.0,1/2.54,1/2.54)
back:scale(1.0,1,1/6)
back:translate(0,1.0,1.7)
back:set_material(mat1)

l_arm = gr.nh_cylinder('l_arm',{0,0,0},0.75,-1.7,1.7)
bottom:add_child(l_arm)
l_arm:scale(1.0,1.0,1.2)
l_arm:translate(4.3,1.0,0)
l_arm:set_material(mat1)

r_arm = gr.nh_cylinder('r_arm',{0,0,0},0.75,-1.7,1.7)
bottom:add_child(r_arm)
r_arm:scale(1.0,1.0,1.2)
r_arm:translate(-4.3,1.0,0)
r_arm:set_material(mat1)

bl = gr.nh_cylinder('bl',{0,0,0},0.5,-1.5,1.5)
cushions:add_child(bl)
bl:scale(3.0,1.2,1.0)
bl:rotate('Y',90)
bl:set_material(mat2)

tl = gr.nh_cylinder('tl',{0,0,0},0.5,-1.5,1.5)
cushions:add_child(tl)
tl:scale(3.0,1.2,1.0)
tl:rotate('Y',90)
tl:rotate('X',95)
tl:translate(0,1.2,1.0)
tl:set_material(mat2)

bm = gr.nh_cylinder('bm',{0,0,0},0.5,-1.5,1.5)
cushions:add_child(bm)
bm:scale(3.0,1.2,1.0)
bm:rotate('Y',90)
bm:translate(-3.1,0,0)
bm:set_material(mat2)

tm = gr.nh_cylinder('tm',{0,0,0},0.5,-1.5,1.5)
cushions:add_child(tm)
tm:scale(3.0,1.2,1.0)
tm:rotate('Y',90)
tm:rotate('X',95)
tm:translate(-3.1,1.2,1.0)
tm:set_material(mat2)


br = gr.nh_cylinder('br',{0,0,0},0.5,-1.5,1.5)
cushions:add_child(br)
br:scale(3.0,1.2,1.0)
br:rotate('Y',90)
br:translate(-6.2,0,0)
br:set_material(mat2)

tr = gr.nh_cylinder('tr',{0,0,0},0.5,-1.5,1.5)
cushions:add_child(tr)
tr:scale(3.0,1.2,1.0)
tr:rotate('Y',90)
tr:rotate('X',95)
tr:translate(-6.2,1.2,1.0)
tr:set_material(mat2)



table = gr.node('table')
scene_root:add_child(table)
table:scale(2,1.5,2)
table:translate(27,6.4,11)

legs = gr.node('legs')
table:add_child(legs)

t = gr.node('table')
table:add_child(t)

flat = gr.node('flat')
table:add_child(flat)

t0 = gr.nh_cylinder('t0',{0,0,0},1.0,-3.0,3.0)
t:add_child(t0)
t0:scale(4,0.7,1.0)
t0:set_material(top_col)


surface = gr.nh_box('surface', {-0.5,0.5,0.5},1.0)
flat:add_child(surface)
surface:scale(5.5,1.0,5.5)
surface:translate(0,-0.5,-5.5)
surface:set_material(flat_col)

lb = gr.nh_cylinder('lb',{0,0,0},0.5,-2,2)
legs:add_child(lb)
lb:rotate('X',90)
lb:translate(3,-2,-2.5)
lb:set_material(leg_col)

rb = gr.nh_cylinder('rb',{0,0,0},0.5,-2,2)
legs:add_child(rb)
rb:rotate('X',90)
rb:translate(-3,-2,-2.5)
rb:set_material(leg_col)

lf = gr.nh_cylinder('lf',{0,0,0},0.5,-2,2)
legs:add_child(lf)
lf:rotate('X',90)
lf:translate(3,-2,2.5)
lf:set_material(leg_col)

rf = gr.nh_cylinder('rf',{0,0,0},0.5,-2,2)
legs:add_child(rf)
rf:rotate('X',90)
rf:translate(-3,-2,2.5)
rf:set_material(leg_col)



chair = gr.node('chair')
scene_root:add_child(chair)
chair:scale(2,2,2)
chair:rotate('Y',90)
chair:translate(38,3,-5)

bottom = gr.node('bottom')
chair:add_child(bottom)

lf = gr.nh_cylinder('lf',{0,0,0},0.2,-2.3,2.3)
bottom:add_child(lf)
lf:rotate('X',90)
lf:translate(2.3,0,-2.6)
lf:set_material(chair_col)

rf = gr.nh_cylinder('rf',{0,0,0},0.2,-2.3,2.3)
bottom:add_child(rf)
rf:rotate('X',90)
rf:translate(-2.3,0,-2.6)
rf:set_material(chair_col)


rb = gr.nh_cylinder('rb',{0,0,0},0.2,-2.3,2.3)
bottom:add_child(rb)
rb:rotate('X',90)
rb:translate(-2.3,0,2.6)
rb:set_material(chair_col)

lb = gr.nh_cylinder('lb',{0,0,0},0.2,-2.3,2.3)
bottom:add_child(lb)
lb:rotate('X',90)
lb:translate(2.3,0,2.6)
lb:set_material(chair_col)


seat = gr.nh_cylinder('seat',{0,0,0},0.3,-2.5,2.5)
bottom:add_child(seat)
seat:set_material(chair_col)
seat:scale(10.6,1.0,1.0)
seat:rotate('Y',90)
seat:translate(0,2.3,0)

back=gr.node('back')
chair:add_child(back)
back:translate(0,5.8,2.6)

back0 = gr.nh_cylinder('back0',{0,0,0},0.2,-2.6,2.6)
back:add_child(back0)
back0:set_material(chair_col)
back0:rotate('X',90)
back0:translate(2.2,-0.85,0)

back1 = gr.nh_cylinder('back1',{0,0,0},0.2,-2.6,2.6)
back:add_child(back1)
back1:set_material(chair_col)
back1:rotate('X',90)
back1:translate(-2.2,-0.85,0)

flat = gr.nh_cylinder('flat',{0,0,0},0.3,-2.3,2.3)
back:add_child(flat)
flat:set_material(chair_col)
flat:scale(7.0,1.0,1.0)
flat:rotate('Y',90)
flat:rotate('X',90)
flat:translate(0,0,-0.29)

lego = gr.node('alllego')
lego:scale(1/15,1/15,1/15)
lego:translate(22,8.1,7)
scene_root:add_child(lego)

proc = gr.proceduralLego('proc',3,3,3,
    {{1,1}},
    {white,green,red,yellow},
    true
)

lego:add_child(proc)

proc2 = gr.proceduralLego('proc',4,2,9,
    {{1,1}},
    {white,green,red,yellow},
    false
)
proc2:translate(20,0,36)
lego:add_child(proc2)

proc3 = gr.proceduralLego('proc2',5,3,20,
    {{1,1}},
    {white,green,red,yellow},
    false
)
proc3:translate(40,0,86)
lego:add_child(proc3)

piece=gr.lego('p0',1,1,false)
piece:rotate('X',90)
piece:rotate('Y',45)
piece:translate(-5,0,50)
lego:add_child(piece)
piece:set_material(red)


lights = {
--    gr.light({15, 30.0, 15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
--    gr.light({-15, 30.0, 15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
--    gr.light({15, 30.0, -15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({0, 44, 0}, {0.9, 0.9, 0.9}, {1, 0, 0})
}

gr.render(scene_root, 'scene.png', 1000, 1000,
--    {0, 200,0}, {0, 0, 0}, {0, 0, 1}, --birds eye
--    {-45,30,-45}, {0,30,0},{0,1,0}, --corner
    {0,15,-2},{5,15,0},{0,1,0}, --table view
    50, {0.3, 0.3, 0.3}, lights)
