enum ValueType
{
  VALUETYPE_INT = 0,
  VALUETYPE_FLOAT,
  VALUETYPE_POINTER
};

class HistoryTableEntry
{
public:
  int lineNumber;
  ValueType type;
  union {
    int integer;
    float floating;
    void *pointer;
  } value;
};