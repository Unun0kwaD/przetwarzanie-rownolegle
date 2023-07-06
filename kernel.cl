#define MAX_WORD_LEN 20
// Function to implement strcmp function
unsigned char *strcpy(unsigned char *destination, __global const unsigned char *source) {
  // return if no memory is allocated to the destination
  if (destination == ((void *)0)) {
    return ((void *)0);
  }

  // take a pointer pointing to the beginning of the destination string
  unsigned char *ptr = destination;

  // copy the C-string pointed by source into the array
  // pointed by destination
  while (*source != '\0') {
    *destination = *source;
    destination++;
    source++;
  }

  // include the terminating null character
  *destination = '\0';

  // the destination is returned by standard `strcpy()`
  return ptr;
}
/*
int strcmp(const char *p1,const char *p2)
{
  unsigned char *s1 = (const unsigned char *)p1;
  unsigned char *s2 = (const unsigned char *)p2;
  unsigned c1, c2;

  do {
    c1 = (unsigned char)*s1++;
    c2 = (unsigned char)*s2++;
    if (c1 == '\0')
      return c1 - c2;
  } while (c1 == c2);

  return c1 - c2;
}
*/

int strcmp(const unsigned char *X, const unsigned char *Y) {
  while (*X) {
    // if characters differ, or end of the second string is reached
    if (*X != *Y) {
      break;
    }

    // move to the next pair of characters
    X++;
    Y++;
  }

  // return the ASCII difference after converting `char*` to `unsigned char*`
  return *(const unsigned char *)X - *(const unsigned char *)Y;
}


__kernel void calculate_weight(__global const unsigned char *stra, __global int *result,
                               int len) {
  int gid = get_global_id(0);
  int dim = (int)(sqrt((float)get_global_size(0)));
  unsigned char a[MAX_WORD_LEN];
  unsigned char b[MAX_WORD_LEN];
  strcpy(a, &stra[gid % dim]);
  strcpy(b, &stra[gid / dim]);
  result[gid] = -1;
  for (int i = 1; i < len; i++) {
    b[len - i] = '\0';
    if (strcmp(&a[i], &b[0]) == 0) {
      result[gid] = i*i;
      break;
    }
  }
}
