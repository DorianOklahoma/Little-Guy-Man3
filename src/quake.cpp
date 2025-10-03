#include "quake.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <cmath>

using namespace godot;

void Quake::_bind_methods() {
    // Shake methods
    ClassDB::bind_method(D_METHOD("start_shake"), &Quake::start_shake);
    ClassDB::bind_method(D_METHOD("stop_shake"), &Quake::stop_shake);
    ClassDB::bind_method(D_METHOD("set_shake_enabled", "val"), &Quake::set_shake_enabled);
    ClassDB::bind_method(D_METHOD("get_shake_enabled"), &Quake::get_shake_enabled);

    // Shake properties
    ClassDB::bind_method(D_METHOD("set_shake_intensity", "val"), &Quake::set_shake_intensity);
    ClassDB::bind_method(D_METHOD("get_shake_intensity"), &Quake::get_shake_intensity);
    ClassDB::bind_method(D_METHOD("set_shake_speed", "val"), &Quake::set_shake_speed);
    ClassDB::bind_method(D_METHOD("get_shake_speed"), &Quake::get_shake_speed);
    ClassDB::bind_method(D_METHOD("set_shake_duration", "val"), &Quake::set_shake_duration);
    ClassDB::bind_method(D_METHOD("get_shake_duration"), &Quake::get_shake_duration);

    // Add shake properties
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "shake_enabled"), "set_shake_enabled", "get_shake_enabled");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "shake_intensity"), "set_shake_intensity", "get_shake_intensity");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "shake_speed"), "set_shake_speed", "get_shake_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "shake_duration"), "set_shake_duration", "get_shake_duration");

    // Add shake signals
    ADD_SIGNAL(MethodInfo("quake_started"));
    ADD_SIGNAL(MethodInfo("quake_finished"));

    // Pulse methods
    ClassDB::bind_method(D_METHOD("start_pulse"), &Quake::start_pulse);
    ClassDB::bind_method(D_METHOD("stop_pulse"), &Quake::stop_pulse);
    ClassDB::bind_method(D_METHOD("set_pulse_enabled", "val"), &Quake::set_pulse_enabled);
    ClassDB::bind_method(D_METHOD("get_pulse_enabled"), &Quake::get_pulse_enabled);

    // Pulse properties
    ClassDB::bind_method(D_METHOD("set_pulse_intensity", "val"), &Quake::set_pulse_intensity);
    ClassDB::bind_method(D_METHOD("get_pulse_intensity"), &Quake::get_pulse_intensity);
    ClassDB::bind_method(D_METHOD("set_pulse_speed", "val"), &Quake::set_pulse_speed);
    ClassDB::bind_method(D_METHOD("get_pulse_speed"), &Quake::get_pulse_speed);
    ClassDB::bind_method(D_METHOD("set_pulse_duration", "val"), &Quake::set_pulse_duration);
    ClassDB::bind_method(D_METHOD("get_pulse_duration"), &Quake::get_pulse_duration);

    // Add pulse properties
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "pulse_enabled"), "set_pulse_enabled", "get_pulse_enabled");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pulse_intensity"), "set_pulse_intensity", "get_pulse_intensity");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pulse_speed"), "set_pulse_speed", "get_pulse_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pulse_duration"), "set_pulse_duration", "get_pulse_duration");

    // Add pulse methods
    ADD_SIGNAL(MethodInfo("pulse_started"));
    ADD_SIGNAL(MethodInfo("pulse_finished"));
}

// Funtion to toggle shake
void Quake::set_shake_enabled(bool val) {
	// Check of value is already set
    if (shake_enabled == val) {
    	return;
    }
    // Update shake
    shake_enabled = val;
    // Toggle shake
    if (shake_enabled) {
        start_shake();
    }
    else {
        stop_shake();
    }
}

// Function to return shake toggle
bool Quake::get_shake_enabled() const {
    return shake_enabled;
}

// Function to start shake
void Quake::start_shake() {
	// Set toggle to true
    shake_enabled = true;
    // Reset time shaking
    shake_elapsed_time = 0.0f;
    // Start process
    set_process(true);
}

// Function to stop shake
void Quake::stop_shake() {
    if (shake_enabled) {
    	// Set toggle to false
        shake_enabled = false;
        // Reset to starting possition
        set_position(original_position);
        // Stop process if pulse is disabled
        if (!pulse_enabled) {
            set_process(false);
        }
        // Send finished signal
        emit_signal("quake_finished");
    }
}

void Quake::set_shake_intensity(float val) {
    shake_intensity = val;
}

float Quake::get_shake_intensity() const {
    return shake_intensity;
}

void Quake::set_shake_speed(float val) {
    shake_speed = val;
}

float Quake::get_shake_speed() const {
    return shake_speed;
}

void Quake::set_shake_duration(float val) {
    shake_duration = val;
}

float Quake::get_shake_duration() const {
    return shake_duration;
}

// Function to toggle pulse
void Quake::set_pulse_enabled(bool val) {
	// Check of value is already set
    if (pulse_enabled == val) return;
    // Update pulse
    pulse_enabled = val;
    // Toggle pulse
    if (pulse_enabled) {
        start_pulse();
    } else {
        stop_pulse();
    }
}

// Function to return shake toggle
bool Quake::get_pulse_enabled() const {
    return pulse_enabled;
}

// Function to start pulse
void Quake::start_pulse() {
	// Set toggle to true
    if (!pulse_enabled) {
        pulse_enabled = true;
    }
    // Reset time pulsing
    pulse_elapsed_time = 0.0f;
    // Save original scale
    original_scale = get_scale();
    // Send start signal
    emit_signal("pulse_started");
    // Start process
    set_process(true);
}

// Function to stop pulse
void Quake::stop_pulse() {
    if (pulse_enabled) {
    	// Set toggle to false
        pulse_enabled = false;
        // Reset to starting scale
        set_scale(original_scale);
        // Send finished signal
        emit_signal("pulse_finished");
        // Stop process if shake is disabled
        if (!shake_enabled) {
            set_process(false);
        }
    }
}

void Quake::set_pulse_intensity(float val) {
    pulse_intensity = val;
}

float Quake::get_pulse_intensity() const {
    return pulse_intensity;
}

void Quake::set_pulse_speed(float val) {
    pulse_speed = val;
}

float Quake::get_pulse_speed() const {
    return pulse_speed;
}

void Quake::set_pulse_duration(float val) {
    pulse_duration = val;
}

float Quake::get_pulse_duration() const {
    return pulse_duration;
}

// Process creation
void Quake::_process(double delta) {
	// Reset process
    bool need_process = false;
    // Handle shaking
    if (shake_enabled) {
    	// Add to runtime
        shake_elapsed_time += delta;
        // Stop shake if elapsed time is greater than duration
        	// Dont stop if duration is 0
        if (shake_duration > 0.0f && shake_elapsed_time >= shake_duration) {
            stop_shake();
        }
        else {
        	// Get random offset for shake effect
        		// Multiply by intensity for intensity setting
            Vector2 offset = Vector2(
	            UtilityFunctions::randf_range(-1.0f, 1.0f),
	            UtilityFunctions::randf_range(-1.0f, 1.0f)
	        ).normalized() * shake_intensity * (0.5f + 0.5f);
            // Set new possition for shake
            set_position(original_position + offset);
            // Set the process to continue running
            need_process = true;
        }
    }

    // Handle pulsing
    if (pulse_enabled) {
    	// Add to runtime
        pulse_elapsed_time += delta;
        // Stop pulse if elapsed time is greater than duration
        	// Donst stop if duration is 0
        if (pulse_duration > 0.0f && pulse_elapsed_time >= pulse_duration) {
            stop_pulse();
        }
        else {
        	// Get pulse factor
            float scale_factor = 1.0f + pulse_intensity * std::sin(pulse_elapsed_time * pulse_speed * 2.0f * Math_PI);
            // Set scale for pulse
            set_scale(original_scale * scale_factor);
            // Set the process to continue running
            need_process = true;
        }
    }
    // Stop process if no method in use
    if (!need_process) {
        set_process(false);

        // Reset position
        if (!shake_enabled)
            set_position(original_position);

        // Reset scale
        if (!pulse_enabled)
            set_scale(original_scale);
    }
}

void Quake::_ready() {
    original_position = get_position();
    original_scale = get_scale();
}

