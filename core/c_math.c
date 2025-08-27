//
// Created by Cory Smith on 7/25/25.
//

#include "core.h"

// Vec2

Vec2 c_vec2_add(Vec2 a, Vec2 b) {
    return (Vec2){a.x + b.x, a.y + b.y};
}

Vec2 c_vec2_sub(Vec2 a, Vec2 b) {
    return (Vec2){a.x - b.x, a.y - b.y};
}

Vec2 c_vec2_scale(Vec2 a, f32 b) {
    return (Vec2){a.x * b, a.y * b};
}

f32 c_vec2_dot(Vec2 a, Vec2 b) {
    return ((a.x * b.x) + (a.y * b.y));
}

// Vec3

Vec3 c_vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 c_vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z + b.z};
}

Vec3 c_vec3_scale(Vec3 a, f32 b) {
    return (Vec3){a.x * b, a.y * b, a.z * b};
}

f32 c_vec3_dot(Vec3 a, Vec3 b) {
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

// Vec4

Vec4 c_vec4_add(Vec4 a, Vec4 b) {
    return (Vec4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

Vec4 c_vec4_sub(Vec4 a, Vec4 b) {
    return (Vec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}


// Mat4

Mat4 c_mat4_identity() {
    return (Mat4){
        .m = {
            1, 0, 0, 0,
        	0, 1, 0, 0,
        	0, 0, 1, 0,
        	0, 0, 0, 1
        }
    };
}


Mat4 c_mat4_mul(Mat4 a, Mat4 b) {
	return (Mat4){
	};
}

Mat4 c_mat4_inv(Mat4 a) {

}

Mat4 c_mat4_mul_inv(Mat4 a, Mat4 b) {

}

Mat4 c_mat4_inv_inv(Mat4 a, Mat4 b) {

}

Mat4 c_mat4_transpose(Mat4 a) {

}

Mat4 c_mat4_transpose_inv(Mat4 a) {

}

Mat4 c_mat4_look_at(Vec3 eye, Vec3 at, Vec3 up) {

}

Mat4 c_mat4_ortho(Vec3 min, Vec3 max) {

}
