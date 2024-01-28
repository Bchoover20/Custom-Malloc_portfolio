// This adds coalescing of free blocks.
// Improves performance to 54/100 ... takes less time.

//
// Test Build Trig Sig Phi
//

/*-------------------------------------------------------------------
 *  Malloc Lab Starter code:
 *        single doubly-linked free block list with LIFO policy
 *        with support for coalescing adjacent free blocks
 *
 * Terminology:
 * o We will implement an explicit free list allocator.
 * o We use "next" and "previous" to refer to blocks as ordered in
 *   the free list.
 * o We use "following" and "preceding" to refer to adjacent blocks
 *   in memory.
 *-------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"

/* Macros for unscaled pointer arithmetic to keep other code cleaner.
   Casting to a char* has the effect that pointer arithmetic happens at
   the byte granularity (i.e. POINTER_ADD(0x1, 1) would be 0x2).  (By
   default, incrementing a pointer in C has the effect of incrementing
   it by the size of the type to which it points (e.g. Block).)
   We cast the result to void* to force you to cast back to the
   appropriate type and ensure you don't accidentally use the resulting
   pointer as a char* implicitly.
*/
#define UNSCALED_POINTER_ADD(p, x) ((void*)((char*)(p) + (x)))
#define UNSCALED_POINTER_SUB(p, x) ((void*)((char*)(p) - (x)))


/******** FREE LIST IMPLEMENTATION ***********************************/


/* An BlockInfo contains information about a block, including the size
   as well as pointers to the next and previous blocks in the free list.
   This is similar to the "explicit free list" structure illustrated in
   the lecture slides.

   Note that the next pointer are only needed when the block is free. To
   achieve better utilization, mm_malloc should use the space for next as
   part of the space it returns.

   +--------------+
   |     size     |  <-  Block pointers in free list point here
   |              |
   |   (header)   |
   |              |
   |     prev     |
   +--------------+
   |   nextFree   |  <-  Pointers returned by mm_malloc point here
   |   prevFree   |
   +--------------+      (allocated blocks do not have a 'nextFree' field)
   |  space and   |      (this is a space optimization...)
   |   padding    |
   |     ...      |      Free blocks write their nextFree/prevFree pointers in
   |     ...      |      this space.
   +--------------+

*/
typedef struct _BlockInfo {
  // Size of the block and whether or not the block is in use or free.
  // When the size is negative, the block is currently free.
  long int size;
  // Pointer to the previous block in the list.
  struct _Block* prev;
} BlockInfo;

/* A FreeBlockInfo structure contains metadata just for free blocks.
 * When you are ready, you can improve your naive implementation by
 * using these to maintain a separate list of free blocks.
 *
 * These are "kept" in the region of memory that is normally used by
 * the program when the block is allocated. That is, since that space
 * is free anyway, we can make good use of it to improve our malloc.
 */
typedef struct _FreeBlockInfo {
  // Pointer to the next free block in the list.
  struct _Block* nextFree;
  // Pointer to the previous free block in the list.
  struct _Block* prevFree;
} FreeBlockInfo;

/* This is a structure that can serve as all kinds of nodes.
 */
typedef struct _Block {
  BlockInfo info;             // the payload
  FreeBlockInfo freeNode;
} Block;

/* Pointer to the first FreeBlockInfo in the free list, the list's head. */
static Block* free_list_head = NULL;
static Block* malloc_list_tail = NULL;

static int length = 0;

static size_t heap_size = 0;


/* Size of a word on this architecture. */
#define WORD_SIZE sizeof(void*)

/* Alignment of blocks returned by mm_malloc.
 * (We need each allocation to at least be big enough for the free space
 * metadata... so let's just align by that.)  */
#define ALIGNMENT (sizeof(FreeBlockInfo))


// Prototypes ::::

/* This function will have the OS allocate more space for our heap.
 *
 * It returns a pointer to that new space. That pointer will always be
 * larger than the last request and be continuous in memory.
 */
void* requestMoreSpace(size_t reqSize);

/* This function will get the first block or returns NULL if there is not
 * one.
 *
 * You can use this to start your through search for a block.
 */
Block* first_block();

/* This function will get the adjacent block or returns NULL if there is not
 * one.
 *
 * You can use this to move along your malloc list one block at a time.
 */
Block* next_block(Block* block);

/* Use this function to print a thorough listing of your heap data structures.
 */
void examine_heap();

/* Checks the heap for any issues and prints out errors as it finds them.
 *
 * Use this when you are debugging to check for consistency issues. */
int check_heap(); 




Block* searchList(size_t reqSize) {
  Block* ptrFreeBlock = first_block(); // if first block is null list is empty
   long int checkSize = -reqSize;         

  // ptrFreeBlock will point to the beginning of the memory heap!
  // end will point to the end of the memory heap.
  //
  // You want to go through every block until you hit the end.
  // Make sure you read the explanation for the next_block function above.
  // It should come in handy!

  // need to use check size

  /**
   *    // check if size is less than  0
        // is it able to fit inside of our hypothetical block

      
  */

 if (reqSize <= 0) {

  return NULL;
 }

  if (ptrFreeBlock != NULL) {   // gets the first block in the heap or returns NULL if its not there

    
    // do nothing
    int enoughSpace = 0;
    int counter = 0;
    while (enoughSpace == 0 && ptrFreeBlock != NULL) {

      
      // make sure the data has not been previously allocated and also that there is enough space in the hypothetical block (might need to be req size)
      if (ptrFreeBlock->info.size <= checkSize) {


        // conditions met return the pointer to be used in malloc
        enoughSpace = 1;
        return ptrFreeBlock;

      }
      else {

      counter++;
      ptrFreeBlock = next_block(ptrFreeBlock); // go through the heap until enough space is found
    //  printf("iterating through heap %d", counter);
      }

      
      
    }


  }


  // how to iterate, how to know if your at the end 

  /**********************************************/
  // When you are ready, you can implement the free list.
  // calculate address and pass it in to the add sizeof(blockInfo) + payload 
 
  // how do you know that you reach the end --- the address where Im at > end of the heap 
  // beggining of the heap + heap size, 


  // To begin, you can ignore the free list and just go through every single
  // block in your memory looking for a free space big enough.
  //
  // Return NULL when you cannot find any available node big enough.
  /*************************************/


  return ptrFreeBlock; // return a Block* pointer that could be NULL
}

/* Find a free block of at least the requested size in the free list.  Returns
   NULL if no free block is large enough. */
Block* searchFreeList(size_t reqSize) {
  Block* ptrFreeBlock = free_list_head;
  long int checkSize = -reqSize;

  //
  // YOUR CODE HERE! dang I thought this was given 
  //

  

  return NULL;
}

// TOP-LEVEL ALLOCATOR INTERFACE ------------------------------------ do I need to initialize with an init

/* Allocate a block of size size and return a pointer to it. If size is zero,
 * returns null.
 */
void* mm_malloc(size_t size) {
  Block* ptrFreeBlock = NULL;
  Block* splitBlock = NULL;
  long int reqSize;

  // Zero-size requests get NULL.
  if (size == 0) {
    return NULL;
  }



  // do an init call to initalize the data on the first go... in searchList or malloc?
  // node should be created here right?


  // Determine the amount of memory we want to allocate
  reqSize = size;

  // Round up for correct alignment
  reqSize = ALIGNMENT * ((reqSize + ALIGNMENT - 1) / ALIGNMENT);



  // first step is to search the malloc list aka the heap for an empty block of sufficient size 
  // if searchList returns null, its rather the start of the LL or there is no room 
  
  ptrFreeBlock = searchList(reqSize);

  if (ptrFreeBlock == NULL) { // search list returned null and its not the start of the list 
    
    // not enough room in the heap 
    //printf("          Not enough room in heap  "); // and this causes malloc to fail? 
 


  // subtract by the size of block info
  // if you can split it, split it,

  // if you cannot, allocate it 
  ptrFreeBlock = requestMoreSpace(reqSize + sizeof(BlockInfo));

    
  // else execute the add blocks 

  //printf("length is: %d", length);
  //printf(" Beggining of the list! - only print once");
  length++;

  // ptrFreeBlock is Null what do I do, request size? 
  
  // Allocation?
  ptrFreeBlock->info.size = reqSize; // since it is going to be filled (allocated) maybe I should make it negative
  // printf("      Space Found, the size of node %d", ptrFreeBlock->info.size); // should match?

  // THEN I can make the pointer point to the old tail pointer which is a prev block in the list // before tail gets updated
  ptrFreeBlock->info.prev = malloc_list_tail;


  // tail is moved now at start of block that was returned by searchList
  malloc_list_tail = ptrFreeBlock; 

  // ask the OS for more space using the function request more space --- it request more space 


  // allocate! 
  //.info.size = newBlock.info.size * -1; 
  // block info contains a size and a pointer
  
 
  // you dont want to reset the linked list, but if it has no space
  // then return null but how do you get it going, move tail
    
    
  }

else{
  // ALLOCATE 

  int prevSignError = ptrFreeBlock->info.size; // so save temp to check compare if 

//  printf("This will show if its negative or not %d \n", ptrFreeBlock->info.size);   

  ptrFreeBlock->info.size = ptrFreeBlock->info.size * -1;   // is it you? 


  // save the extra space to the second node instead of ptrFreeBlock


  // if the size of the payload is greater than reqSize plus sizeof(BlockInfo), then split it into two, reqSize is always gonna be pos right?
  if (ptrFreeBlock->info.size > reqSize + sizeof(BlockInfo)) {

    // printf("SPLIT \n");
    // printf("This will show if its negative or not %d \n", ptrFreeBlock->info.size);  
    // SPLIT


    // need to save the leftover into WOWOWOW 
   

    // size is adjusted 
    Block *newBlock = (Block*)UNSCALED_POINTER_ADD(ptrFreeBlock, (sizeof(BlockInfo)+reqSize)); // bringing you to 40
    
    newBlock->info.size =  (ptrFreeBlock->info.size - (reqSize + sizeof(BlockInfo))); // the size should just be the size of the payload but still need to sub

    ptrFreeBlock->info.size = (reqSize);  // size of payload since you are saving and returning that first node
 
    // need to grab the nextBlocks ptr , what if its NULL, and what about tail? dont mess with tail because it will always be at the end since it is only being updated when you add new block



    // 'freeing' it , making it negative
    newBlock->info.size = newBlock->info.size * -1;



    Block *nextBlock = next_block(ptrFreeBlock);



    if (nextBlock != NULL) {

      nextBlock->info.prev = newBlock; // sending the pointer back (arch)

      newBlock->info.prev = ptrFreeBlock; // sending the pointer back (arch) 
    }
    else { // nextblock was null update tail 

   
      malloc_list_tail = newBlock;

      newBlock->info.prev = ptrFreeBlock;

    }



  }


  // which one should it be returning, it should be ptrFreeBlock because it could be split again and it works with the if conditional
  Block *payload = (Block*)UNSCALED_POINTER_ADD(ptrFreeBlock, sizeof(BlockInfo));
  
 // printf("12345678 \n");
  return payload;
  // return payload but instead freePtrBlock with the unscaled 
}

  Block *payload = (Block*)UNSCALED_POINTER_ADD(malloc_list_tail, sizeof(BlockInfo));   // do we like payload 
  

  /** 
   * Step Num 1: Allocate
   * Step Num 2: Make prev point to Tail (current)
   * Step Num 3: Point tail to New Node
   * Step Num 4: Initialize the size
  */

  //examine_heap(); //see how it runs without it 
 // check_heap();


/******************************************************/
   //
   // Remember to maintain your free_list_head
   //

  /******************************************************/

  // When you are ready to implement a free list, remove the searchList call
  // and uncomment the searchFreeList call below it.
  //ptrFreeBlock = searchList(reqSize);
  //ptrFreeBlock = searchFreeList(reqSize);

  // ptrFreeBlock is either NULL (no room left) or a currently free block

  return payload;
}

void coalesce(Block* blockInfo) {               // start of entire block (blockInfo)
  Block* nextBlock = next_block(blockInfo);
  Block* previousBlock = blockInfo->info.prev;  //  
  Block* tmpBlock = NULL;                       // block is going to be saved 


  int sizeAdder = 0;
  int singleMerge = 0;



  if (previousBlock != NULL) {  // if previous block is not NULL, but what if it is null 


      if (previousBlock->info.size > 0) { // previousBlock is allocated dont touch it 

        singleMerge = 1;
      }
      else { // previousBlock is free

        singleMerge = 0; 
      }
  
  }
  else {  // previousBlock is NULL so dont touch it 

    singleMerge = 1;
  }
  
  // if your overlapping its probably because your signage is wrong

  if (blockInfo->info.size < 0) { // I mean this will always pass as true (if blockInfo is free, add the size of it plus the size of header)

           sizeAdder += blockInfo->info.size * -1;  // this is the value of BlockInfo payload (made pos)
           sizeAdder += sizeof(BlockInfo);          // might need to be sizeOf but you know its 16 ...sizeof(blockInfo)

  }
  
  
  if (nextBlock != NULL) {  // if nextblock is not Null

    
    if (nextBlock->info.size < 0) {     // if the next block is free  
  
    // then add size of header to sizeAdder but the next

      sizeAdder += sizeof(BlockInfo);                 // adding size of header for nextBlock
      sizeAdder += (nextBlock->info.size * -1);       // and the size of the payload in nextBlock, num will come out negative since it is free 

      // I need to find the next block make sure its not null and then link the prev to to the start of tempBLock to skip over the colesced block

      if (singleMerge == 0) { // if previus block is not null then work with previous block
        
          // might give a seg fault if the next block is null, is okay as long as you are not using nextBlock anymore
          if (next_block(nextBlock) != NULL) {

            nextBlock = next_block(nextBlock);       // next block is what will be colesced start of the 
       
            nextBlock->info.prev = previousBlock;    // looking to just try to avoid seg fault and get a good colesce
            
           // printf("1 \n");
            // updating that pointer, linking back but skipping over the node we are colescing 
           
          }
          else { // the subsequent nextBlock is null so just link with the current nextBlock that is not null
           
            // do not skip next is null 
            nextBlock->info.prev = previousBlock;  // GIANT LINK BACK,, was previousBLock
           // printf("12 \n");
          }
 
          if (sizeAdder > 0) {

            sizeAdder = sizeAdder * -1;
          }

          previousBlock->info.size += sizeAdder; // adding the length of the newly merged free block was previousBlock

          nextBlock->info.prev = previousBlock; // // delete
          // currently not storing the header
      }
      else {  // singleMerge = 1; // will not trigger yet 
 
          // previousBlock is already allocated merge to blockInfo
          if (next_block(nextBlock) != NULL) {
            
  
            nextBlock = next_block(nextBlock);  // moving to the next one
            nextBlock->info.prev = blockInfo;    // updating that pointer, linking back but skipping over the node we are colescing 

         //   printf("123 \n");
          }
          else {

            nextBlock->info.prev = blockInfo;
          }

     
          if (sizeAdder > 0) {

           sizeAdder = sizeAdder * -1;
          }
          // I can not figure out if this is supposed to be previousBlock or blockInfo 
          blockInfo->info.size += sizeAdder; // adding the length of the newly merged free block 

          blockInfo->info.prev = previousBlock; // delete this obvi
          
      }
 
    } 
    else { // nextBlock is allocated but previous BLock is free

      if (singleMerge == 0) {
        
        // then merge blockInfo with previous block 

        // dont need to do another next block since it is already allocated, so just link back to previous 
        nextBlock->info.prev = previousBlock; 


        if (sizeAdder > 0) {

        sizeAdder = sizeAdder * -1;
        }
        // you caused the seg fault 
       // printf("1234 \n");

        previousBlock->info.size += sizeAdder;

        

        
        
      }

    }

    // if nextBlock is allocated then that if conditional fails 
    // then just merge an

  }

 // examine_heap();

  
 

  // You can change or remove the declarations
  // above.  They are included as minor hints.
}

/* Free the block referenced by ptr. */
void mm_free(void* ptr) {   

  // pointer is pointing to payload --- free is doing weird things right now

  // subtract from pointer to get to the header with the meta data --- does it need to be changed
  Block* blockInfo = (Block*)UNSCALED_POINTER_SUB(ptr, sizeof(BlockInfo));

  // cast it to a block it is now a block, does that pointer sub work above?

  blockInfo->info.size = blockInfo->info.size * -1; // making it negative freeing it - deallocating

  // You can change or remove the declarations
  // above.  They are included as minor hints.
  //
  // Remember to maintain your free_list_head
  
   //examine_heap();
  // When you are ready... you will want to implement coalescing:
  coalesce(blockInfo);

  
   //  examine_heap(); // do a check and examine on small test's that are passing post coalesce
   //  check_heap();
}

// PROVIDED FUNCTIONS -----------------------------------------------
//
// You do not need to modify these, but they might be helpful to read
// over.

/* Get more heap space of exact size reqSize. */  // given
void* requestMoreSpace(size_t reqSize) {
  void* ret = UNSCALED_POINTER_ADD(mem_heap_lo(), heap_size);
  heap_size += reqSize;

  void* mem_sbrk_result = mem_sbrk(reqSize);
  if ((size_t)mem_sbrk_result == -1) {
    printf("ERROR: mem_sbrk failed in requestMoreSpace\n");
    exit(0);
  }

  return ret;
}

/* Initialize the allocator. */
int mm_init() {
  free_list_head = NULL;
  malloc_list_tail = NULL;
  heap_size = 0;

  return 0;
}

/* Gets the first block in the heap or returns NULL if there is not one. */
Block* first_block() {
  Block* first = (Block*)mem_heap_lo();
  if (heap_size == 0) {
    return NULL;
  }

  return first;
}

/* Gets the adjacent block or returns NULL if there is not one. */
Block* next_block(Block* block) {
  size_t distance = (block->info.size > 0) ? block->info.size : -block->info.size;

  // doing these maths and then checking you are ahead

  Block* end = (Block*)UNSCALED_POINTER_ADD(mem_heap_lo(), heap_size);
  Block* next = (Block*)UNSCALED_POINTER_ADD(block, sizeof(BlockInfo) + distance);
  if (next >= end) {
    return NULL;
  }

  return next;
}

/* Print the heap by iterating through it as an implicit free list. */
void examine_heap() {
  /* print to stderr so output isn't buffered and not output if we crash */
  Block* curr = (Block*)mem_heap_lo();                                                  // first pointer in the LL
  Block* end = (Block*)UNSCALED_POINTER_ADD(mem_heap_lo(), heap_size);                  // mem_heap_lo is an internal lib func that finds the start of the heap
  fprintf(stderr, "heap size:\t0x%lx\n", heap_size);
  fprintf(stderr, "heap start:\t%p\n", curr);
  fprintf(stderr, "heap end:\t%p\n", end);

  fprintf(stderr, "free_list_head: %p\n", (void*)free_list_head); // this should be null (nil);

  fprintf(stderr, "malloc_list_tail: %p\n", (void*)malloc_list_tail); // this should not be null (This should be at the end of the linked list)

  while(curr && curr < end) {
    /* print out common block attributes */
    fprintf(stderr, "%p: %ld\t", (void*)curr, curr->info.size);

    /* and allocated/free specific data */
    if (curr->info.size > 0) {
      fprintf(stderr, "ALLOCATED\tprev: %p\n", (void*)curr->info.prev);
    } else {
      fprintf(stderr, "FREE\tnextFree: %p, prevFree: %p, prev: %p\n", (void*)curr->freeNode.nextFree, (void*)curr->freeNode.prevFree, (void*)curr->info.prev);
    }

    curr = next_block(curr);
  }
  fprintf(stderr, "END OF HEAP\n\n");

  curr = free_list_head;
  fprintf(stderr, "Head ");
  while(curr) {
    fprintf(stderr, "-> %p ", curr);
    curr = curr->freeNode.nextFree;
  }
  fprintf(stderr, "\n");
}

/* Checks the heap data structure for consistency. */
int check_heap() {
  Block* curr = (Block*)mem_heap_lo();
  Block* end = (Block*)UNSCALED_POINTER_ADD(mem_heap_lo(), heap_size);
  Block* last = NULL;
  long int free_count = 0;

  while(curr && curr < end) {
    if (curr->info.prev != last) {
      fprintf(stderr, "check_heap: Error: previous link not correct.\n");
      examine_heap();
    }

    if (curr->info.size <= 0) {
      // Free
      free_count++;
    }

    last = curr;
    curr = next_block(curr);
  }

  curr = free_list_head;
  last = NULL;
  while(curr) {
    if (curr == last) {
      fprintf(stderr, "check_heap: Error: free list is circular.\n");
      examine_heap();
    }
    last = curr;
    curr = curr->freeNode.nextFree;
    if (free_count == 0) {
      fprintf(stderr, "check_heap: Error: free list has more items than expected.\n");
      examine_heap();
    }
    free_count--;
  }

  return 0;
}
