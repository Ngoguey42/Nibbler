/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLLib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 08:52:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/21 18:22:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLLIB_H
# define OPENGLLIB_H

#include <cmath>

# ifndef DEG_TO_RAD
#  define DEG_TO_RAD(angleDegrees) (angleDegrees * M_PI / 180.0)
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846f
# endif

#define M_PIF 3.14159265358979323846f

# include "ftconstexpr/ConstexprMath.hpp"
# include "ftconstexpr/Array.class.hpp"
# include "ftconstexpr/Vertex.class.hpp"

// ============= VALUES ============= //
#define CHUNK_SIZE 30                   // Pixels integer
#define SNAKE_WAVELENGTH 115.f          // Pixels float
#define SNAKE_WIDTH 0.60f               // Percent of CHUNK_SIZE
#define POINTS_PER_SIDE 9               // Integer
#define SNAKE_HEIGHT 25.f				// Float, z-axis
#define PRECALC_POINTS_DELTA 0.15f      // Density of pre-calculated points
#define SCREEN_PADDING CHUNK_SIZE		// Pixels integer
#define NUM_PRECALC_POINTS 110			// Integer, array size
#define NUM_POINTS_PER_APPLE_SLICE 16	// Integer
#define NUM_APPLE_STRIP 6				// Integer, array size

// =========== CONVERSIONS ========== //
#define CHUNK_SIZEF static_cast<float>(CHUNK_SIZE)
#define POINTS_PER_SIDEF static_cast<float>(POINTS_PER_SIDE)
#define SCREEN_PADDINGF static_cast<float>(SCREEN_PADDING)
#define NUM_PRECALC_POINTSF static_cast<float>(NUM_PRECALC_POINTS)
#define NUM_POINTS_PER_APPLE_SLICEF static_cast<float>(NUM_POINTS_PER_APPLE_SLICE)

// ======= CALCULATED VALUES ======== //
// == SCREEN ==== //
#define SCREEN_PADDING2 (SCREEN_PADDING * 2)
// == SNAKE ===== //
#define SNAKE_WIDTH_ABSOLUTE (SNAKE_WIDTH * CHUNK_SIZEF)
#define SNAKE_WIDTH_INV (1.f - SNAKE_WIDTH)
#define SNAKE_WIDTH_HALF (SNAKE_WIDTH / 2.f)
// == POLYGONS == //
#define PHASE_PER_CHUNK (CHUNK_SIZEF / SNAKE_WAVELENGTH)
#define PHASE_PER_TRIANGLE (PHASE_PER_CHUNK / POINTS_PER_SIDEF)
#define TRIANGLES_DISTANCE (CHUNK_SIZEF / POINTS_PER_SIDEF)
// == PRECALC === //
#define MAX_POINTS_PER_APPLE_STRIP (NUM_POINTS_PER_APPLE_SLICE * 2 + 2)
#define MAX_POINTS_PER_APPLE_STRIPF static_cast<float>(MAX_POINTS_PER_APPLE_STRIP)
#define APPLE_POINTS_DELTA_RAD (M_PIF * 2.f / NUM_POINTS_PER_APPLE_SLICE)
	
//todo
#define MAX_POINTS_BEFORE_ANGLE (POINTS_PER_SIDE + 1)
#define MAX_POINTS_PER_GROUP 40
/* #define MAX_POINTS_BEFORE_ANGLEF ftce::floor(POINTS_PER_SIDEF * SNAKE_WIDTH_INV + 1.f) */
// #define MAX_POINTS_BEFORE_ANGLE static_cast<int>(MAX_POINTS_BEFORE_ANGLEF)

class AngledSnakePoints;
template <size_t S1 = MAX_POINTS_PER_GROUP,
	size_t S2 = MAX_POINTS_PER_GROUP,
	size_t S3 = MAX_POINTS_PER_GROUP,
	size_t S4 = MAX_POINTS_PER_GROUP,
	size_t S5 = MAX_POINTS_PER_GROUP,
	size_t S6 = MAX_POINTS_PER_GROUP>
	class CornerPoints;
class Window;

std::pair<int, int>  buildDelta(std::pair<int, int> const &a,
								std::pair<int, int> const &b);

typedef ftce::Array<ftce::Vertex, MAX_POINTS_PER_APPLE_STRIP>	t_appleStrip;
typedef ftce::Array<t_appleStrip, NUM_APPLE_STRIP>				t_apple;

#endif
