#ifndef ANIMUS_MEM
#define ANIMUS_MEM

#define MEM_BOARD_TYPE 900
#define MEM_REFRESH_RATE 901
#define MEM_ROW_COUNT 902
#define MEM_COL_COUNT 903
#define MEM_ROW_0 904
#define MEM_ROW_1 905
#define MEM_ROW_2 906
#define MEM_ROW_3 907
#define MEM_ROW_4 908
#define MEM_ROW_5 909
#define MEM_ROW_6 910
#define MEM_ROW_7 911
#define MEM_ROW_8 912
#define MEM_ROW_9 913
#define MEM_ROW_10 914
#define MEM_ROW_11 915
#define MEM_ROW_12 916
#define MEM_ROW_13 917
#define MEM_ROW_14 918
#define MEM_ROW_15 919
#define MEM_ROW_16 920
#define MEM_ROW_17 921
#define MEM_ROW_18 922
#define MEM_ROW_19 923
#define MEM_COL_0 924
#define MEM_COL_1 925
#define MEM_COL_2 926
#define MEM_COL_3 927
#define MEM_COL_4 928
#define MEM_COL_5 929
#define MEM_COL_6 930
#define MEM_COL_7 931
#define MEM_COL_8 932
#define MEM_COL_9 933
#define MEM_COL_10 934
#define MEM_COL_11 935
#define MEM_COL_12 936
#define MEM_COL_13 937
#define MEM_COL_14 938
#define MEM_COL_15 939
#define MEM_COL_16 940
#define MEM_COL_17 941
#define MEM_COL_18 942
#define MEM_COL_19 943
#define MEM_NKRO_MODE 944
#define MEM_LAY_COUNT 945
#define MEM_DYNAMIC_ADDR 950
#include "Global.h"


class CMem
{
private:
public:
  CMem(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void SetKey(byte x, byte y, byte z, byte inputChar, byte inputType);
  void SetRowCount(byte input);
  void SetColCount(byte input);
  void SetLayCount(byte input);
  void SetRowPin(byte pinNo, byte rowNo);
  void SetColPin(byte pinNo, byte colNo);
  void SetBoardType(byte input);
  void SetNKROType(byte input);
  void SetRefreshRate(byte input);

  byte GetKeyData(byte x, byte y, byte z);
  byte GetKeyType(byte x, byte y, byte z);
  byte GetRowCount();
  byte GetColCount();
  byte GetLayCount();
  byte GetRowPin(byte rowNo);
  byte GetColPin(byte colNo);
  byte GetBoardType();
  byte GetNKROType();
  byte GetRefreshRate();

  void Serial(String input);
  void End(void);
};
extern CMem PersMem;

#endif
