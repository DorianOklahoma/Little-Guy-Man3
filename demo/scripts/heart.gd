extends Node2D


func _on_area_2d_body_entered(body: Node2D) -> void:
	if 'get_life' in body:
		body.get_life()
		queue_free()
