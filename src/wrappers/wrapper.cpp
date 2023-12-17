#include "Vector2Wrapper.h"
#include "CollisionWrapper.h"
#include "PolygonWrapper.h"


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {

    Vector2Wrapper::Init(env, exports);
    CollisionWrapper::Init(env, exports);
    PolygonWrapper::Init(env, exports);

    return exports;
}

NODE_API_MODULE(collidify, InitAll)