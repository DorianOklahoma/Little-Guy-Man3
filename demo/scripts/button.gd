extends Node2D

@onready var interactive_map = get_node("../interactive_map")
var active: bool = false

func _ready():
	interactive_map.visible = false
	interactive_map.collision_enabled = false
	$AnimatedSprite2D.play("off")

func interact():
	active = !active

	if active:
		$AnimatedSprite2D.play("on")
		interactive_map.visible = true
		interactive_map.collision_enabled = true
	else:
		$AnimatedSprite2D.play("off")
		interactive_map.visible = false
		interactive_map.collision_enabled = false
