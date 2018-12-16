# Project: Interpreter Implementation
## Members
|  이름  |   학번   |                                                기여                                                | 기여도 |
|:------:|:--------:|:--------------------------------------------------------------------------------------------------:|:------:|
| 서한솔 | 20140285 | 자료구조(콜스택, 히스토리, 심볼테이블 등) 구현, 파서 구현, Control flow 인터프리팅 구현, 중간 발표 |  55%   |
| 김현수 | 20140168 | Prompt 인터페이스 구현, AST 인터프리팅 구현, print/trace 로직 구현                                 | 40%    |
| 백대현 | 20183269 | 스캐너(Lexer.cpp) 구현과 중간발표 후 연락 부재                                                     | 5%     |
## Execution and Test
```powershell
> .\bin\minic.exe .\example1.c
> .\bin\minic.exe .\example2.c
> .\bin\minic.exe .\example3.c
```
## Data Structures
| 자료구조     | 설명                                                                                                    | 예시           |
|--------------|---------------------------------------------------------------------------------------------------------|----------------|
| Tokens       | NUM, REAL, INC, DEC, EQUAL, ..., PRINTF 각각의 object                                                   | 0,1,2,.. -> NUM |
| ParseTree    | nonterminal이름, 라인번호, value, 부모노드, 형제노드, 자식노드 들을 저장하는 트리(AST)                  |                |
| SymbolTable  | 변수이름, 타입, assigned여부, level, scope, 히스토리, 주소들을 저장하는 리스트                          |                |
| TypeObject   | Type을 recursive하게 정의하기 위해 type, baseType, arraySize, parameterType, returnType을 저장하는 트리 | int **a[0];    |
| HistoryTable | trace를 수행하기위해 각 심볼마다 정의되어 라인번호와 값을 해당 변수가 수정될 때마다 기록하는 리스트     |                |
| CallStack    | 현재 프로시져에서 다른 프로시져로 넘어가기 위해 현재 parseTree(AST)와 level을 저장하는 스택             |                |


우리의 구현체는 라인번호 1개 당 1 개의 statement를 가진다고 가정하고 분기문이나 프로시져를 전환할 때마다 돌아올 라인번호가 아닌 statement 위치(parseTree pointer)를 저장한다.
## Implementation
### next command
1. next 에 따라붙는 번호 만큼 statement를 실행시킨다.
1. statement를 실행시킬 때 declaration을 만나면 symbol table에 기록을 해준다.
1. assignment를 만나면 등호 왼쪽 변수의 주소를 계산하고 등호 오른쪽 변수의 값을 계산하여 해당 주소에 값을 저장해준다.
1. 