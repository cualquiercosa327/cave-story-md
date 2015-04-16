#include "ai_mimiga.h"

#include <genesis.h>
#include "audio.h"
#include "player.h"
#include "sprite.h"
#include "stage.h"
#include "tables.h"
#include "tsc.h"

void ai_update_toroko(Entity *e) {
	switch(e->state) {
	case 0: // Stand still
		sprite_set_animation(e->sprite, 0);
		break;
	case 3: // Run back and forth
	case 4:
		if(e->attack == 0) {
			sprite_set_animation(e->sprite, 1);
		} else {
			sprite_set_animation(e->sprite, 2);
			Bullet *b = bullet_colliding(e);
			if(b != NULL) {
				sound_play(e->hurtSound, 10); // Squeak
				e->attack = 0; // Don't hurt the player anymore
				e->eflags |= NPC_INTERACTIVE; // Enable interaction
				e->state = 10; // Change animation to falling on ground
				e->y_speed = pixel_to_sub(-1);
				e->x_speed /= 2;
				e->grounded = false;
				sprite_set_animation(e->sprite, 3);
				b->ttl = 0;
				sprite_delete(b->sprite);
			}
		}
		if(e->x_speed == 0) {
			e->direction = !e->direction;
			e->x_speed = pixel_to_sub(-2 + 4*e->direction);
			sprite_set_attr(e->sprite, TILE_ATTR(PAL3, false, false, e->direction));
		}
		break;
	case 6: // Jump then run
		break;
	case 8: // Jump in place
		break;
	case 10: // Falling down
		if(e->grounded) {
			e->x_speed = 0;
			e->state = 11;
			sprite_set_animation(e->sprite, 4);
		}
		break;
	case 11: // After falling on ground

		break;
	default:
		break;
	}
	if(!e->grounded) e->y_speed += gravity;
	e->x_next = e->x + e->x_speed;
	e->y_next = e->y + e->y_speed;
	entity_update_collision(e);
	e->x = e->x_next;
	e->y = e->y_next;
}

void ai_update_misery_float(Entity *e) {
	switch(e->state) {
	case 20:
	case 21:
		e->y_speed -= 0x20;
		break;
	default:
		break;
	}
	e->y += e->y_speed;
}

bool ai_setstate_misery_float(Entity *e, u16 state) {
	e->state = state;
	switch(state) {
	case 20: // Hover, going up
	case 21:
		break;
	default:
		break;
	}
	return false;
}