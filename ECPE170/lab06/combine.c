#include "config.h"
#include "vec.h"
#include "combine.h"

#include <stdio.h>

// ORIGINAL function.
// This combiner function uses the greater amount
// of abstraction to operate, but has the slowest
// performance.
void combine1(vec_ptr v, data_t *dest)
{
  printf("Running combine1() - No code-level optimizations\n");

  long int i;

  *dest = IDENT;

  for(i=0; i < vec_length(v); i++)
    {
      data_t val;
      get_vec_element(v, i, &val);
      *dest = *dest OP val;
    }

}


// CODE MOTION OPTIMIZATION:

// Move the call to vec_length() out of the loop
// because we (the programmer) know that the vector length will
// not change in the middle of the combine() function. 
//  The compiler, though, doesn't know that!
void combine2(vec_ptr v, data_t *dest)
{
  printf("Running combine2()\n");
  printf("Added optimization: Code motion\n");

  long int i, length;

  *dest = IDENT;

  length = vec_length(v);
  for(i=0; i < length; i++)
    {
      data_t val;
      get_vec_element(v, i, &val);
      *dest = *dest OP val;
    }

}


// REDUCING PROCEDURE CALLS OPTIMIZATION:

// This optimization eliminates the function call to
// get_vec_element() and accesses the data directly,
// trading off higher performance versus some loss
// of program modularity.
void combine3(vec_ptr v, data_t *dest)
{
  printf("Running combine3()\n");
  printf("Added optimization: Reducing procedure calls\n"); 


  long int i, length;

  *dest = IDENT;

  length = vec_length(v);
  for(i=0; i < length; i++)
    {
      data_t val;
	  val = v->data[i];
      *dest = *dest OP val;
    }

}


// ELIMINATING UNNEEDED MEMORY ACCESSES OPTIMIZATION:

// This optimization eliminates the trip to memory
// to store the result of each operation (and retrieve it
// the next time). Instead, it is saved in a local variable 
// (i.e. a register in the processor)
// and only written to memory at the very end.
void combine4(vec_ptr v, data_t *dest)
{
  printf("Running combine4()\n");
  printf("Added optimization: Eliminating unneeded memory accesses\n");

  long int i, length;
  data_t val = 0;
  *dest = IDENT;

  length = vec_length(v);
  for(i=0; i < length; i++)
    {
	  val = v->data[i];
    }
  *dest = *dest OP val;
}


// LOOP UNROLLING x2
// (i.e. process TWO vector elements per loop iteration)
void combine5x2(vec_ptr v, data_t *dest)
{
  printf("Running combine5x2()\n");
  printf("Added optimization: Loop unrolling x2\n");

  long int i, length;
  *dest = IDENT;

  length = vec_length(v);
  for(i=0; i < length; i+=2)
    {
	  *dest = *dest OP v->data[i];
	  *dest = *dest OP v->data[i+1];
    }

}

// LOOP UNROLLING x3
// (i.e. process THREE vector elements per loop iteration)
void combine5x3(vec_ptr v, data_t *dest)
{
  printf("Running combine5x3()\n");
  printf("Added optimization: Loop unrolling x3\n");

  long int i, length;
  *dest = IDENT;

  length = vec_length(v);
  for(i=0; i < length; i+=3)
    {
      *dest = *dest OP v->data[i];
	  *dest = *dest OP v->data[i+1];
      *dest = *dest OP v->data[i+2];
    }

}


// LOOP UNROLLING x2 + 2-way parallelism
void combine6(vec_ptr v, data_t *dest)
{
  printf("Running combine6()\n");
  printf("Added optimization: Loop unrolling x2, Parallelism x2\n");

  long int i, length;
  //*dest = IDENT;
  data_t val1 = IDENT;
  data_t val2 = IDENT;

  length = vec_length(v);
  for(i=0; i < length; i+=2)
    {
      val1 = val1 OP v->data[i];
	  val2 = val2 OP v->data[i+1];
    }

  for(; i< length; i++) 
	{
	  val1 = val1 OP v->data[i];	
	}
  *dest = val1 OP val2;
}
