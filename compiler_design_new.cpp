#include <iostream>
#include <cstring>
#include <stack>
#include <map>
#include <vector>
using namespace std;

map<string,int> link;
vector<string> var_store;

bool check_number(string str)
{ int count =0;
  for(int j=0;j<str.length();j++)
  { if(str[j] >= 48 && str[j] <= 57) {count++;}
  }
  if(count == str.length())
  { return true;
  }
  else {return false;}
}

int assign_number(string str)
{ int n;
    if(check_number(str))
    { n = stoi(str);
    }
    else
    {
      n = link[str];
    }
  return n;
}

bool check_var(string str)
{ int count_var = 0;
  for(int j=0;j<str.length();j++)
  { if( (str[j] >= 97 && str[j] <= 122) || (str[j] >= 65 && str[j] <= 90) || str[j] == '_' || (str[j] >= 48 && str[j] <= 57) )
    { count_var++; }
  }
  if(count_var == str.length())
  { return true;
  }
  else {return false;}
}

void segregate(string str,string store[],int &n)
{ int count_var = 0;
  if(str == "int")
  { store[n] = "int";
    n++;
  }
  else if(str == "cout")
  { store[n] = "cout";
    var_store.push_back(str);
    n++;
  }
  else if(str == "<<")
  { store[n] = "seperator";
    n++;
  }
  else if(str[0] >= 48 && str[0] <= 57)
  { if(check_number(str))
    { store[n] = "num";
      var_store.push_back(str);
      n++;
    }
    else
    { store[n] = "other";
      n++;
    }
  }
  else if( (str[0] >= 97 && str[0] <= 122) || (str[0] >= 65 && str[0] <= 90) || str[0] == '_' )
  { if(check_var(str))
    { store[n] = "var";
      var_store.push_back(str);
      n++;
    }
    else
    { store[n] = "other";
      n++;
    }
  }
  else
  { store[n] = "other";
    n++;
  }
}

void lexer(string s,string store[],int &n)
{ int point =0;
  for(int i=0;i<s.length();i++)
  { if(s[i] == '(' || s[i] == ')' || s[i] == '/' || s[i] == ',' || s[i] == '=' || s[i] == ';' || s[i] == ' ')
    { if(point == i)
      { point++;
      }
      else
      { string str = s.substr(point,i-point);
        segregate(str,store,n);
        point = i+1;
      }
      if(s[i] == '(')
      { store[n] = "lparen";
        var_store.push_back(store[n]);
        n++;
      }
      else if(s[i] == ')')
      { store[n] = "rparen";
        var_store.push_back(store[n]);
        n++;
      }
      else if(s[i] == '/')
      { store[n] = "division";
        var_store.push_back(store[n]);
        n++;
      }
      else if(s[i] == ',')
      { store[n] = "comma";
        var_store.push_back(store[n]);
        n++;
      }
      else if(s[i] == '=')
      { store[n] = "eq";
        var_store.push_back(store[n]);
        n++;
      }
      else if(s[i] == ';')
      { store[n] = "eol";
        var_store.push_back(store[n]);
        n++;
      }
    }
  }
}

void parser(string store[],int n,bool verbose_flag)
{ for(int i=0;i<n;i++)
  { if(store[i] == "other")
    { cout << "invalid syntax" << endl;
      exit(0);
    }
  }
  stack<string> sack;
  sack.push("S");
  int i=0;
  for(;i<n;)
  { if(sack.top() == "S" && store[i] == "int")
    { sack.pop();
      sack.push("eol");
      sack.push("A");
     if(verbose_flag) {cout << "S->A;" << endl;}
    }
    else if(sack.top() == "S" && store[i] == "cout")
    { sack.pop();
      sack.push("eol");
      sack.push("X");
      sack.push("var");
      sack.push("seperator");
      sack.push("cout");
     if(verbose_flag) {cout << "S-> cout sep var X;" << endl;}
    }
    else if(sack.top() == "X" && store[i] == "seperator")
    { sack.pop();
      sack.push("X");
      sack.push("var");
      sack.push("seperator");
    if(verbose_flag) {cout << "X->sep var X" << endl;}
    }
    else if(sack.top() == "X" && store[i] == "eol")
    { sack.pop();
     if(verbose_flag) {cout << "X->E" << endl;}
    }
    else if(sack.top() == "A" && store[i] == "int")
    { sack.pop();
      sack.push("B");
      sack.push("eq");
      sack.push("var");
      sack.push("int");
     if(verbose_flag) {cout << "A->int var eq B" << endl;}
    }
    else if(sack.top() == "B" && (store[i] == "lparen" || store[i] == "num" || store[i] == "var") )
    { sack.pop();
      sack.push("B1");
      sack.push("C");
     if(verbose_flag) {cout << "B->CB1" << endl;}
    }
    else if(sack.top() == "B1" && store[i] == "division")
    { sack.pop();
      sack.push("B1");
      sack.push("C");
      sack.push("division");
    if(verbose_flag) {cout << "B1->/CB1" << endl;}
    }
    else if(sack.top() == "B1" && store[i] == "comma")
    { sack.pop();
      sack.push("A");
      sack.push("comma");
     if(verbose_flag) {cout << "B1->,A" << endl;}
    }
    else if(sack.top() == "B1" && (store[i] == "eol" || store[i] == "rparen"))
    { sack.pop();
     if(verbose_flag) {cout << "B1->e" << endl;}
    }
    else if(sack.top() == "C" && store[i] == "lparen")
    { sack.pop();
      sack.push("rparen");
      sack.push("B");
      sack.push("lparen");
     if(verbose_flag) {cout << "C->(B)" << endl;}
    }
    else if(sack.top() == "C" && store[i] == "num")
    { sack.pop();
      sack.push("num");
     if(verbose_flag) {cout << "C->num" << endl;}
    }
    else if(sack.top() == "C" && store[i] == "var")
    { sack.pop();
      sack.push("var");
     if(verbose_flag) {cout << "C->var" << endl;}
    }
    else if(sack.top() == store[i])
    { sack.pop();
      i++;
     if(verbose_flag) {cout << "pop" << endl;}
    }
    else
    { cout << "invalid grammar" << endl;
      exit(0);
    }
  }
  if(!sack.empty())
  { cout << "invalid grammar" << endl;
    exit(0);
  }
}

int find_terminator(int i)
{ int pos = 0;
      for(int j=i+2;j<var_store.size();j++)
      { if(var_store[j] == "comma" || var_store[j] == "eol")
        { pos = j;
          break;
        }
      }
  return pos;
}

void solve(int start,int ennd)
{ int x_start = -1,x_end = -1;
  int final_return;
  for(int i=start;i<ennd;i++)
  { if(var_store[i]=="lparen")
    { x_start = i;
    }
    if(var_store[i] == "rparen")
    { x_end = i;
      // delete positions of x_start and x_end
      var_store.erase(var_store.begin()+x_start);
      var_store.erase(var_store.begin()+x_end-1);
      break;
    }

  }
  if( x_start != -1 && x_end != -1)
  { solve(x_start,x_end-1);}
  else
  { if(ennd == start + 1)
    { int n3;
      n3 = assign_number(var_store[start]);
      final_return = n3;
      var_store[start] = to_string(final_return);
    }
    else
    { int n1,n2;
      n1 = assign_number(var_store[start]);
      n2 = assign_number(var_store[start+2]);
      if(n2 == 0)
      { cout << "cannot divide by 0" << endl;
        exit(0);
      }
      else { final_return = n1 / n2; }
      var_store[start] = to_string(final_return);
      // delete var_store[ennd-1] and [start+1]
      var_store.erase(var_store.begin()+start+1);
      var_store.erase(var_store.begin()+start+1);
    }


  }
}

void allote()
{ for(int i=0;i<var_store.size();i++)
  { if(var_store[i] == "eq" && (var_store[i+2] == "comma" || var_store[i+2] == "eol"))
    { if( check_number(var_store[i+1]) )
      { link[var_store[i-1]] = stoi(var_store[i+1]);
      }
      else if( check_var(var_store[i+1]) )
      { // find value of var_store[i+1] in link and if value present then link[var_store[i-1]] = value else return "value unassigned"
        string s = var_store[i+1];
        if(link.find(s) != link.end())
        { link[var_store[i-1]] = link[s];
        }
        //link[var_store[i-1]] = link[s];
        else
        { cout << "value of " << s << " is unassigned" << endl;
        }
      }
    }
    else if(var_store[i] == "eq" && (var_store[i+2] != "comma" || var_store[i+2] != "eol"))
    { // find pos of comma in var_store and solve from i+1 to pos
      int pos = find_terminator(i);
      // recursion required
      while(i+2 != pos)
      { solve(i+1,pos);
        pos = find_terminator(i);
        for(int k=0;k<var_store.size();k++)
        { cout << var_store[k] << " ";
        }
        cout << endl;
      }
      link[var_store[i-1]] = stoi(var_store[i+1]);
    }
  }
  // print function code
  if(var_store[0] == "cout")
  { var_store.pop_back();
    for(int i=1;i<var_store.size();i++)
    { // if var_store[i] is in map then print else print given value not assigned
      if(link.find(var_store[i]) != link.end())
      { cout << link[var_store[i]] << " ";
      }
      else
      { cout << "\nvalue of " << var_store[i] << " is not assigned" << endl;
      }
    }
  }
}

int main(int argc, char** argv)
{ bool verbose_flag = false;
  if(argc > 1)
  { string str = argv[1];
    if(str == "-v") { verbose_flag = true;}
  }
  while(1)
  { string s;
    getline(cin,s);
    if(s.empty())
    { continue;}
    else
    {
    string store[s.length()];
    int store_len =0;
    lexer(s,store,store_len);
    if(store_len == 0) {continue;}
    if(verbose_flag)
    { cout << "tokens are: ";
      for(int i=0;i<store_len;i++)
      { cout << store[i] << " ";
      }
      cout << endl;
    }
    parser(store,store_len,verbose_flag);
    allote();
    var_store.clear();
    }

  }
  return 0;
}

