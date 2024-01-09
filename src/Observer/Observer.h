#pragma once

#include <cassert>
#include <functional>
#include <list>
#include <type_traits>
namespace NSObserverDetail {

template <class TData>
bool constexpr isArithmetic = std::is_arithmetic_v<TData>;

template <class TData>
bool constexpr isPointer = std::is_pointer_v<TData>;

template <class TData>
bool constexpr isEnum = std::is_enum_v<TData>;

template <class TData>
bool constexpr isSimpleClass = isArithmetic<TData> || isPointer<TData> || isEnum<TData>;
}  // namespace NSObserverDetail

struct CByValue;
struct CByReference;

namespace NSObserverDetail {

template <class TData, class TSendBy>
struct CDataSentByImpl;

template <class TData>
struct 
CDataSentByImpl<TData, CByValue> {
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
    std::conditional_t<std::is_same_v<TData, void>, void, typename AutoSendByImpl<isSimpleClass<TData>>::CType>;

}  // namespace NSObserverDetail

template <class TData, class TSendBy>
class CObserver;

template <class TData, class TSendBy>
class CObservable;

template <class TData>
class Observer;

template <class TData>
class Observable;

template <class TData, class TSendBy = NSObserverDetail::AutoSendBy<TData>>
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
    CObserver(T1&& onSubscribe, T2&& onNotify, T3&& onUnsubscribe)
        : onSubscribe_(std::forward<T1>(onSubscribe)),
          onNotify_(std::forward<T2>(onNotify)),
          onUnsubscribe_(std::forward<T3>(onUnsubscribe)) {
        assert(onSubscribe_);
        assert(onNotify_);
        assert(onUnsubscribe_);
    }
    CObserver(const CObserver&) = delete;
    CObserver(CObserver&&) noexcept = delete;
    CObserver& operator=(const CObserver&) = delete;
    CObserver& operator=(CObserver&&) noexcept = delete;
    ~CObserver() {
        Unsubscribe();
    }

    void Unsubscribe() {
        if (!observable_) {
            return;
        }
        observable_->Unsubscribe(this);
    }

    void Subscribe(CObservable* observable) {
        observable_ = observable;
    }

    static void DoNothing(CDataSentBy) {
    }

private:
    CObservable* observable_ = nullptr;
    CAction onSubscribe_;
    CAction onNotify_;
    CAction onUnsubscribe_;
};

template <class TData, class TSendBy = NSObserverDetail::AutoSendBy<TData>>
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
    CObservable(TF&& data) : data_(std::forward<TF>(data)) {
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
            obs->onNotify_(data_());
        }
    }

    void Subscribe(CObserver* observer) {
        if (observer == nullptr) {
            return;
        }
        subscribers_.push_back(observer);
        observer->Subscribe(this);
        observer->onSubscribe_(data_());
    }

    void UnsubscribeAll() {
        while (!subscribers_.empty()) {
            subscribers_.front()->Unsubscribe();
        }
    }

    CDataSentBy Data() const;

private:
    void Unsubscribe(CObserver* observer) {
        if (!observer) {
            return;
        }
        subscribers_.remove(observer);
        observer->onUnsubscribe_(data_());
    }

    CGetAction data_;
    CSubscribers subscribers_;
};