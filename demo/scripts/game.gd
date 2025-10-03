extends Node2D

func delete_game():
	var children = get_node("/root/game").get_children()
	for child in children:
		child.queue_free()

func exit_to_menu():
	delete_game()
	get_tree().change_scene_to_file("res://scenes/main_menu.tscn")

func win():
	delete_game()
	get_tree().change_scene_to_file("res://scenes/win.tscn")
