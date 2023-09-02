extends Node2D
@onready var label = $Label

signal pressed(button_index)
signal enter
signal exit

var id = 0:
	set(val):
		id = val
		if is_instance_valid(label):
			label.text = str(id)

func _ready():
	self.id = id

func _on_area_2d_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton and event.is_pressed():
		get_viewport().set_input_as_handled()
		pressed.emit(event.button_index)

func _on_area_2d_mouse_entered():
	enter.emit()
	
func _on_area_2d_mouse_exited():
	exit.emit()
