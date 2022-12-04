/**
 * @file detector.h
 * @author Jenny Dietrich
 * @date 19.11.2022
 * @brief role detection related functions
 */

#ifndef DETECT_H_
#define DETECT_H_

/**
 * type definition of the 2 roles mouse and cat
 */
typedef enum role {
	CAT, MOUSE
} t_role;

/**
 * Detects whether the NIBO is a cat or a mouse and shows a pixelart from the role on the display
 *
 * @return the detected role
 */
t_role detectAndSetRole();

/**
 * Resets the role and display
 */
void resetRole();

#endif
