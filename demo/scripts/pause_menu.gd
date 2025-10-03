extends Control

# Cooldown to avoid rapid pause/unpause
var can_toggle := true
var toggle_cooldown := 0.2  # seconds
var toggle_timer := 0.0

func _ready() -> void:
	$AnimationPlayer.play("RESET")

func resume():
	get_tree().paused = false
	$AnimationPlayer.play_backwards("new_animation")
	_start_cooldown()

func paused():
	get_tree().paused = true
	$AnimationPlayer.play("new_animation")
	_start_cooldown()

func _start_cooldown() -> void:
	toggle_timer = 0.0
	can_toggle = false

func _process(delta: float) -> void:
	if !can_toggle:
		toggle_timer += delta
		if toggle_timer >= toggle_cooldown:
			can_toggle = true

	_check_escape_input()

func _check_escape_input() -> void:
	if can_toggle and Input.is_action_just_pressed("escape"):
		if get_tree().paused:
			resume()
		else:
			paused()

func _on_resume_pressed() -> void:
	resume()

func _on_restart_pressed() -> void:
	resume()
	get_tree().reload_current_scene()

func _on_menu_pressed() -> void:
	get_node("/root/game").exit_to_menu()
