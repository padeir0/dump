
extern int a; 
// extern variables are *declared* before entering main 
// and can be accessed in other files

static int b;
// static variables or functions are *declared*
// and can be used only inside the file.
// a static variable declared inside a method
// exists beyond the calling of that method
// but only can only be accessed within the that method,
// like a private, permanent storange within a single function.



int main()
{
    register int c;
    // registers tell the compiler that the variable will
    // be heavily used, the compiler can ignore that tho
    
    return 0;
}
