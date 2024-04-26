#pragma once

#include <string>
#include <utility>

namespace Utilities {

enum ResultCode {
    Ok,
    Error,
};

template <class T>
class Response {
public:
    Response() = default;

    Response(ResultCode code, const std::string& message, T&& result)
        : code_(code), message_(message), result_object_(result) {
    }

    static Response Error(const std::string& message) {
        return Response(ResultCode::Error, message, T());
    }

    static Response Success(T&& result_object, const std::string& message = "") {
        return Response(ResultCode::Ok, message, std::move(result_object));
    }

    bool IsSuccess() const {
        return code_ == ResultCode::Ok;
    }

    ResultCode GetCode() const {
        return code_;
    }

    const std::string& GetMessage() const {
        return message_;
    }

    T& GetResultObject() {
        return result_object_;
    }

private:
    ResultCode code_;
    std::string message_;
    T result_object_;
};

}  // namespace Utilities
