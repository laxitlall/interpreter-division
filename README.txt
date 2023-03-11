WHAT IT DOES:-
this interpreter works with tokens, lexical analyzer, checks syntax and expressions that divide integer from integer.
it tokenizes a single line of words and store it in array
the array is then passes to parser function which checks whether the line tokens are syntactically correct or not.

HOW TO RUN IT:-
the given program has 2 mode i)non-verbose mode ii)verbose_mode
if command line argument is only ./a.out 
   then code will run without showing any background detail
else if command line argument is ./a.out -v ( v is for verbose mode )
   then on executing a single line the background details like tokens and grammar checking process will be shown

g++ compiler_design_new.cpp
./a.out          (for non verbose mode)
./a.out -v       (for verbose mode)

basic input will be-
int a = number_1, int b = number_2, int c = number_3;
int x = a/(b/c);
cout << x;

RULES:-
i)  any number of integer declaration can be done
ii) it is valid to initialize a variable and equate it to other variable like
    int a =4;
    int x =a; (valid)

    but not valid if variable in not initialized and equated to other variable like
    int x =a; (invalid)
iii)empty parrenthesis is not allowed like
    int x = (); (invalid)
iv) integer declaration to be started with int even after comma
    int a =10, b=2;  (invalid)
v)  any number of expression can be calculated in a single line like
    int x = a/(b/c), int y = (a/b)/c, int z = a/b/c;  (valid)
vi) any number of variables can be output in cout statement
    cout << x << y << z;
vii)cout will only display variable values not additional string like
    cout << x << y;   (valid)
    cout << x << "and" << y (invalid)
viii)if a variable is not initialized and is used in print statement then it will give error
     int a = 5;
     cout << a << b;  (invalid as b has no value)
ix) division gives ceil integer answer 
    int a = 2/5;      // a = 0
x)  division by 0 returns error and exits function
    int a=10, int b=2, int c=5;
    int x = a/(b/c);     // output: cannot divide by 0
xi) var is [_a-zA-Z][_a-zA-Z0-9]*
xii)always end statement with ;



  
