class NG {
public:
    NG() {}
    static NG &getInstance() {
        static NG instance;  // Bad
        return instance;
    }
    NG(NG const &)             = delete;
    void operator=(NG const &) = delete;
};

class Good {
public:
    static Good &getInstance() {
        static Good instance;  // Don't catch!
        return instance;
    }
    Good(Good const &)           = delete;
    void operator=(Good const &) = delete;

private:
    Good() {}
};
