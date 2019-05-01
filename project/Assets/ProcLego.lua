
mat = gr.material({0.7,0.7,0.7},{0.5,0.5,0.5},0.5)
white = gr.material({1.0,1.0,1.0},{0.8,0.8,0.8},10)
green = gr.material({0,1.0,0},{0.1,0.8,0.1},10)
red = gr.material({1.0,0,0},{0.8,0.1,0.1},10)
blue = gr.material({0,0,1.0},{0.1,0.1,0.8},10)

scene_root = gr.node('root')

proc = gr.proceduralLego('proc',10,10,1,
    {{1,1}},
    {white,green,red,blue},
    true
)
proc:scale(1/3,1/3,1/3)
--proc:rotate('Y',0)

scene_root:add_child(proc)


lights = {
    gr.light({15, 30.0, 15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-15, 30.0, 15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({15, 30.0, -15}, {0.9, 0.9, 0.9}, {1, 0, 0}),
    gr.light({-15, 30.0, -15}, {0.9, 0.9, 0.9}, {1, 0, 0})
}

gr.render(scene_root, 'proc.png', 500, 500,
    {0, 14,-30}, {0, 0, 0}, {0, 1, 0}, 50,
    {0.3, 0.3, 0.3}, lights)
