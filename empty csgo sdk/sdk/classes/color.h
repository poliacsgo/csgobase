#pragma once

namespace sdk {
	namespace classes {
		class color {
		public:
			float red, green, blue, alpha;

			color() {
				red = 0.f, green = 0.f, blue = 0.f, alpha = 255.f;
			}

			color(float red_value, float green_value, float blue_value, float alpha_value) {
				red = red_value, green = green_value, blue = blue_value, alpha = alpha_value;
			}

			color(float red_value, float green_value, float blue_value) {
				red = red_value, green = green_value, blue = blue_value, alpha = 255.f;
			}
		};
	};
};