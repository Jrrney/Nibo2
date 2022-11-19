#ifndef DETECT_H_
#define DETECT_H_

typedef enum role {
	CAT,
	MOUSE
} t_role;

t_role detectAndSetRole();

#endif
