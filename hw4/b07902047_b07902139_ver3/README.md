# Bonus features

* **Error** messages are colored with red, while **Warning** messages are colored with purple

## Error

* Raise **function name cannot be used as rvalue** when we use function name as a rvalue, including in assignment, expression, and parameter passing.
  * `int f(int x){} int main(){ int a=f,b; b=f+1; a=-f; f(f);}`
* Raise **lvalue required as left operand of assignment** when we use function name as a lvalue.
  * `int f(int x){} int main() { f=1; }`
* Raise **variable or field '<var name>' declared void** when we declare a variable or a function parameter with void type.
  * `typedef void a; int main() { a x; }`
  * `typedef void a; int f(a x){}`
* Raise **declaration of '<array name>' as array of voids** when we declare an array of void type.
  * `typedef void a[2]; int main() { int x; }`
* Raise **incompatible type for arguments of '<func name>'** when the parameters passed into the function aren't compatible and cannot be casted, such as passing constant-string to non-string function argument.
  * `void c(int c){} int main(){ c("abc"); }`
* Raise **void value not ignored as it ought to be** when we use a void value in an expression.
  * `void f(){} int main(){ int a=1+f(); }`
* Raise **invalid use of void expression** when we use a void value in a unary operation.
  * `void f(){} int main(){ int a=!f(); }`
* Raise **'<func name>' declared as function returning an array** when we declare a function with array return type.
  * `typedef int a[2]; a f(){}`
* Raise **array size is not a constant expression** when declaring an array with a non constant expression.
  *  `int a, b[a+1], c[2/0];`

## Warning

* Prompt **division by zero** when the results of a constant expression involves division by zero.
  * `int main(){ int a=1/0; }`
* Prompt **'return' with no value, in function returning non-void** when a non-void function returns nothing(void).
  * `int f(){ return; }`
* Prompt **'return' with a value, in function returning void** when a void function returns something non-void.
  * `void f(){ int a; return a; }`

## Optimization

* Constant Folding
  * Note that our constant folding won't fold when the constant expression involves invalid operations such as division by zero.

# Basic features

* All other features mentioned in `Assignment4.docx`
