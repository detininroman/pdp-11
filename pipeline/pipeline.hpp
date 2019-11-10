class Pipeline {
public:
        getInstance();
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

    Pipeline *instance;
}
