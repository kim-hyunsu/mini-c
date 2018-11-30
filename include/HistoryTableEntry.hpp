class HistoryTableEntry {
private:

public:
  int lineNumber;
  union {
    int integer;
    float floating;
    void* pointer;
  } value;
};