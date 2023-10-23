#pragma once

namespace sdk {
	class vec2_t {
	public:
		float x, y;

		vec2_t() {}
		vec2_t(float x, float y) {
			this->x = x;
			this->y = y;
		}

		inline vec2_t operator+(const vec2_t &v) const {
			return vec2_t(x + v.x, y + v.y);
		}
		inline vec2_t operator-(const vec2_t &v) const {
			return vec2_t(x - v.x, y - v.y);
		}
		inline vec2_t operator*(const vec2_t &v) const {
			return vec2_t(x * v.x, y * v.y);
		}
		inline vec2_t operator/(const vec2_t &v) const {
			return vec2_t(x / v.x, y / v.y);
		}
		inline void operator+=(const vec2_t &v) {
			x += v.x;
			y += v.y;
		}
		inline void operator-=(const vec2_t &v) {
			x -= v.x;
			y -= v.y;
		}
		inline void operator*=(const vec2_t &v) {
			x *= v.x;
			y *= v.y;
		}
		inline void operator/=(const vec2_t &v) {
			x /= v.x;
			y /= v.y;
		}
	};

	class vec3_t {
	public:
		float x, y, z;

		vec3_t() {}
		vec3_t(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};
}  // namespace sdk