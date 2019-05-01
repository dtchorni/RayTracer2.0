
mat1 = gr.material({0.7,0.7,0.7},{0.5,0.5,0.5},0.5)
mat2 = gr.material({0.5,0.5,0.5},{0.3,0.3,0.3},0.3)

scene_root = gr.node('root')

couch = gr.node('couch')
scene_root:add_child(couch)

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





lights = {
    gr.light({10, 30.0, 10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-10, 30.0, 10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({10, 30.0, -10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-10, 30.0, -10}, {0.9, 0.9, 0.9}, {1, 0, 0}),
}

gr.render(scene_root, 'couch.png', 500, 500,
    {5, 7,-20}, {0, 0, 0}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, lights)
