extends Node2D
#
#func _ready():
#	var x = ExampleRef.new()
#	print(x.id)
@onready var label = $Label
@onready var example:Example = $Example as Example

func _unhandled_input(_event):
	if Input.is_action_just_pressed("ui_accept"):
		test()
		
func test():
	var x = ExampleRef.new()
	label.text = str(Example.test_static(2,4))
	print(Example.test_static(2,4))
	var start_time = Time.get_ticks_usec()
	print(Example.test_static2(2,[1,2,3,4,5],[
		Vector3i(1,2,5),
		Vector3i(1,3,2),
		Vector3i(3,2,2),
		Vector3i(3,4,5),
		Vector3i(2,4,4),
		Vector3i(2,5,2),
		Vector3i(4,5,3),
	]))
	var end_time = Time.get_ticks_usec()
	print("%f us" % (end_time - start_time))
	print(example.test_array())
	print("example.varargs_func_nv" ,example.varargs_func_nv("1","2","3"))
	print(x.id)


func _on_button_pressed():
	test()
