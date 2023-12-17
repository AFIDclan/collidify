
#include "PolygonWrapper.h"
#include "Vector2Wrapper.h"
#include "CollisionWrapper.h"

Napi::FunctionReference PolygonWrapper::constructor;

Napi::Object PolygonWrapper::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Polygon", {
        InstanceMethod("Contains", &PolygonWrapper::Contains),
        InstanceMethod("CollidesWith", &PolygonWrapper::CollidesWith),
        InstanceMethod("MoveBy", &PolygonWrapper::MoveBy),
        InstanceMethod("MoveTo", &PolygonWrapper::MoveTo),
        InstanceMethod("RotateBy", &PolygonWrapper::RotateBy),
        InstanceAccessor("vertices", &PolygonWrapper::GetVertices, nullptr)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Polygon", func);

    return exports;
}


PolygonWrapper::PolygonWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<PolygonWrapper>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Check if the first argument is an array
    if (info.Length() >= 1 && info[0].IsArray()) {
        Napi::Array js_array = info[0].As<Napi::Array>();
        std::vector<Vector2> vertices;

        for (size_t i = 0; i < js_array.Length(); ++i) {
            Napi::Value val = js_array[i];
            // Check if the value is an object and can be unwrapped to Vector2Wrapper
            if (val.IsObject()) {
                Vector2Wrapper* vector_wrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(val.As<Napi::Object>());
                vertices.push_back(*vector_wrapper->GetInternalInstance());
            } else {
                Napi::TypeError::New(env, "Array must contain Vector2 objects").ThrowAsJavaScriptException();
                return;
            }
        }

        this->polygon_ = new Polygon(vertices);
    } else {
        this->polygon_ = new Polygon();
    }
}

PolygonWrapper::~PolygonWrapper() {
    delete this->polygon_;
}

Napi::Value PolygonWrapper::Contains(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Check if the first argument is an array
    if (info.Length() >= 1 && info[0].IsObject()) {
        Vector2Wrapper* vector_wrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(info[0].As<Napi::Object>());
        bool return_value = this->polygon_->Contains(*vector_wrapper->GetInternalInstance()).first;
        return Napi::Boolean::New(env, return_value);
    } else {
        Napi::TypeError::New(env, "Vector2 object expected").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
}

Napi::Value PolygonWrapper::CollidesWith(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Check if the first argument is an array
    if (info.Length() >= 1 && info[0].IsObject()) {
        PolygonWrapper* polygon_wrapper = Napi::ObjectWrap<PolygonWrapper>::Unwrap(info[0].As<Napi::Object>());
        Collision col = this->polygon_->CollidesWith(*polygon_wrapper->GetInternalInstance());

        // Return col
        Napi::Object obj = CollisionWrapper::constructor.New({});
        CollisionWrapper* col_wrapper = Napi::ObjectWrap<CollisionWrapper>::Unwrap(obj);
        
        Collision* col_internal = col_wrapper->GetInternalInstance();

        col_internal->collides = col.collides;
        col_internal->col_point1 = col.col_point1;
        col_internal->col_point2 = col.col_point2;

        return obj;
        
    } else {
        Napi::TypeError::New(env, "Polygon object expected").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
}

Napi::Value PolygonWrapper::GetVertices(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::vector<Vector2> vertices = this->polygon_->vertices;
    Napi::Array js_array = Napi::Array::New(env, vertices.size());

    for (size_t i = 0; i < vertices.size(); ++i) {
        Vector2 vertex = vertices[i];
        Napi::Object obj = Vector2Wrapper::constructor.New({
            Napi::Number::New(env, vertex.x), 
            Napi::Number::New(env, vertex.y)
        });
        js_array[i] = obj;
    }

    return js_array;
}

void PolygonWrapper::MoveBy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Check if the first argument is an array
    if (info.Length() >= 1 && info[0].IsObject()) {
        Vector2Wrapper* vector_wrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(info[0].As<Napi::Object>());
        this->polygon_->MoveBy(*vector_wrapper->GetInternalInstance());
    } else {
        Napi::TypeError::New(env, "Vector2 object expected").ThrowAsJavaScriptException();
    }
}

void PolygonWrapper::MoveTo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Check if the first argument is an array
    if (info.Length() >= 1 && info[0].IsObject()) {
        Vector2Wrapper* vector_wrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(info[0].As<Napi::Object>());
        this->polygon_->MoveTo(*vector_wrapper->GetInternalInstance());
    } else {
        Napi::TypeError::New(env, "Vector2 object expected").ThrowAsJavaScriptException();
    }
}

void PolygonWrapper::RotateBy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Check if the first argument is an array
    if (info.Length() >= 1 && info[0].IsNumber()) {
        this->polygon_->RotateBy(info[0].As<Napi::Number>().DoubleValue());
    } else {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }
}

Polygon* PolygonWrapper::GetInternalInstance() {
    return this->polygon_;
}