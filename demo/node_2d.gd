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
	print(Example.test_static2(1))
	print(example.test_array())
	print("example.varargs_func_nv" ,example.varargs_func_nv("1","2","3"))
	print(x.id)


func _on_button_pressed():
	test()
