#pragma once

#include <cassert>
#include <functional>
#include <list>
#include <type_traits>

namespace Renderer {

namespace NSObserverDetail {

template <class TData>
bool constexpr IsArithmetic = std::is_arithmetic_v<TData>;

template <class TData>
bool constexpr IsPointer = std::is_pointer_v<TData>;

template <class TData>
bool constexpr IsEnum = std::is_enum_v<TData>;

template <class TData>
bool constexpr IsSimpleClass = IsArithmetic<TData> || IsPointer<TData> || IsEnum<TData>;
}  // namespace NSObserverDetail

struct CByValue;
struct CByReference;

namespace NSObserverDetail {

template <class TData, class TSendBy>
struct CDataSentByImpl;

template <class TData>
struct CDataSentByImpl<TData, CByValue> {
    using CType = TData;
};

template <class TData>
struct CDataSentByImpl<TData, CByReference> {
    using CType = const TData&;
};

template <class TData, class TSendBy>
using CDataSentBy = typename CDataSentByImpl<TData, TSendBy>::CType;

template <bool TFlag>
struct AutoSendByImpl;

template <>
struct AutoSendByImpl<true> {
    using CType = CByValue;
};

template <>
struct AutoSendByImpl<false> {
    using CType = CByReference;
};

template <class TData>
using AutoSendBy =
    std::conditional_t<std::is_same_v<TData, void>, void, typename AutoSendByImpl<IsSimpleClass<TData>>::CType>;

}  // namespace NSObserverDetail

template <class TData>
using AutoSendBy = NSObserverDetail::AutoSendBy<TData>;

template <class TData, class TSendBy>
class CObserver;

template <class TData, class TSendBy>
class CObservable;

template <class TData, class TSendBy = AutoSendBy<TData>>
class CObserver {
    using CData = TData;
    using CSendBy = TSendBy;

    using CObservable = CObservable<CData, CSendBy>;

    using CDataSentBy = NSObserverDetail::CDataSentBy<CData, CSendBy>;
    using CSignature = void(CDataSentBy);
    using CAction = std::function<CSignature>;

    friend CObservable;

public:
    template <class T1, class T2, class T3>
    explicit CObserver(T1&& on_subscribe, T2&& on_notify, T3&& on_unsubscribe)
        : on_subscribe_(std::forward<T1>(on_subscribe)),
          on_notify_(std::forward<T2>(on_notify)),
          on_unsubscribe_(std::forward<T3>(on_unsubscribe)) {
        assert(on_subscribe_);
        assert(on_notify_);
        assert(on_unsubscribe_);
    }
    CObserver(const CObserver&) = delete;
    CObserver(CObserver&&) noexcept = delete;
    CObserver& operator=(const CObserver&) = delete;
    CObserver& operator=(CObserver&&) noexcept = delete;
    ~CObserver() {
        Unsubscribe();
    }

    void Unsubscribe() {
        if (!IsSubscribed())
            return;
        observable_->Detach_(this);
        observable_ = nullptr;
    }

    bool IsSubscribed() const {
        return Observable_ != nullptr;
    }

    static void DoNothing(CDataSentBy) {
    }

private:
    void Subscribe_(CObservable* observable) {
        assert(observable);
        observable_ = observable;
    }

    CObservable* observable_ = nullptr;
    CAction on_subscribe_;
    CAction on_notify_;
    CAction on_unsubscribe_;
};

template <class TData, class TSendBy = AutoSendBy<TData>>
class CObservable {
    using CData = TData;
    using CSendBy = TSendBy;

    using CObserver = CObserver<CData, CSendBy>;
    using CObserversContainer = std::list<CObserver*>;

    using CDataSentBy = NSObserverDetail::CDataSentBy<CData, CSendBy>;
    using CSignature = CDataSentBy();
    using CGetAction = std::function<CSignature>;

    using CSubscribers = std::list<CObserver*>;

    friend CObserver;

public:
    template <class TF>
    explicit CObservable(TF&& data) : data_(std::forward<TF>(data)) {
        assert(data_);
    }
    CObservable(const CObservable&) = delete;
    CObservable(CObservable&&) noexcept = delete;
    CObservable& operator=(const CObservable&) = delete;
    CObservable& operator=(CObservable&&) noexcept = delete;
    ~CObservable() {
        UnsubscribeAll();
    }

    void Notify() {
        for (auto obs : subscribers_) {
            obs->on_notify_(data_());
        }
    }

    void Subscribe(CObserver* obs) {
        assert(obs);
        if (obs->IsSubscribed())
            obs->Unsubscribe();
        subscribers_.push_back(obs);
        obs->Subscribe_(this);
        obs->on_subscribe_(data_());
    }

    void UnsubscribeAll() {
        while (!subscribers_.empty()) {
            subscribers_.front()->Unsubscribe();
        }
    }

private:
    void Detach_(CObserver* obs) {
        assert(obs);
        observer->on_unsubscribe_(data_());
        subscribers_.remove(observer);
    }

    CGetAction data_;
    CSubscribers subscribers_;
};

}  // namespace Renderer
