/*
 * Copyright (C) 2016 Javad Doliskani, javad.doliskani@uwaterloo.ca
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sidh_public_key.h"
#include "sidh_isogeny.h"
#include "sidh_private_key.h"
#include <stdio.h>
#include <math.h>

void sidh_public_key_init(public_key_t public_key) {
    sidh_elliptic_curve_init(public_key->E);
    sidh_point_init(public_key->P);
    sidh_point_init(public_key->Q);
}

void sidh_public_key_clear(public_key_t public_key) {
    sidh_elliptic_curve_clear(public_key->E);
    sidh_point_clear(public_key->P);
    sidh_point_clear(public_key->Q);
}

void sidh_public_key_generate(public_key_t public_key,
                              const point_t kernel_gen,
                              const public_params_t paramsA,
                              const public_params_t paramsB) {

    point_t points[2];
    sidh_point_init(points[0]);
    sidh_point_init(points[1]);

    sidh_elliptic_curve_set(public_key->E, paramsA->E);
    sidh_point_set(points[0], paramsB->P);
    sidh_point_set(points[1], paramsB->Q);

    sidh_isogeny_evaluate_strategy(public_key->E,
                                   points,
                                   2,
                                   kernel_gen,
                                   paramsA->l,
                                   paramsA->e,
                                   0.5);

//        sidh_isogeny_evaluate_naive(public_key->E,
//                               points,
//                               2,
//                               kernel_gen,
//                               paramsA->l,
//                               paramsA->e,
//                               10);

    sidh_point_set(public_key->P, points[0]);
    sidh_point_set(public_key->Q, points[1]);

    sidh_point_clear(points[0]);
    sidh_point_clear(points[1]);
}

void sidh_public_key_print(const public_key_t public_key) {
    printf("E: %s\n", sidh_elliptic_curve_get_str(public_key->E));
    printf("P: %s\n", sidh_point_get_str(public_key->P));
    printf("Q: %s\n", sidh_point_get_str(public_key->Q));
}