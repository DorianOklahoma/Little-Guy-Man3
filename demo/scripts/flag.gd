extends Node2D

@onready var game : Node2D = get_node("/root/game")

func _on_area_2d_body_entered(body: Node2D) -> void:
	if body.is_in_group("player"):
		print("Player has reached the end")
		game.win()
