#include <cstring>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
int InterpretCommand(char com);
enum type {
  number,
  char_string
};
struct StackVariable {
  type Type;
  int number = 0;
  string char_string = "";
};
//this will prevent is_in_code_block from allowing to run if statements in disabled if statements
int code_block_counter = 0;
//for loop stack
vector<string> ForStack;
//counts for loop iterations
vector<int> ForCounter;
//stores exectuion of for loops
bool is_in_for_loop = false;
//stores code to execute in truth loop, vector to allow loop nesting
vector<string> TruthStack;
//stores execution information for truth loop
vector<bool> TruthBool;
bool is_in_truth_loop;
//to avoid repeating additions to TruthStack and for loops
bool is_reinterpreted = false;
//for comments
bool is_in_comment = false;
//for # function
bool endprg = false;
//for debbuging
char cur_command;
//important global variables
vector<StackVariable> Stack;
//used for special chars entering
bool interpret_next_command = true;
//temp data handler
string data_handler = "";
//for curly brackets support
vector<bool> IfStack;
//bool interpret_code_blocks = false;
bool is_in_code_block = false;
//data handler
StackVariable DataHandler;
//data handler switch
bool is_data_handler_in_use = false;
// copied from StackOverflow
int parseInt(const std::string &s) {
  std::size_t pos;
  int result = std::stoi(s, &pos);
  if (pos != s.size())
    throw std::runtime_error("can't parse integer");
  return result;
}
void PutOnStack(StackVariable stack) {
  //todo: fix zero strings
  int var;
  try {
    if (stack.Type != number) {
      var = parseInt(stack.char_string);
      stack.number = var;
      stack.Type = number;
      stack.char_string = "";
    }
    Stack.push_back(stack);
  } catch (...) {
    stack.Type = char_string;
    Stack.push_back(stack);
  }
}
void PrintErrMessage(int exitcode) {
  switch (exitcode) {
  case 2:
    cout << cur_command << ": "
         << "Stack is empty" << endl;
    break;
  case 3:
    cout << cur_command << ": "
         << "Stack is too small" << endl;
    break;
  case 11:
    cout << cur_command << ": "
         << "Missing {" << endl;
    break;
  case 12:
    cout << cur_command << ": "
         << "Missing [" << endl;
    break;
  case 13:
    cout << cur_command << ": "
         << "Missing (" << endl;
    break;
  case 21:
    cout << cur_command << ": "
         << "Wrong type" << endl;
    break;
  case 22:
    cout << cur_command << ": "
         << "Division by 0" << endl;
    break;
  default:
    break;
  }
}
int PopAndPrint() {
  int x = Stack.size();
  if (x == 0) {
    return 2;
  }
  StackVariable temp = Stack[x - 1];
  if (temp.Type == number) {
    cout << temp.number;
  } else {
    cout << temp.char_string;
  }
  Stack.pop_back();
  return 0;
}
/* EXIT CODES:
 *0 - finished successfully
 *2- stack is empty
 *3 - stack is too small
 * 11 - missing {
 * 12 missing [
 * 13 missing (
 * 21 - wrong type
 * 22 - division by zero
 *
 *
 * */
void DataHandlerUpdate() {
  if (data_handler != "") {
    StackVariable temp;
    temp.char_string = data_handler;
    temp.Type = char_string;
    data_handler = "";
    PutOnStack(temp);
  }
}
int UserInput() {
  StackVariable temp;
  temp.Type = char_string;
  getline(cin, temp.char_string);
  PutOnStack(temp);
  return 0;
}
int RemoveFromStack() {
  if (Stack.size() == 0) {
    return 2;
  }
  Stack.pop_back();
  return 0;
}
int CalculateLenghtofStack() {
  int a = Stack.size();
  StackVariable temp;
  temp.Type = char_string;
  temp.char_string = to_string(a);
  PutOnStack(temp);
  return 0;
}
int BooleanTest() {
  if (Stack.size() == 0) {
    return 2;
  }
  bool out = false;
  int len = Stack.size() - 1;
  if (Stack[len].Type == char_string) {
    out = false;
  } else {
    if (Stack[len].Type == number && Stack[len].number == 0) {
      out = false;
    }
    if (Stack[len].Type == number && Stack[len].number != 0) {
      out = true;
    }
  }
  StackVariable temp;
  temp.Type = char_string;
  if (out == true) {
    temp.char_string = "1";
  } else {
    temp.char_string = "0";
  }
  PutOnStack(temp);
  return 0;
}
int Duplicate() {
  if (Stack.size() == 0) {
    return 2;
  }
  int len = Stack.size() - 1;
  StackVariable temp = Stack[len];
  temp.Type = Stack[len].Type;
  temp.char_string = Stack[len].char_string;
  temp.number = Stack[len].number;
  PutOnStack(temp);
  return 0;
}
int ConvertToASCII() {
  if (Stack.size() == 0) {
    return 2;
  }
  int ascii = 0;
  char cascii;
  int len = Stack.size() - 1;
  if (Stack[len].Type == number) {
    ascii = Stack[len].number;
    cascii = (char)ascii;
    Stack[len].Type = char_string;
    Stack[len].number = 0;
    Stack[len].char_string = cascii;
  } else {
    ascii = Stack[len].char_string.length();
    Stack[len].Type = number;
    Stack[len].number = ascii;
    Stack[len].char_string = "";
  }
  return 0;
}
int IfCommand() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  bool temp = false;
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  if (tmp.Type == tmp2.Type) {
    if (tmp.Type == char_string) {
      if (tmp.char_string == tmp2.char_string) {
        temp = true;
      }
    }
    if (tmp.Type == number) {
      if (tmp.number == tmp2.number) {
        temp = true;
      }
    }
  } else {
    temp = false;
  }
  IfStack.push_back(temp);
  return 0;
}
int SmallerThan() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  bool temp = false;
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  if (tmp.Type == tmp2.Type) {
    if (tmp.Type == char_string) {
      int i = 0;
      int j = 0;
      i = tmp.char_string.length();
      j = tmp2.char_string.length();
      if (i < j) {
        temp = true;
      }
    }
    if (tmp.Type == number && tmp2.Type == number) {
      if (tmp.number < tmp2.number) {
        temp = true;
      }
    }
  } else {
    temp = false;
  }
  IfStack.push_back(temp);
  return 0;
}
int GreaterThan() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  bool temp = false;
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  if (tmp.Type == tmp2.Type) {
    if (tmp.Type == char_string) {
      int i = 0;
      int j = 0;
      i = tmp.char_string.length();
      j = tmp2.char_string.length();
      if (i > j) {
        temp = true;
      }
    }

    if (tmp.Type == number && tmp2.Type == number) {
      if (tmp.number > tmp2.number) {
        temp = true;
      }
    }
  } else {
    temp = false;
  }
  IfStack.push_back(temp);
  return 0;
}
int Add() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  if (tmp.Type == char_string || tmp2.Type == char_string) {
    return 21;
  }
  int out = 0;
  out = tmp2.number + tmp.number;
  StackVariable temp;
  temp.Type = number;
  temp.number = out;
  Stack.pop_back();
  Stack.pop_back();
  PutOnStack(temp);
  return 0;
}
int Divide() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  if (tmp.Type == char_string || tmp2.Type == char_string) {
    return 21;
  }
  if (tmp.number == 0) {
    return 22;
  }
  int out = 0;
  out = tmp2.number / tmp.number;
  StackVariable temp;
  temp.Type = number;
  temp.number = out;
  Stack.pop_back();
  Stack.pop_back();
  PutOnStack(temp);
  return 0;
}
int Modulo() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  if (tmp.Type == char_string || tmp2.Type == char_string) {
    return 21;
  }
  int out = 0;
  out = tmp2.number % tmp.number;
  StackVariable temp;
  temp.Type = number;
  temp.number = out;
  Stack.pop_back();
  Stack.pop_back();
  PutOnStack(temp);
  return 0;
}
int Substract() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  if (tmp.Type == char_string || tmp2.Type == char_string) {
    return 21;
  }
  int out = 0;
  out = tmp2.number - tmp.number;
  StackVariable temp;
  temp.Type = number;
  temp.number = out;
  Stack.pop_back();
  Stack.pop_back();
  PutOnStack(temp);
  return 0;
}
int Multiply() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  if (tmp.Type == char_string || tmp2.Type == char_string) {
    return 21;
  }
  int out = 0;
  out = tmp2.number * tmp.number;
  StackVariable temp;
  temp.Type = number;
  temp.number = out;
  Stack.pop_back();
  Stack.pop_back();
  PutOnStack(temp);
  return 0;
}
int Negate() {
  if (Stack.size() == 0) {
    return 2;
  }
  int len = Stack.size() - 1;
  StackVariable tmp = Stack[len];
  if (tmp.Type == char_string) {
    return 21;
  }
  tmp.number = -tmp.number;
  Stack.pop_back();
  PutOnStack(tmp);
  return 0;
}
int Convert() {
  if (Stack.size() == 0) {
    return 2;
  }
  int len = Stack.size() - 1;
  StackVariable tmp = Stack[len];
  string temp = to_string(tmp.number);
  Stack.pop_back();
  int var;
  try {
    if (tmp.Type != number) {
      var = parseInt(tmp.char_string);
      //  cout << "Debug: " << var << endl;
      tmp.number = var;
      tmp.Type = number;
      tmp.char_string = "";
      Stack.push_back(tmp);
      goto end;
    }

  } catch (...) {
    Stack.push_back(tmp);
    goto end;
  }
  // cout << "here" << endl;
  tmp.char_string = temp;
  tmp.number = 0;
  tmp.Type = char_string;
  Stack.push_back(tmp);
end:
  return 0;
}
int Join() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (Stack.size() <= 1) {
    return 3;
  }
  int len = Stack.size() - 1;
  int len2 = len - 1;
  StackVariable tmp = Stack[len];
  StackVariable tmp2 = Stack[len2];
  string stmp = "";
  string stmp2 = "";
  if (tmp.Type == char_string) {
    stmp = tmp.char_string;
  } else {
    stmp = to_string(tmp.number);
  }
  if (tmp2.Type == char_string) {
    stmp2 = tmp2.char_string;
  } else {
    stmp2 = to_string(tmp2.number);
  }
  string out = stmp2 + stmp;
  Stack.pop_back();
  Stack.pop_back();
  StackVariable temp;
  temp.Type = char_string;
  temp.char_string = out;
  PutOnStack(temp);
  return 0;
}
int DataHandlerAction() {
  if (Stack.size() == 0 && !is_data_handler_in_use) {
    return 2;
  }
  if (is_data_handler_in_use) {
    is_data_handler_in_use = false;
    PutOnStack(DataHandler);
  } else {
    is_data_handler_in_use = true;
    int len = Stack.size() - 1;
    StackVariable tmp = Stack[len];
    DataHandler = tmp;
    Stack.pop_back();
  }
  return 0;
}
int Split() {
  if (Stack.size() == 0) {
    return 2;
  }
  int len = Stack.size() - 1;
  StackVariable tmp = Stack[len];
  if (tmp.Type == number) {
    return 21;
  }
  int n = tmp.char_string.length();

  // declaring character array
  char char_array[n + 1];

  // copying the contents of the
  // string to char array
  strcpy(char_array, tmp.char_string.c_str());
  Stack.pop_back();
  StackVariable temp;
  temp.Type = char_string;
  for (int i = 0; i < n; i++) {
    temp.char_string = char_array[i];
    PutOnStack(temp);
  }

  return 0;
}
int RandomNumber() {
  int tmp = rand();
  StackVariable temp;
  temp.Type = number;
  temp.number = tmp;
  PutOnStack(temp);
  return 0;
}

int ForLoop() {
  if (Stack.size() == 0) {
    return 2;
  }
  int len = Stack.size() - 1;
  StackVariable tmp = Stack[len];
  if (tmp.Type != number) {
    return 21;
  }
  is_in_for_loop = true;
  int counter = 0;
  counter = tmp.number;
  ForStack.push_back(";");
  ForCounter.push_back(counter);
  is_in_for_loop = true;
  Stack.pop_back();
  return 0;
}
int EndForLoop() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (ForStack.size() == 0 || ForCounter.size() == 0) {
    return 13;
  }
  int where = ForCounter.size() - 1;
  int count = ForCounter[ForCounter.size() - 1];
  string s = ForStack[ForStack.size() - 1];
  //cout << "Debug: " << s << endl;
  int n = s.length();
  // declaring character array
  char char_array[n + 1];
  // copying the contents of the
  // string to char array
  //is_in_for_loop = false;
  strcpy(char_array, s.c_str());
  for (int i = 1; i < count; i++) {
    for (int j = 0; j < n; j++) {
      //cout << "For: " << j << endl;
      InterpretCommand(char_array[j]);
    }
  }
  //ForStack.pop_back();
  //ForCounter.pop_back();
  ForCounter.erase(ForCounter.begin() + where);
  ForStack.erase(ForStack.begin() + where);
  if (ForCounter.size() == 0 && ForStack.size() == 0) {
    is_in_for_loop = false;
  } else {
    is_in_for_loop = true;
  }
  return 0;
}
int TruthLoop() {
  if (Stack.size() == 0) {
    return 2;
  }
  int len = Stack.size() - 1;
  StackVariable tmp = Stack[len];
  is_in_truth_loop = true;
  bool execute = false;
  if (tmp.Type == number) {
    if (tmp.number != 0) {
      execute = true;
    }
  } else {
    execute = false;
  }
  TruthStack.push_back(";");
  TruthBool.push_back(execute);
  return 0;
}
int EndTruthLoop() {
  if (Stack.size() == 0) {
    return 2;
  }
  if (TruthStack.size() == 0 || TruthBool.size() == 0) {
    if (TruthBool.size() != 0) {
      TruthStack.pop_back();
      TruthBool.pop_back();
    }
    if (TruthStack.size() == 0) {
      is_in_truth_loop = false;
    }
    return 13;
  }
  int len = Stack.size() - 1;
  StackVariable tmp = Stack[len];
  is_in_truth_loop = true;
  bool execute = false;
  if (tmp.Type == number) {
    if (tmp.number != 0) {
      execute = true;
    }
  } else {
    execute = false;
  }
  //cout << "EX: " << execute << endl;
  if (execute == false) {
    if (TruthBool.size() != 0) {
      TruthStack.pop_back();
      TruthBool.pop_back();
    }
    if (TruthStack.size() == 0) {
      is_in_truth_loop = false;
    }
  } else {
    // cout << "here" << endl;
    string s = TruthStack[TruthStack.size() - 1];
    //cout << "Debug: " << s << endl;
    int n = s.length();
    // declaring character array
    char char_array[n + 1];
    // copying the contents of the
    // string to char array
    strcpy(char_array, s.c_str());
    is_reinterpreted = true;
    for (int i = 0; i < n; i++) {
      // cout << "Truth Loop: " << endl;
      InterpretCommand(char_array[i]);
    }
    is_reinterpreted = false;
  }

  return 0;
}
int InterpretCommand(char com) {
  int out = 0;
  cur_command = com;
  //cout << "Command: " << com << endl;
  /*cout << "Code Block Counter: " << code_block_counter << endl;
  if (IfStack.size() != 0) {
    cout << "If Stack Size: " << IfStack.size() << endl;
    cout << "If Stack: " << IfStack[IfStack.size() - 1] << endl;
  }*/
  bool bollean = false;
  if (IfStack.size() != 0) {
    int s = IfStack.size() - 1;
    bollean = IfStack[s];
  }
  if (com == '{') {
    code_block_counter++;
  }
  if (com == '}') {
    code_block_counter--;
  }

  bool in_truth_loop = false;
  if (TruthBool.size() != 0) {
    int s = TruthBool.size() - 1;
    in_truth_loop = TruthBool[s];
    //cout << in_truth_loop << endl;
  }
  if (!interpret_next_command) {
    data_handler = data_handler + com;
    interpret_next_command = true;
    goto end;
  }
  if (is_in_comment) {
    if (com == '\"') {
      is_in_comment = false;
    }
    goto end;
  }
  if (in_truth_loop && is_in_truth_loop && !is_reinterpreted) { // this will cause trouble later
    TruthStack[TruthStack.size() - 1] = TruthStack[TruthStack.size() - 1] + com;
    //cout << TruthStack[0] << endl;
  }

  if (!in_truth_loop && is_in_truth_loop && com != ')') {
    goto end;
  }
  if (bollean == false && is_in_code_block == true && com != '}') {
    goto end;
  }
  if (is_in_for_loop && com != ']') {
    ForStack[ForStack.size() - 1] = ForStack[ForStack.size() - 1] + com;
  }
  if (is_in_for_loop && com == ']') {
    if (ForStack.size() > 1) {
      ForStack[ForStack.size() - 2] = ForStack[ForStack.size() - 2] + ForStack[ForStack.size() - 1];
      ForStack[ForStack.size() - 2] = ForStack[ForStack.size() - 2] + com;
    }
  }
  switch (com) {
  case '[':
    DataHandlerUpdate();
    out = ForLoop();
    break;
  case ']':
    DataHandlerUpdate();
    out = EndForLoop();
    break;
  case '(':
    DataHandlerUpdate();
    out = TruthLoop();
    break;
  case ')':
    DataHandlerUpdate();
    //cout << "End" << endl;
    out = EndTruthLoop();
    break;
  case '\'':
    DataHandlerUpdate();
    out = RandomNumber();
    break;
  case '|':
    DataHandlerUpdate();
    out = Split();
    break;
  case '&':
    DataHandlerUpdate();
    out = DataHandlerAction();
    break;
  case '^':
    DataHandlerUpdate();
    out = Join();
    break;
  case '~':
    DataHandlerUpdate();
    out = Convert();
    break;
  case '<':
    DataHandlerUpdate();
    out = SmallerThan();
    break;
  case '>':
    DataHandlerUpdate();
    out = GreaterThan();
    break;
  case '_':
    DataHandlerUpdate();
    out = Negate();
    break;
  case '+':
    DataHandlerUpdate();
    out = Add();
    break;
  case '-':
    DataHandlerUpdate();
    out = Substract();
    break;
  case '/':
    DataHandlerUpdate();
    out = Divide();
    break;
  case '*':
    DataHandlerUpdate();
    out = Multiply();
    break;
  case '%':
    DataHandlerUpdate();
    out = Modulo();
    break;
  case '#':
    endprg = true;
    break;
  case '!':
    DataHandlerUpdate();
    out = PopAndPrint();
    break;
  case ';':
    DataHandlerUpdate();
    break;
  case ':':
    DataHandlerUpdate();
    out = Duplicate();
    break;
  case '\\':
    //data_handler = data_handler + com;
    interpret_next_command = false;
    break;
  case '?':
    DataHandlerUpdate();
    out = UserInput();
    break;
  case ',':
    DataHandlerUpdate();
    out = RemoveFromStack();
    break;
  case '.':
    DataHandlerUpdate();
    out = BooleanTest();
    break;
  case '@':
    DataHandlerUpdate();
    out = CalculateLenghtofStack();
    break;
  case '$':
    DataHandlerUpdate();
    out = ConvertToASCII();
    break;
  case '=':
    DataHandlerUpdate();
    out = IfCommand();
    break;
  case '{':
    DataHandlerUpdate();
    is_in_code_block = true;
    break;
  case '}': //to be changed TEMPORARY
    DataHandlerUpdate();
    if (code_block_counter == 0) {
      is_in_code_block = false;
    }
    if (code_block_counter < 0) {
      return 11; //lol
    }
    if (IfStack.size() != 0) {
      IfStack.pop_back();
    }

    break;
  case '\"':
    if (is_in_comment) {
      is_in_comment = false;
    } else {
      is_in_comment = true;
    }
    break;
  default:
    data_handler = data_handler + com;
    break;
  }
end:
//temorporay i guess
ifloop:
  if (IfStack.size() < code_block_counter) {
    //fix for double false if statements
    IfStack.push_back(false);
    if (IfStack.size() < code_block_counter) {
      goto ifloop;
    }
  }

  // cout << "Data: " << data_handler << endl;
  return out;
}
int InterpretCode(string path) {
  //out << path << endl;
  fstream file;
  file.open(path, ios::in);
  if (!file) {
    cout << "File not found: " << path << endl;
    return 1;
  }
  char command;
  //stringstream buffer;
  //buffer << file.rdbuf();
  file.unsetf(ios_base::skipws);
  while (!file.eof()) {
    if (endprg) {
      file.close();
      return 0;
    }
    file >> command;
    //cout << "Debug: " << command << endl;
    int out = InterpretCommand(command);
    PrintErrMessage(out);
    //inserts separator at the end of execution to avoid doubled last instruction execution due to bad eof functioning - workaround
    command = ';';
  }
  file.close();
  return 0;
}
int main(int argc, char **argv) {
  srand(time(NULL));
  if (argc == 1) {
    cout << "Nothing to do" << endl;
  }
  if (argc == 2) {
    //cout << argv[1] << endl;
    string var = argv[1];
    //cout << var << endl;
    if (var == "--help") {
      cout << "USAGE:" << endl
           << "stec [INPUT FILE]" << endl;
      cout << "--help  - Prints help message" << endl;
      cout << "--version - Prints version info" << endl;
      cout << "Please use one argument at a time" << endl;
      return 0;
    }
    if (var == "--version") {
      cout << "Stackative Interpreter v1.0 for Stackative-21A" << endl;
      return 0;
    }
    int out = 0;
    out = InterpretCode(var);
    return out;
  }
  return 0;
}
