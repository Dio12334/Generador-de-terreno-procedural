#ifndef VECTORS_H
#define VECTORS_H

#include <cmath>
#include <math.h>

struct Vector3{
    float x;
    float y; 
    float z;
    Vector3(): x(0), y(0), z(0){}
    Vector3(float x, float y, float z): x(x), y(y), z(z){}
    Vector3(float u): x(u), y(u), z(u){}

    void normalize(){
        float dist = sqrt(x*x + y*y + z*z);
        x /= dist;
        y /= dist;
        z /= dist;
    }

    Vector3 rnormalize(){
      float dist = sqrt(x*x +y*y +z*z);
      return Vector3(x/dist, y/dist, z/dist);
    }

    float length(){
      return sqrt(x*x +y*y+z*z);
    }
     Vector3 operator/(const float& number){
        return Vector3(x/number, y/number, z/number);
      }

      Vector3 operator*(const float& number){
        return Vector3(x*number, y*number, z*number);
      }

      Vector3 operator*(const Vector3& vec){
        return Vector3((vec.x * x), (vec.y*y), (vec.z*z));
      }

      Vector3 cross_product(const Vector3& vec){
        return Vector3( ((y*vec.z)-(z*vec.y)), -((x*vec.z)-(z*vec.x)), ((x*vec.y)-(y*vec.x)));
      }
      Vector3 operator+(const Vector3& vec){
        return Vector3(x+vec.x, y+vec.y, z+vec.z);
      }

      Vector3 operator-(const Vector3& vec){
        return Vector3(x-vec.x, y-vec.y, z-vec.z);
      }

      void operator =(const Vector3& vec){
        x = vec.x;
        y = vec.y;
        z = vec.z;
      }
      void operator +=(const Vector3& vec){
        x = vec.x + x;
        y = vec.y + y;
        z = vec.z + z;
      }

      void operator -=(const Vector3& vec){
        x = x - vec.x;
        y = y - vec.y;
        z = z - vec.z;

      }
};

struct Vector2{
    float x;
    float y;

    Vector2(): x(0), y(0){}
    Vector2(float x, float y):x(x), y(y){}
    Vector2(float u): x(u), y(u){} 
    
    float lenght(){
      return (sqrt(x*x + y*y));
    }
    Vector2 operator/(const float& number){
        return Vector2(x/number, y/number);
    }
    Vector2 intify(){
      return Vector2((int)x, (int)y);
    }
      
    Vector2 operator*(float& number){
        return Vector2(x*number, y*number);
    }

      float operator*(const Vector2& vec){
        return (vec.x * x)+ (vec.y*y);
      }

      Vector3 cross_product(const Vector2& vec){
        return Vector3( ((y*0)-(0*vec.y)), -((x*0)-(0*vec.x)), ((x*vec.y)-(y*vec.x)));
      } 
      Vector2 operator+(const Vector2& vec){
        return Vector2(x+vec.x, y+vec.y);
      }

      Vector2 operator-(const Vector2& vec){
        return Vector2(x-vec.x, y-vec.y);
      }

      void operator =(const Vector2& vec){
        x = vec.x;
        y = vec.y;
      }
      void operator +=(const Vector2& vec){
        x = vec.x + x;
        y = vec.y + y;
      }
     void operator *=(const float& number){
        x = x*number;
        y = y*number;
      }


      void operator -=(const Vector2& vec){
        x = x - vec.x;
        y = y - vec.y;

      }
};

#endif
