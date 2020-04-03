#pragma once

#include "vector_2d.h"

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
		#define ALIGN16 __declspec(align(16))
		#define CHECK_VALID( _v ) 0
		#define FastSqrt(x)	(sqrt)(x)
		class vector_3d {
		public:
			// The only notation exception, for clarity of course.
			float x, y, z;

			constexpr explicit vector_3d(float flX = 0.f, float flY = 0.f, float flZ = 0.f) : x(flX), y(flY), z(flZ) { }
			constexpr explicit vector_3d(const float* flV) : x(flV[0]), y(flV[1]), z(flV[2]) { }

			~vector_3d() { }

			void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);

			// Basic
			bool IsEmpty() const {
				return x == 0.f && y == 0.f && z == 0.f;
			}

			void Clear() {
				x = y = z = 0.f;
			}

			bool IsValid() {
				return !std::isnan(x) || !std::isnan(y) || !std::isnan(z);
			}

			// Operators
			vector_3d& operator=(const vector_2d& vOther) {
				x = vOther.x;
				y = vOther.y;
				z = 0.f;
				return *this;
			}

			bool operator==(const vector_3d& vOther) const {
				return (x == vOther.x && y == vOther.y && z == vOther.z);
			}

			bool operator!=(const vector_3d& vOther) const {
				return !(*this == vOther);
			}

			float& operator[](int iMember) {
				assert((iMember >= 0) && (iMember < 3));
				return ((float*)this)[iMember];
			}

			float operator[](int iMember) const {
				assert((iMember >= 0) && (iMember < 3));
				return ((float*)this)[iMember];
			}

			template <typename A>
			vector_3d operator+(A tOther) const {
				vector_3d vBuffer = *this;
				vBuffer += static_cast<float>(tOther);
				return vBuffer;
			}

			template <typename A>
			vector_3d operator-(A tOther) const {
				vector_3d vBuffer = *this;
				vBuffer -= static_cast<float>(tOther);
				return vBuffer;
			}

			template <typename A>
			vector_3d operator*(A tOther) const {
				vector_3d vBuffer = *this;
				vBuffer *= static_cast<float>(tOther);
				return vBuffer;
			}

			template <typename A>
			vector_3d operator/(A tOther) const {
				vector_3d vBuffer = *this;
				vBuffer /= static_cast<float>(tOther);
				return vBuffer;
			}

			template <typename A>
			vector_3d& operator+=(A tOther) {
				x += static_cast<float>(tOther);
				y += static_cast<float>(tOther);
				z += static_cast<float>(tOther);

				return *this;
			}

			template <typename A>
			vector_3d& operator-=(A tOther) {
				x -= static_cast<float>(tOther);
				y -= static_cast<float>(tOther);
				z -= static_cast<float>(tOther);

				return *this;
			}

			template <typename A>
			vector_3d& operator*=(A tOther) {
				x *= static_cast<float>(tOther);
				y *= static_cast<float>(tOther);
				z *= static_cast<float>(tOther);

				return *this;
			}

			template <typename A>
			vector_3d& operator/=(A tOther) {
				x /= static_cast<float>(tOther);
				y /= static_cast<float>(tOther);
				z /= static_cast<float>(tOther);

				return *this;
			}

			vector_3d operator+(const vector_3d& tOther) const {
				vector_3d vBuffer = *this;

				vBuffer.x += tOther.x;
				vBuffer.y += tOther.y;
				vBuffer.z += tOther.z;

				return vBuffer;
			}

			vector_3d operator-(const vector_3d& tOther) const {
				vector_3d vBuffer = *this;

				vBuffer.x -= tOther.x;
				vBuffer.y -= tOther.y;
				vBuffer.z -= tOther.z;

				return vBuffer;
			}

			vector_3d& operator+=(const vector_3d& tOther) {
				x += tOther.x;
				y += tOther.y;
				z += tOther.z;

				return (*this);
			}

			vector_3d& operator-=(const vector_3d& tOther) {
				x -= tOther.x;
				y -= tOther.y;
				z -= tOther.z;

				return (*this);
			}

			// Math
			float Length2D() const {
				return sqrt(LengthSqr2D());
			}

			float LengthSqr2D() const {
				return x * x + y * y;
			}

			float Length() const {
				return sqrt(LengthSqr());
			}

			float LengthSqr() const {
				return x * x + y * y + z * z;
			}

			float Distance(const vector_3d& vOther) const {
				return abs((vOther - *this).Length());
			}

			void Normalize() {
				*this /= Length() + std::numeric_limits< float >::epsilon();
			}

			vector_3d Normalized() const {
				vector_3d vBase = *this;
				vBase.Normalize();
				return vBase;
			}

			float Dot(const vector_3d& vOther) const {
				return x * vOther.x + y * vOther.y + z * vOther.z;
			}

			float Dot(float* flOther) const {
				return x * flOther[0] + y * flOther[1] + z * flOther[2];
			}

			vector_3d CrossProduct(const vector_3d& vA, const vector_3d& vB) const {
				return vector_3d(vA.y * vB.z - vA.z * vB.y, vA.z * vB.x - vA.x * vB.z, vA.x * vB.y - vA.y * vB.x);
			}

			vector_3d Cross(const vector_3d& vOther) const {
				return CrossProduct(*this, vOther);
			}

			vector_3d Angle() {
				vector_3d vForward, vAngles;
				vForward = *this;

				if (vForward.x == 0.f && vForward.y == 0.f) {
					vAngles.x = vForward.z > 0.f ? -90.f : 90.f;
					vAngles.y = 0.f;
				}
				else {
					vAngles.x = atan2(-vForward.z, vForward.Length2D()) * (180.f / 3.1415926);
					vAngles.y = atan2(vForward.y, vForward.x) * (180.f / 3.1415926);
				}

				vAngles.z = 0.f;

				return vAngles;
			}

			void Clamp() {
				x = std::clamp(x, -89.0f, 89.0f);
				y = std::clamp(std::remainderf(y, 360.0f), -180.f, 180.f);
				z = std::clamp(z, -50.f, 50.f);
			}

			float NormalizeInPlace() {
				float radius = FastSqrt(x * x + y * y + z * z);

				// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
				float iradius = 1.f / (radius + FLT_EPSILON);

				x *= iradius;
				y *= iradius;
				z *= iradius;

				return radius;
			}
		};

		FORCEINLINE float DotProduct(const vector_3d& a, const vector_3d& b) {
			return (a.x * b.x + a.y * b.y + a.z * b.z);
		}

		inline void vector_3d::Init(float ix, float iy, float iz) {
			x = ix; y = iy; z = iz;
			CHECK_VALID(*this);
		}

		class ALIGN16 vector_aligned : public vector_3d {
		public:
			inline vector_aligned(void) {};
			inline vector_aligned(float X, float Y, float Z) {
				Init(X, Y, Z);
			}

#ifdef VECTOR_NO_SLOW_OPERATIONS

		private:
			// No copy constructors allowed if we're in optimal mode
			vector_aligned(const vector_aligned& vOther);
			vector_aligned(const Vector& vOther);

#else
		public:
			explicit vector_aligned(const vector_3d& vOther) {
				Init(vOther.x, vOther.y, vOther.z);
			}

			vector_aligned& operator=(const vector_3d& vOther) {
				Init(vOther.x, vOther.y, vOther.z);
				return *this;
			}

#endif
			float w;	// this space is used anyway
		};
	};
};