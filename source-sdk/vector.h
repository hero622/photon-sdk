#pragma once

namespace sdk {
	struct vec2_t {
		float x, y;

		vec2_t() {}

		vec2_t(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};

	struct vec3_t {
		float x, y, z;

		vec3_t() {}

		vec3_t(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};
}  // namespace sdk