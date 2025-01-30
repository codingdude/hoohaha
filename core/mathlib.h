#ifndef HOOHAHA_CORE_MATHLIB_H_
#define HOOHAHA_CORE_MATHLIB_H_

namespace core
{

class Vector3d final
{
public:
    inline Vector3d();
    inline Vector3d(float scalar);
    inline Vector3d(float* raw_ptr);
    inline Vector3d(float x, float y, float z);

    inline void Init(float scalar);
    inline void Init(float* raw_ptr); // yeah, but no, but...
    inline void Init(float x, float y, float z);
    inline void Normalize();
    inline void Clear();

    inline float* Data();
    inline const float* Data() const;

    inline int Size() const;

    inline float Length() const;
    inline float DotProduct(const Vector3d& rhs) const;
    inline Vector3d CrossProduct(const Vector3d& rhs) const;
    inline Vector3d GetNormalized() const;

    inline float X() const;
    inline float Y() const;
    inline float Z() const;

    inline float& X();
    inline float& Y();
    inline float& Z();

    inline float operator[](int index) const;
    inline float& operator[](int index);

    inline bool operator==(const Vector3d& rhs) const;
    inline bool operator!=(const Vector3d& rhs) const;

    inline Vector3d operator+(const Vector3d& rhs) const;
    inline Vector3d operator-(const Vector3d& rhs) const;
    inline Vector3d operator*(const Vector3d& rhs) const;
    inline Vector3d operator/(const Vector3d& rhs) const;

    inline Vector3d operator*(float scalar) const;
    inline Vector3d operator/(float scalar) const;

    inline Vector3d& operator+=(const Vector3d& rhs);
    inline Vector3d& operator-=(const Vector3d& rhs);
    inline Vector3d& operator*=(const Vector3d& rhs);
    inline Vector3d& operator/=(const Vector3d& rhs);

    inline Vector3d& operator*=(float scalar);
    inline Vector3d& operator/=(float scalar);

private:
    enum
    {
        kXIndex = 0,
        kYIndex = 1,
        kZIndex = 2,

        kSize = 3
    };

    float xyz[kSize];
};

class Vector4d final
{
public:
    inline Vector4d();
    inline Vector4d(float scalar);
    inline Vector4d(float* raw_ptr);
    inline Vector4d(float x, float y, float z, float w);

    inline void Init(float scalar);
    inline void Init(float* raw_ptr); // yeah, but no, but...
    inline void Init(float x, float y, float z, float w);
    inline void Normalize();
    inline void Clear();

    inline float* Data();
    inline const float* Data() const;

    inline int Size() const;

    inline float Length() const;
    inline float DotProduct(const Vector4d& rhs) const;
    inline Vector4d CrossProduct(const Vector4d& rhs) const;
    inline Vector4d GetNormalized() const;

    inline float X() const;
    inline float Y() const;
    inline float Z() const;
    inline float W() const;

    inline float& X();
    inline float& Y();
    inline float& Z();
    inline float& W();

    inline float operator[](int index) const;
    inline float& operator[](int index);

    inline bool operator==(const Vector4d& rhs) const;
    inline bool operator!=(const Vector4d& rhs) const;

    inline Vector4d operator+(const Vector4d& rhs) const;
    inline Vector4d operator-(const Vector4d& rhs) const;
    inline Vector4d operator*(const Vector4d& rhs) const;
    inline Vector4d operator/(const Vector4d& rhs) const;

    inline Vector4d operator*(float scalar) const;
    inline Vector4d operator/(float scalar) const;

    inline Vector4d& operator+=(const Vector4d& rhs);
    inline Vector4d& operator-=(const Vector4d& rhs);
    inline Vector4d& operator*=(const Vector4d& rhs);
    inline Vector4d& operator/=(const Vector4d& rhs);

    inline Vector4d& operator*=(float scalar);
    inline Vector4d& operator/=(float scalar);

private:
    enum
    {
        kXIndex = 0,
        kYIndex = 1,
        kZIndex = 2,
        kWIndex = 3,

        kSize = 4
    };

    float xyzw[kSize];
};

}

#endif // HOOHAHA_CORE_MATHLIB_H_
