#pragma once

#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <algorithm>

namespace sdk {
	namespace math {
		class vector_2d {
		public:
			// The only notation exception, for clarity of course.
			float x, y;

			constexpr explicit vector_2d(float flX = 0.f, float flY = 0.f) : x(flX), y(flY) { }
			constexpr explicit vector_2d(const float* flV) : x(flV[0]), y(flV[1]) { }

			~vector_2d() { }

			// Basic
			bool IsEmpty() const {
				return x == 0.f && y == 0.f;
			}

			void Clear() {
				x = y = 0.f;
			}

			// Operators
			bool operator==(const vector_2d& vOther) const {
				return (x == vOther.x && y == vOther.y);
			}

			bool operator!=(const vector_2d& vOther) const {
				return !(*this == vOther);
			}

			template <typename A>
			vector_2d operator+(A tOther) const {
				vector_2d vBuffer = *this;
				vBuffer += static_cast<float>(tOther);
				return vBuffer;
			}

			template <typename A>
			vector_2d operator-(A tOther) const {
				vector_2d vBuffer = *this;
				vBuffer -= static_cast<float>(tOther);
				return vBuffer;
			}

			template <typename A>
			vector_2d operator*(A tOther) const {
				vector_2d vBuffer = *this;
				vBuffer *= static_cast<float>(tOther);
				return vBuffer;
			}

			template <typename A>
			vector_2d operator/(A tOther) const {
				vector_2d vBuffer = *this;
				vBuffer /= static_cast<float>(tOther);
				return vBuffer;
			}

			template <typename A>
			vector_2d& operator+=(A tOther) {
				x += static_cast<float>(tOther);
				y += static_cast<float>(tOther);

				return *this;
			}

			template <typename A>
			vector_2d& operator-=(A tOther) {
				x -= static_cast<float>(tOther);
				y -= static_cast<float>(tOther);

				return *this;
			}

			template <typename A>
			vector_2d& operator*=(A tOther) {
				x *= static_cast<float>(tOther);
				y *= static_cast<float>(tOther);

				return *this;
			}

			template <typename A>
			vector_2d& operator/=(A tOther) {
				x /= static_cast<float>(tOther);
				y /= static_cast<float>(tOther);

				return *this;
			}

			vector_2d operator+(const vector_2d& tOther) const {
				vector_2d vBuffer = *this;

				vBuffer.x += tOther.x;
				vBuffer.y += tOther.y;

				return vBuffer;
			}

			vector_2d operator-(const vector_2d& tOther) const {
				vector_2d vBuffer = *this;

				vBuffer.x -= tOther.x;
				vBuffer.y -= tOther.y;

				return vBuffer;
			}

			vector_2d& operator+=(const vector_2d& tOther) {
				x += tOther.x;
				y += tOther.y;

				return (*this);
			}

			vector_2d& operator-=(const vector_2d& tOther)
			{
				x -= tOther.x;
				y -= tOther.y;

				return (*this);
			}

			// Math
			float Length() const {
				return sqrt(LengthSqr());
			}

			float LengthSqr() const {
				return x * x + y * y;
			}

			float Distance(const vector_2d& vOther) const {
				return (vOther - (*this)).Length();
			}

			void Normalize() {
				*this /= Length();
			}

			vector_2d Normalized() const {
				vector_2d vBase = *this;
				vBase.Normalize();
				return vBase;
			}
		};
	};
};