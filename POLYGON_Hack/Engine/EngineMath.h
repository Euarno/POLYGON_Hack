#pragma once

#include <cmath>
#include <algorithm>
#include <string>
#include <locale>

struct FVector {
    double X; // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    double Y; // 0x0004(0x0004)
    double Z; // 0x0008(0x0004)

    inline FVector() : X(0), Y(0), Z(0) {}

    inline FVector(double x, double y, double z) : X(x), Y(y), Z(z) {}

    inline FVector operator + (const FVector& other) const {
        return FVector(X + other.X, Y + other.Y, Z + other.Z);
    }

    inline FVector operator - (const FVector& other) const {
        return FVector(X - other.X, Y - other.Y, Z - other.Z);
    }

    inline FVector operator * (double scalar) const {
        return FVector(X * scalar, Y * scalar, Z * scalar);
    }

    inline FVector operator * (const FVector& other) const {
        return FVector(X * other.X, Y * other.Y, Z * other.Z);
    }

    inline FVector operator / (double scalar) const {
        return FVector(X / scalar, Y / scalar, Z / scalar);
    }

    inline FVector operator / (const FVector& other) const {
        return FVector(X / other.X, Y / other.Y, Z / other.Z);
    }

    inline FVector& operator=  (const FVector& other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    inline FVector& operator+= (const FVector& other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    inline FVector& operator-= (const FVector& other) {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    inline FVector& operator*= (double scalar) {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    inline double Dot(const FVector& b) const {
        return (X * b.X) + (Y * b.Y) + (Z * b.Z);
    }

    inline double MagnitudeSqr() const {
        return Dot(*this);
    }

    inline double Magnitude() const {
        return std::sqrt(MagnitudeSqr());
    }

    inline FVector Unit() const {
        double fMagnitude = Magnitude();
        return FVector(X / fMagnitude, Y / fMagnitude, Z / fMagnitude);
    }

    inline int dot_product(FVector vector_a, FVector vector_b) const {
        int product = 0;
        product += vector_a.X * vector_b.Y;
        product += vector_a.Y * vector_b.Y;
        product += vector_a.Z * vector_b.Z;
        return product;
    }

    friend bool operator==(const FVector& first, const FVector& second) {
        return first.X == second.X && first.Y == second.Y && first.Z == second.Z;
    }

    friend bool operator!=(const FVector& first, const FVector& second) {
        return !(first == second);
    }
};

struct FRotator {
    float Pitch; // 0x0000(0x0004)
    float Yaw; // 0x0004(0x0004)
    float Roll; // 0x0008(0x0004)

    inline FRotator() : Pitch(0), Yaw(0), Roll(0) {}

    inline FRotator(float pitch, float yaw, float roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}

    inline float Size() {
        return std::sqrt(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
    }

    inline FRotator Clamp() {
        FRotator r = { Pitch, Yaw, Roll };
        if (r.Yaw > 180.f) r.Yaw -= 360.f;
        else if (r.Yaw < -180.f) r.Yaw += 360.f;

        if (r.Pitch > 180.f) r.Pitch -= 360.f;
        else if (r.Pitch < -180.f) r.Pitch += 360.f;

        if (r.Pitch < -89.f) r.Pitch = -89.f;
        else if (r.Pitch > 89.f) r.Pitch = 89.f;

        r.Roll = 0.f;
        return r;
    }

    inline FRotator operator + (const FRotator& other) const {
        return FRotator(Pitch + other.Pitch, Yaw + other.Yaw, Roll + other.Roll);
    }

    inline FRotator operator - (const FRotator& other) const {
        return FRotator(Pitch - other.Pitch, Yaw - other.Yaw, Roll - other.Roll);
    }

    inline FRotator operator * (float scalar) const {
        return FRotator(Pitch * scalar, Yaw * scalar, Roll * scalar);
    }

    inline FRotator operator * (const FRotator& other) const {
        return FRotator(Pitch * other.Pitch, Yaw * other.Yaw, Roll * other.Roll);
    }

    inline FRotator operator / (float scalar) const {
        return FRotator(Pitch / scalar, Yaw / scalar, Roll / scalar);
    }

    inline FRotator operator / (const FRotator& other) const {
        return FRotator(Pitch / other.Pitch, Yaw / other.Yaw, Roll / other.Roll);
    }

    inline FRotator& operator=  (const FRotator& other) {
        Pitch = other.Pitch;
        Yaw = other.Yaw;
        Roll = other.Roll;
        return *this;
    }

    inline FRotator& operator+= (const FRotator& other) {
        Pitch += other.Pitch;
        Yaw += other.Yaw;
        Roll += other.Roll;
        return *this;
    }

    inline FRotator& operator-= (const FRotator& other) {
        Pitch -= other.Pitch;
        Yaw -= other.Yaw;
        Roll -= other.Roll;
        return *this;
    }

    inline FRotator& operator*= (float scalar) {
        Pitch *= scalar;
        Yaw *= scalar;
        Roll *= scalar;
        return *this;
    }

    friend bool operator==(const FRotator& first, const FRotator& second) {
        return first.Pitch == second.Pitch && first.Yaw == second.Yaw && first.Roll == second.Roll;
    }
};

struct FVector2D {
    double X; // 0x0000(0x0004)
    double Y; // 0x0004(0x0004)

    inline FVector2D() : X(0), Y(0) {}

    inline FVector2D(double x, double y) : X(x), Y(y) {}

    inline FVector2D operator + (const FVector2D& other) const {
        return FVector2D(X + other.X, Y + other.Y);
    }

    inline FVector2D operator - (const FVector2D& other) const {
        return FVector2D(X - other.X, Y - other.Y);
    }

    inline FVector2D operator * (double scalar) const {
        return FVector2D(X * scalar, Y * scalar);
    }

    inline FVector2D operator * (const FVector2D& other) const {
        return FVector2D(X * other.X, Y * other.Y);
    }

    inline FVector2D operator / (double scalar) const {
        return FVector2D(X / scalar, Y / scalar);
    }

    inline FVector2D operator / (const FVector2D& other) const {
        return FVector2D(X / other.X, Y / other.Y);
    }

    inline FVector2D& operator=  (const FVector2D& other) {
        X = other.X;
        Y = other.Y;
        return *this;
    }

    inline FVector2D& operator+= (const FVector2D& other) {
        X += other.X;
        Y += other.Y;
        return *this;
    }

    inline FVector2D& operator-= (const FVector2D& other) {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }

    inline FVector2D& operator*= (double scalar) {
        X *= scalar;
        Y *= scalar;
        return *this;
    }
};
struct FVector4 {
    double X; // 0x0000(0x0004)
    double Y; // 0x0004(0x0004)
    double Z; // 0x0008(0x0004)
    double W; // 0x000C(0x0004)

    inline FVector4() : X(0), Y(0), Z(0), W(0) {}

    inline FVector4(double x, double y, double z, double w) : X(x), Y(y), Z(z), W(w) {}

    inline FVector4 operator + (const FVector4& other) const {
        return FVector4(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
    }

    inline FVector4 operator - (const FVector4& other) const {
        return FVector4(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
    }

    inline FVector4 operator * (double scalar) const {
        return FVector4(X * scalar, Y * scalar, Z * scalar, W * scalar);
    }

    inline FVector4 operator * (const FVector4& other) const {
        return FVector4(X * other.X, Y * other.Y, Z * other.Z, W * other.W);
    }

    inline FVector4 operator / (double scalar) const {
        return FVector4(X / scalar, Y / scalar, Z / scalar, W / scalar);
    }

    inline FVector4 operator / (const FVector4& other) const {
        return FVector4(X / other.X, Y / other.Y, Z / other.Z, W / other.W);
    }

    inline FVector4& operator= (const FVector4& other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;
        return *this;
    }

    inline FVector4& operator+= (const FVector4& other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        W += other.W;
        return *this;
    }

    inline FVector4& operator-= (const FVector4& other) {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        W -= other.W;
        return *this;
    }

    inline FVector4& operator*= (double scalar) {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
        return *this;
    }

    inline FVector4& operator*= (const FVector4& other) {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        W *= other.W;
        return *this;
    }

    inline FVector4& operator/= (double scalar) {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        W /= scalar;
        return *this;
    }

    inline FVector4& operator/= (const FVector4& other) {
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        W /= other.W;
        return *this;
    }
};
struct FTransform
{
    FVector4 Rotation;
    FVector4 Translation;
    FVector4 Scale3D;
};

struct FNameEntry
{
    uint16_t bIsWide : 1;
    uint16_t LowercaseProbeHash : 5;
    uint16_t Len : 10;

    union
    {
        char AnsiName[1024];
        wchar_t	WideName[1024];
    };
};

class FMinimalViewInfo {
public:
    FVector Location; // 0x00(0x0c)
    FVector Rotation; // 0x0c(0x0c)
    float FOV; // 0x18(0x04)
    float DesiredFOV; // 0x1c(0x04)
    float OrthoWidth; // 0x20(0x04)
    float OrthoNearClipPlane; // 0x24(0x04)
    float OrthoFarClipPlane; // 0x28(0x04)
    float AspectRatio; // 0x2c(0x04)
};

class FCameraCacheEntry {
public:
    float Timestamp; // 0x00(0x04)
    unsigned char UnknownData00[0xc]; // 0x04(0x0c)
    FMinimalViewInfo POV; // 0x10(0x5b0)
};
