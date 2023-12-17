#include "CollisionWrapper.h"
#include "Vector2Wrapper.h" // Include the Vector2Wrapper if you have one

Napi::FunctionReference CollisionWrapper::constructor;

Napi::Object CollisionWrapper::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Collision", {
        InstanceAccessor("collides", &CollisionWrapper::GetCollides, &CollisionWrapper::SetCollides),
        InstanceAccessor("colPoint1", &CollisionWrapper::GetColPoint1, &CollisionWrapper::SetColPoint1),
        InstanceAccessor("colPoint2", &CollisionWrapper::GetColPoint2, &CollisionWrapper::SetColPoint2)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Collision", func);

    return exports;
}

CollisionWrapper::CollisionWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<CollisionWrapper>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Handle constructor logic, if necessary
    this->collision_ = new Collision(); // or use other constructors as needed
}

CollisionWrapper::~CollisionWrapper() {
    delete this->collision_;
}

// Getter for 'collides'
Napi::Value CollisionWrapper::GetCollides(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, this->collision_->collides);
}

// Setter for 'collides'
void CollisionWrapper::SetCollides(const Napi::CallbackInfo& info, const Napi::Value& value) {
    Napi::Env env = info.Env();
    if (!value.IsBoolean()) {
        Napi::TypeError::New(env, "Boolean expected").ThrowAsJavaScriptException();
    } else {
        this->collision_->collides = value.As<Napi::Boolean>().Value();
    }
}

// Getter for 'colPoint1'
Napi::Value CollisionWrapper::GetColPoint1(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Vector2Wrapper::constructor.New({
        Napi::Number::New(env, this->collision_->col_point1.x), 
        Napi::Number::New(env, this->collision_->col_point1.y)
    });
    return obj;
}

// Setter for 'colPoint1'
void CollisionWrapper::SetColPoint1(const Napi::CallbackInfo& info, const Napi::Value& value) {
    Napi::Env env = info.Env();
    if (!value.IsObject()) {
        Napi::TypeError::New(env, "Object expected").ThrowAsJavaScriptException();
        return;
    }
    Vector2Wrapper* vectorWrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(value.As<Napi::Object>());
    this->collision_->col_point1 = *vectorWrapper->GetInternalInstance();
}

// Getter for 'colPoint2'
Napi::Value CollisionWrapper::GetColPoint2(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Vector2Wrapper::constructor.New({
        Napi::Number::New(env, this->collision_->col_point2.x), 
        Napi::Number::New(env, this->collision_->col_point2.y)
    });
    return obj;
}

// Setter for 'colPoint2'
void CollisionWrapper::SetColPoint2(const Napi::CallbackInfo& info, const Napi::Value& value) {
    Napi::Env env = info.Env();
    if (!value.IsObject()) {
        Napi::TypeError::New(env, "Object expected").ThrowAsJavaScriptException();
        return;
    }
    Vector2Wrapper* vectorWrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(value.As<Napi::Object>());
    this->collision_->col_point2 = *vectorWrapper->GetInternalInstance();
}


Collision* CollisionWrapper::GetInternalInstance() {
    return this->collision_;
}
