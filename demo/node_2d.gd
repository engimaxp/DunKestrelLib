extends Node2D
#
#func _ready():
#	var x = ExampleRef.new()
#	print(x.id)
@onready var label = $Label
@onready var example:Example = $Example as Example
@onready var timer = $Timer
@onready var line_edit = $LineEdit
@onready var line_edit_2 = $LineEdit2

var can_press = true

const DOT = preload("res://dot.tscn")
const LINE = preload("res://line_2d.tscn")
const CLABEL = preload("res://label.tscn")
var graph = DunGraph.new()

var vid = 1;

var start_d
var end_d
var lines = {}
var selected_l
func dot_press(button_index,d):
	print(button_index,d)
	if can_press:
		can_press = false
		timer.start()
	if button_index == MOUSE_BUTTON_LEFT:
		start_d = d
	if button_index == MOUSE_BUTTON_RIGHT:
		if start_d != null and end_d != start_d:
			end_d = d
			if lines.has(Vector2i(start_d.id,end_d.id)):
				var l = lines[Vector2i(start_d.id,end_d.id)]
				selected_l = l[0]
				selected_l.line_color = Color.DARK_TURQUOISE
			else:
				selected_l = null
				var l = LINE.instantiate()
				l.add_point(start_d.position)
				l.add_point(end_d.position)
				l.start_end = Vector2i(start_d.id,end_d.id)
				var weight = int(line_edit.text) if line_edit.text.is_valid_int() else 1
				var cl = CLABEL.instantiate()
				cl.text = str(weight)
				cl.position = (start_d.position + end_d.position) / 2.0
				add_child(cl)
				add_child(l)
				graph.addEdge(Vector3i(start_d.id,end_d.id,weight))
				lines[Vector2i(start_d.id,end_d.id)] = [l,cl]
				start_d = null
				end_d = null
			
	if button_index == MOUSE_BUTTON_MIDDLE:
		graph.removeNode(d.id)
		for l in lines.keys():
			if l.x == d.id or l.y == d.id:
				lines[l][0].queue_free()
				lines[l][1].queue_free()
				lines.erase(l)
		d.queue_free()

var addable_dot = true
func set_addable_dot(val):
	addable_dot = val

func _unhandled_input(_event):
	if _event is InputEventMouseButton and _event.is_pressed() \
		and _event.button_index == MOUSE_BUTTON_RIGHT:
		if can_press and addable_dot:
			can_press = false
			timer.start()
			var d = DOT.instantiate()
			d.id = vid
			vid += 1
			d.position = _event.position
			add_child(d)
			graph.addNode(d.id)
			d.pressed.connect(dot_press.bind(d))
			d.enter.connect(set_addable_dot.bind(false))
			d.exit.connect(set_addable_dot.bind(true))
	if Input.is_action_just_pressed("ui_accept"):
		test(int(line_edit_2.text))

func new_test(id):
	var dic = graph.dijkstraAlgorithm(id)
	var kdic = {}
	for k in dic.keys():
		if dic[k]["distance"] <= 0 or dic[k]["distance"] >= 9999:
			continue
		for v in dic[k]["edges"]:
			kdic[v] = true
	for l in lines.values():
		l[0].line_color = Color.WHITE
	for k in kdic.keys():
		lines[k][0].line_color = Color.YELLOW_GREEN

func remove_Edge(start,end):
	var v = Vector2i(start,end)
	for x in lines[v]:
		x.queue_free()
	lines.erase(v)
	graph.removeEdge(Vector2i(start,end))

func test(id):
	var start_time = Time.get_ticks_usec()
	new_test(id)
	var end_time = Time.get_ticks_usec()
	print("%f us" % (end_time - start_time))
#	var x = ExampleRef.new()
#	label.text = str(Example.test_static(2,4))
#	print(Example.test_static(2,4))
#	print(Example.test_static2(2,[1,2,3,4,5],[
#		Vector3i(1,2,5),
#		Vector3i(1,3,2),
#		Vector3i(3,2,2),
#		Vector3i(3,4,5),
#		Vector3i(2,4,4),
#		Vector3i(2,5,2),
#		Vector3i(4,5,3),
#	]))
#	print(example.test_array())
#	print("example.varargs_func_nv" ,example.varargs_func_nv("1","2","3"))
#	print(x.id)


func _on_button_pressed():
	test(int(line_edit_2.text))


func _on_timer_timeout():
	can_press = true


func _on_minus_pressed():
	var ov = int(line_edit.text)
	ov -= 1
	line_edit.text = str(ov)


func _on_plus_pressed():
	var ov = int(line_edit.text)
	ov += 1
	line_edit.text = str(ov)


func _on_button_2_pressed():
	get_tree().change_scene_to_file("res://node_2d_2.tscn")


func _on_button_3_pressed():
	if is_instance_valid(selected_l):
		var se = selected_l.start_end
		var weight = int(line_edit.text) if line_edit.text.is_valid_int() else 1
		lines[se][1].text  = str(weight)
		graph.addEdge(Vector3i(se.x,se.y,weight))
