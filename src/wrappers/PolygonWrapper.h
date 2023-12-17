
#ifndef POLYGONWRAPPER_H
#define POLYGONWRAPPER_H

#include <napi.h>
#include "../Polygon.h"
#include "Vector2Wrapper.h"
#include "PolygonWrapper.h"

class PolygonWrapper : public Napi::ObjectWrap<PolygonWrapper> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;

    PolygonWrapper(const Napi::CallbackInfo& info);
    virtual ~PolygonWrapper();

    Polygon* GetInternalInstance();

    Napi::Value Contains(const Napi::CallbackInfo& info);
    Napi::Value CollidesWith(const Napi::CallbackInfo& info);

    void MoveBy(const Napi::CallbackInfo& info);
    void RotateBy(const Napi::CallbackInfo& info);
    void MoveTo(const Napi::CallbackInfo& info);

    Napi::Value GetVertices(const Napi::CallbackInfo& info);


private:
    Polygon* polygon_;
};

#endif // POLYGONWRAPPER_H
