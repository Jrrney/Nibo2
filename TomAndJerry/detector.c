#include "main.h"
#include "mouse.xbm"
#include "cat.xbm"
#include "detector.h"

const int FRONT_DETECT_DISTANCE = 80;

t_role currentRole;

void setRole(t_role role) {
//	if(currentRole == role) return;

	currentRole = role;

	//reinige Display
	gfx_move(0, 0);
	gfx_fill(0);

	if (role == CAT) {
		gfx_draw_xbm_P(cat_width, cat_height, (PGM_P) cat_bits);
	} else if (role == MOUSE) {
		gfx_draw_xbm_P(mouse_width, mouse_height, (PGM_P) mouse_bits);
	}
}

t_role detectAndSetRole() {
	t_role role = MOUSE;

	// Aktualisierung aller Daten vom Coprozessor
	copro_update();

	if ((copro_distance[2] / 256) >= FRONT_DETECT_DISTANCE) {
		role = CAT;
	}
	setRole(role);
	return role;
}

