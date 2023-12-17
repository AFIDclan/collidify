#include "Vector2Wrapper.h"

Napi::FunctionReference Vector2Wrapper::constructor;

Napi::Object Vector2Wrapper::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Vector2", {
        InstanceMethod("Magnitude", &Vector2Wrapper::Magnitude),
        InstanceMethod("Dot", &Vector2Wrapper::Dot),
        InstanceMethod("Normalize", &Vector2Wrapper::Normalize),
        InstanceMethod("Clone", &Vector2Wrapper::Clone),
        InstanceAccessor("x", &Vector2Wrapper::GetX, &Vector2Wrapper::SetX),
        InstanceAccessor("y", &Vector2Wrapper::GetY, &Vector2Wrapper::SetY),
        InstanceMethod("toJSON", &Vector2Wrapper::toJSON)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Vector2", func);

    return exports;
}

Vector2Wrapper::Vector2Wrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Vector2Wrapper>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return;
    }

    double x = info[0].As<Napi::Number>().DoubleValue();
    double y = info[1].As<Napi::Number>().DoubleValue();
    this->vector_ = new Vector2(x, y);
}

Vector2Wrapper::~Vector2Wrapper() {
    delete this->vector_;
}

Napi::Value Vector2Wrapper::Magnitude(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    double returnValue = this->vector_->Magnitude();

    return Napi::Number::New(env, returnValue);
}

Napi::Value Vector2Wrapper::Dot(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Vector2 object expected").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Object obj = info[0].As<Napi::Object>();
    Vector2Wrapper* otherWrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(obj);
    Vector2* otherVector = otherWrapper->GetInternalInstance();

    double returnValue = this->vector_->Dot(*otherVector);

    return Napi::Number::New(env, returnValue);
}

Napi::Value Vector2Wrapper::Normalize(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Vector2 normalized = this->vector_->Normalize();

    Napi::Object obj = Vector2Wrapper::constructor.New({});
    Vector2Wrapper* wrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(obj);
    wrapper->SetInternalInstance(&normalized);

    return obj;
}

Napi::Value Vector2Wrapper::Clone(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Clone by instantiating a new Vector2 with the same values
    Napi::Object obj = Vector2Wrapper::constructor.New({Napi::Number::New(env, this->vector_->x), Napi::Number::New(env, this->vector_->y)});
    Vector2Wrapper* wrapper = Napi::ObjectWrap<Vector2Wrapper>::Unwrap(obj);

    return obj;
}


Napi::Value Vector2Wrapper::GetX(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    double x = this->vector_->x;
    return Napi::Number::New(env, x);
}

void Vector2Wrapper::SetX(const Napi::CallbackInfo& info, const Napi::Value& value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    } else {
        this->vector_->x = value.As<Napi::Number>().DoubleValue();
    }
}

Napi::Value Vector2Wrapper::GetY(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    double y = this->vector_->y;
    return Napi::Number::New(env, y);
}

void Vector2Wrapper::SetY(const Napi::CallbackInfo& info, const Napi::Value& value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    } else {
        this->vector_->y = value.As<Napi::Number>().DoubleValue();
    }
}


Napi::Value Vector2Wrapper::toJSON(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("x", this->vector_->x);
    obj.Set("y", this->vector_->y);
    return obj;
}

Vector2* Vector2Wrapper::GetInternalInstance() {
    return this->vector_;
}

void Vector2Wrapper::SetInternalInstance(Vector2* vector) {
    this->vector_ = vector;
}