#ifndef SHOT_H
#define SHOT_H

#include "core/object.h"
#include "core/reference.h"
#include "bullet_type.h"
#include "core/math/transform_2d.h"
#include "core/math/rect2.h"
#include "scene/resources/texture.h"

class Shot : public Object {
	GDCLASS(Shot, Object);
	
	int time;
	bool popped;
	float angle;
	float speed;
	float accel;
	float angaccel;
	float speed_max;
	float angle_max;
	
	Vector2 trig;
	Vector2 movement_vector;
	Vector2 position;
	bool speedChanged;
	void (*move_fxn)();
	
	/* gravity implementation?
	float grav_ang;
	float gravity;
	Vector2 grav_trig;
	*/

	protected:
		static void _bind_methods();
	
	public:
		void spawn();
		
		void update();
		
		void pop();
		bool is_popped();
		
		void _SetXYSpeed(const Vector2 &p_vector);
		void _SetSpeed(float s);
		void _SetAngle(float a);
		
		void _MovementA1(); //standard movement once movement vector is calculated, fastest
		void _MovementA2(); //constant speed acceleration
		void _MovementA3(); //constant angular acceleration, similar to Ax but does not switch back to A1
		void _MovementAx(); //recalculates trig and movement vector, set as move_fxn when angle (+ speed?) changes, slowest
		void _MovementAy(); //recalculates movement vector only, set as move_fxn when only speed changes (may be simpler to just use Ax?)
		
		void _MovementB2(); //constant x and y acceleration, changes movement vector every frame before A1
		//holy wow is B movement faster, huh... guess it's because it uses the movement vector directly and doesn't bother with trig
		
		void _ShotTask(Ref<Reference> scriptInstance);
		// May be different with new coroutine system?
		// https://godotengine.org/qa/21208/pass-a-gdscript-class-as-reference-in-a-cpp-module
		// https://docs.godotengine.org/en/latest/tutorials/scripting/gdscript/gdscript_basics.html#awaiting-for-signals
}

#endif