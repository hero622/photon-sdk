#pragma once

namespace sdk {
	class vec2_t {
	public:
		float x, y;

		vec2_t(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};

	class vec3_t {
	public:
		float x, y, z;

		vec3_t(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};
}  // namespace sdk