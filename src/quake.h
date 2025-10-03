#ifndef QUAKE_H
#define QUAKE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// Create new quake class
class Quake : public Sprite2D {
    GDCLASS(Quake, Sprite2D);

private:
    // Variables for shaking
    bool shake_enabled = false;
    float shake_intensity = 10.0f;
    float shake_speed = 30.0f;
    float shake_duration = 0.5f;
    float shake_elapsed_time = 0.0f;

    // Save default position
    Vector2 original_position;

    // Variables for pulsing
    bool pulse_enabled = false;
    float pulse_intensity = 0.1f;
    float pulse_speed = 5.0f;
    float pulse_duration = 0.0f; // 0 = infinite
    float pulse_elapsed_time = 0.0f;

    // Save default scale
    Vector2 original_scale;

public:
    static void _bind_methods();

    void _process(double delta) override;

    // Shakeing functions
    void start_shake();
    void stop_shake();
    void set_shake_enabled(bool val);
    bool get_shake_enabled() const;

    // Pulsing functions
    void start_pulse();
    void stop_pulse();
    void set_pulse_enabled(bool val);
    bool get_pulse_enabled() const;

    // Setters/Getters for shake properties
    void set_shake_intensity(float val);
    float get_shake_intensity() const;
    void set_shake_speed(float val);
    float get_shake_speed() const;
    void set_shake_duration(float val);
    float get_shake_duration() const;

    // Setters/Getters for pulse properties
    void set_pulse_intensity(float val);
    float get_pulse_intensity() const;
    void set_pulse_speed(float val);
    float get_pulse_speed() const;
    void set_pulse_duration(float val);
    float get_pulse_duration() const;

    void _ready() override;

};

#endif