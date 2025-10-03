extends Node2D

@onready var main = get_tree().current_scene
@onready var projectile = load("res://scenes/projectile.tscn")
@onready var cooldown_timer: Timer = $cooldown
@onready var quaker: Quake = $Quake

@export var cooldown : float

func _ready() -> void:
	if cooldown != 0:
		cooldown_timer.wait_time = cooldown
		cooldown_timer.one_shot = true
		cooldown_timer.start()

func _physics_process(_delta: float) -> void:
	#rotation_degrees += 50 * delta"duration"
	pass

func shoot():
	var instance = projectile.instantiate()
	instance.direction = rotation
	instance.spawnPosition = global_position - Vector2(20, 0).rotated(rotation)
	instance.spawnRotation = rotation
	instance.zIndex = z_index - 1
	main.add_child.call_deferred(instance)

func interact():
	queue_free()


func _on_quake_quake_finished() -> void:
	shoot()
	cooldown_timer.start()


func _on_cooldown_timeout() -> void:
	cooldown_timer.stop()
	quaker.start_shake()
