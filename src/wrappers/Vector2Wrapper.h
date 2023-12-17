#ifndef VECTOR2WRAPPER_H
#define VECTOR2WRAPPER_H

#include <napi.h>
#include "../Vector2.h"

class Vector2Wrapper : public Napi::ObjectWrap<Vector2Wrapper> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;

    Vector2Wrapper(const Napi::CallbackInfo& info);
    virtual ~Vector2Wrapper(); 

    Vector2* GetInternalInstance();
    void SetInternalInstance(Vector2* vector);

    Napi::Value Magnitude(const Napi::CallbackInfo& info);
    Napi::Value Dot(const Napi::CallbackInfo& info);
    Napi::Value Normalize(const Napi::CallbackInfo& info);
    Napi::Value Clone(const Napi::CallbackInfo& info);

    Napi::Value GetX(const Napi::CallbackInfo& info);
    void SetX(const Napi::CallbackInfo& info, const Napi::Value& value);

    Napi::Value GetY(const Napi::CallbackInfo& info);
    void SetY(const Napi::CallbackInfo& info, const Napi::Value& value);

    Napi::Value toJSON(const Napi::CallbackInfo& info);


private:
    Vector2* vector_;


};

#endif // VECTOR2WRAPPER_H
