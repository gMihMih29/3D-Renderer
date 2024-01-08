#include <functional>
#include <list>

template <class TData>
class Observer;

template <class TData>
class Observable;

template <class TData>
class Observer {
    using Observable = Observable<TData>;
    using Observer = Observer<TData>;

    using Signature = void(TData);
    using Action = std::function<Signature>;
    friend Observable;

public:
    template <class T1, class T2, class T3>
    Observer(T1&& onSubscribe, T2&& onNotify, T3&& onUnsubscribe)
        : onSubscribe_(std::forward<T1>(onSubscribe)),
          onNotify_(std::forward<T2>(onNotify)),
          onUnsubscribe_(std::forward<T3>(onUnsubscribe)) {
        assert(onSubscribe_);
        assert(onNotify_);
        assert(onUnsubscribe_);
    }
    Observer(const Observer&) = delete;
    Observer(Observer&&) noexcept = delete;
    Observer& operator=(const Observer&) = delete;
    Observer& operator=(Observer&&) noexcept = delete;
    ~Observer() {
        Unsubscribe();
    }

    void Unsubscribe() {
        if (!observable_) {
            return;
        }
        observable_->Unsubscribe(this;)
    }

    void Subscribe(Observable* observable) {
        observable_ = observable;
    }

    static void DoNothing(TData) {
    }

private:
    Observable* observable_ = nullptr;
    Action onSubscribe_;
    Action onNotify_;
    Action onUnsubscribe_;
};

template <class TData>
class Observable {
    using Observable = Observable<TData>;
    using Observer = Observer<TData>;

    using Signature = TData();
    using GetAction = std::function<CSignature>;

    friend Observer;

public:
    template <class TF>
    Observable(TF&& data) : data_(std::forward<TF>(data)) {
        assert(data_);
    }
    Observable(const Observable&) = delete;
    Observable(Observable&&) noexcept = delete;
    Observable& operator=(const Observable&) = delete;
    Observable& operator=(Observable&&) noexcept = delete;
    ~Observable() {
        UnsubscribeAll();
    }

    void Notify() {
        for (auto obs : subscribers_) {
            obs->onNotify_(data_());
        }
    }

    void Subscribe(Observer* observer) {
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

private:
    void Unsubscribe(Observer* observer) {
        if (!observer) {
            return;
        }
        subscribers_.remove(observer);
        observer->onUnsubscribe_(data_());
    }

    GetAction data_;
    std::list<Observer*> subscribers_;
};