# Code Review 

1.MUST
   1.  line 17   buffer overflow risk due to strcpy() 
   2.  line 18   malloc is  used without  null check 
   3.  line 19   for loop run i<=4 for array of 4 causes out of bound error
   4.  line 26   no break statement in switch  
   5.  line 32    allocated  memory is not  freed 

#2.Should
   1. line 4  cnt should follow global variable naming convention g_ Count 
   2. line 5  unsafe macro definition (without brackets)
   3. line 7  naming should follow snake_case 
   4. line 20,25,26   magic numbers
   5. line 27  no default case in switch 
   6. line 23  no  braces aroung if statement 
   7. line 7   no fixed width integer types
#3.Nit 
     no proper comments 
     no proper braces and spaces 
   
