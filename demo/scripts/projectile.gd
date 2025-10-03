extends CharacterBody2D

@export var SPEED = 200

var direction : float
var spawnPosition : Vector2
var spawnRotation : float
var zIndex : int

func _ready() -> void:
	global_position = spawnPosition
	global_rotation = spawnRotation
	z_index = zIndex

func _physics_process(_delta: float) -> void:
	velocity = Vector2(-SPEED, 0).rotated(direction)
	move_and_slide()


func _on_area_2d_body_entered(body: Node2D) -> void:
	if 'get_damage' in body:
		body.get_damage()
	queue_free()


func _on_despawn_timer_timeout() -> void:
	queue_free()
