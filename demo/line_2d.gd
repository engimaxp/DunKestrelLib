extends Line2D

var start_end = Vector2i(-1,-1)

var line_color:Color = Color.WHITE:
	set(val):
		line_color = val
		if is_inside_tree():
			self.default_color = line_color

func _ready():
	self.line_color = line_color
