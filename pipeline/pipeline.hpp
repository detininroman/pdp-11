#include <queue>

class Pipeline {
public:
    void addTicks();
    void addTicks(int);
    Pipeline& getInstance();
private:
    // pc - program counter
    // TODO:: fill parameters and types and may be replace something in public
    void fetch(int pc);
    void decode();
    void loadOp();
    void execute();
    void storeRes();

    // We have a singleton
    void Pipeline();
    void ~Pipeline();
    Pipeline(Pipeline const&) = delete;
    Pipeline& operator= (Pipeline const&) = delete;

    int ticks;
    // TODO:: change according to real data
    const int defaultTicksAddCount = 50;
    std::queue<Task> tasks;
}
