#pragma	once

namespace Utils {
	inline float linearInterpolation(float start, float end, float t) {
		return start + t * (end - start);
	}

	inline float bezierQuadratic(float p0, float p1, float p2, float t) {
		float u = 1 - t;
		return u * u * p0 + 2 * u * t * p1 + t * t * p2;
	}

	inline float bezierCubic(float p0, float p1, float p2, float p3, float t) {
		float u = 1 - t;
		return u * u * u * p0 + 3 * u * u * t * p1 + 3 * u * t * t * p2 + t * t * t * p3;
	}
}