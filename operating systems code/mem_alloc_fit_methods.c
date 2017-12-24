#include <limits.h>
#include <time.h>
#include <stdlib.h>

int num_pages = 2048;
static int free_pages_bitmap[num_pages] = {0};

/*----------------------------------------------------------------------------------------*
 First Fit
 *----------------------------------------------------------------------------------------*/
phys_clicks firstFit (phys_clicks size_in_clicks)
{
  int i;
  int n = sizeof(free_pages_bitmap) / sizeof(free_pages_bitmap[0]);
  for (i = 0; i < n; i++)
  {
    // check to see if the hole is greater than the process size
    if (free_pages_bitmap[i] > size_in_clicks)
    {
      // resize the bitmap slot for the pages
      free_pages_bitmap[i] -= size_in_clicks;
      // return the mem address
      return i
    }
  }
  return NO_MEM;
}

/*----------------------------------------------------------------------------------------*
 Next Fit
 *----------------------------------------------------------------------------------------*/
 phys_clicks nextFit (phys_clicks size_in_clicks)
 {
   int i;
   static int offset = 0;
   int n = sizeof(free_pages_bitmap) / sizeof(free_pages_bitmap[0]);
   for (i = 0; i < n; i++)
   {
     j = (i + offset) % n
     // check to see if the hole is greater than the process size
     if (free_pages_bitmap[j] > size_in_clicks)
     {
       // resize the bitmap slot for the pages
       free_pages_bitmap[j] -= size_in_clicks;
       // update offset
       offset = j;
       return j;
     }
   }
   return NO_MEM;
 }

/*----------------------------------------------------------------------------------------*
 Best Fit
 *----------------------------------------------------------------------------------------*/
phys_clicks bestFit (phys_clicks size_in_clicks)
{
  int i;
  int smallest = 0;
  bool changed = false;
  int n = sizeof(free_pages_bitmap) / sizeof(free_pages_bitmap[0]);
  for (i = 0; i < n; i++)
  {
    // check to see if the hole is greater than the process size, but smallest
    // than our current smallest
    if (free_pages_bitmap[i] > size_in_clicks &&
        free_pages_bitmap[i] <= free_pages_bitmap[smallest])
    {
      changed = true;
      smallest = i;
    }
  }
  if (changed){
    free_pages_bitmap[smallest] -= size_in_clicks;
    return smallest;
  }
  else
  {
    return NO_MEM;
  }
}

/*----------------------------------------------------------------------------------------*
 Worst Fit
 *----------------------------------------------------------------------------------------*/
phys_clicks worstFit (phys_clicks size_in_clicks)
{
 int i;
 int largest = 0;
 bool changed = false;
 int n = sizeof(free_pages_bitmap) / sizeof(free_pages_bitmap[0]);
 for (i = 0; i < n; i++)
 {
   // check to see if the hole is greater than the process size, but smallest
   // than our current smallest
   if (free_pages_bitmap[i] > size_in_clicks &&
       free_pages_bitmap[i] >= free_pages_bitmap[largest])
   {
     changed = true;
     largest = i;
   }
 }
 if (changed){
   free_pages_bitmap[largest] -= size_in_clicks;
   return largest;
 }
 else
 {
   return NO_MEM;
 }
}

/*----------------------------------------------------------------------------------------*
 Random Fit
 *----------------------------------------------------------------------------------------*/
phys_clicks randomFit (phys_clicks size_in_clicks){
  bool changed = false;
  int i;
  int j = 0;
  int n = sizeof(free_pages_bitmap) / sizeof(free_pages_bitmap[0]);
  bitchunk_t possible_holes[n];
  for (i = 0; i < n; i++)
  {
    // if a hole is big enough, add it to the list in spot j, increment j.
    if (free_pages_bitmap[i] > size_in_clicks){
      changed = true;
      possible_holes[j] = i;
      j++;
    }
  }
  if (changed)
  {
    time_t t;
    srand((unsigned) time(&t));
    int r = rand();
    int loc = possible_holes[r%j];
    free_pages_bitmap[loc] -= size_in_clicks;
    return loc;
  }
  return NO_MEM;
}
