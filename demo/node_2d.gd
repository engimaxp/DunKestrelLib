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

func _ready():
	pass

var start_d
var end_d
var lines = {}

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
			var l = LINE.instantiate()
			l.add_point(start_d.position)
			l.add_point(end_d.position)
			
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
	print(graph.dijkstraAlgorithm(id))

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
