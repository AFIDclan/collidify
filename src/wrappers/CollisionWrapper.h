#ifndef COLLISIONWRAPPER_H
#define COLLISIONWRAPPER_H

#include <napi.h>
#include "../Polygon.h" 
#include "Vector2Wrapper.h"

class CollisionWrapper : public Napi::ObjectWrap<CollisionWrapper> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;

    CollisionWrapper(const Napi::CallbackInfo& info);
    virtual ~CollisionWrapper();

    Collision* GetInternalInstance();

    // Exposed properties
    Napi::Value GetCollides(const Napi::CallbackInfo& info);
    void SetCollides(const Napi::CallbackInfo& info, const Napi::Value& value);

    Napi::Value GetColPoint1(const Napi::CallbackInfo& info);
    void SetColPoint1(const Napi::CallbackInfo& info, const Napi::Value& value);

    Napi::Value GetColPoint2(const Napi::CallbackInfo& info);
    void SetColPoint2(const Napi::CallbackInfo& info, const Napi::Value& value);

private:
    Collision* collision_;
};

#endif // COLLISIONWRAPPER_H
