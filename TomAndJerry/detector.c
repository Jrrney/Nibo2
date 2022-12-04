/**
 * @file detector.c
 * @author Jenny Dietrich
 * @date 19.11.2022
 * @brief role detection related functions impl
 */

#include "main.h"
#include "mouse.xbm"
#include "cat.xbm"
#include "detector.h"

const int FRONT_DETECT_DISTANCE = 80;

t_role currentRole;

/**
 * Sets the role of the NIBO and displays the role on the display
 *
 * @param role to be set
 */
void setRole(t_role role) {
	currentRole = role;

	//clear Display
	gfx_move(0, 0);
	gfx_fill(0);

	if (role == CAT) {
		// draws a pixelart of a cat
		gfx_draw_xbm_P(cat_width, cat_height, (PGM_P) cat_bits);
	} else if (role == MOUSE) {
		// draws a pixelart of a mouse
		gfx_draw_xbm_P(mouse_width, mouse_height, (PGM_P) mouse_bits);
	}
}

t_role detectAndSetRole() {
	t_role role = MOUSE;

	// Update coprocessor data
	copro_update();

	if ((copro_distance[2] / 256) >= FRONT_DETECT_DISTANCE) {
		role = CAT;
	}
	setRole(role);
	return role;
}


void resetRole() {
	gfx_fill(0);
}
