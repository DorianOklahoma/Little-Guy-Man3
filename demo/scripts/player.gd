extends CharacterBody2D

@onready var animation: AnimatedSprite2D = $Quake/AnimatedSprite2D

const SPEED = 300.0
const JUMP_VELOCITY = -500.0
var is_animation_locked = false
var lives = 2

func _process(_delta: float) -> void:
	if lives <= 0:
		get_tree().reload_current_scene()
	
	if Input.is_action_just_pressed("interact"):
		interact()

func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		velocity += get_gravity() * delta
	# Handle jump.
	if Input.is_action_just_pressed("move_up") and is_on_floor():
		velocity.y = JUMP_VELOCITY
	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var direction := Input.get_axis("move_left", "move_right")

	if direction:
		velocity.x = direction * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
	play_movement_animation()
	move_and_slide()

func play_movement_animation():
	if is_animation_locked:
		return
	elif velocity.x > 0:
		animation.play("walk_right")
	elif velocity.x < 0:
		animation.play("walk_left")
	elif velocity.y > 0:
		animation.play("down")
	elif velocity.y < 0:
		animation.play("up")
	else:
		animation.play("idle")

func get_damage():
	lives -= 1
	print("player was damaged")
	animation.play("damage")
	is_animation_locked = true
	await get_tree().create_timer(0.2).timeout
	is_animation_locked = false

func get_life():
	lives += 1

func interact():
	var overlapping_objects = $interactionArea.get_overlapping_areas()
	
	for area in overlapping_objects:
		var parent = area.get_parent()
		if 'interact' in parent:
			parent.interact()
