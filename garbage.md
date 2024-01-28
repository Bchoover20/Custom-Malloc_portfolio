```Java


// having the tail be equal to the searchList return pointer might be a bad idea

  // why are we searchFreeList(reqSize);
  // why is it ptrFreeBlock


    // how much space do i need to request to OS - 16 bytes , whats the size of the header 
  // need to request 16 bytes plus the size of the header - which header, BLOCK
  // request size + blockinfo -- the size of blockinfo, ask the computer (sizeof), min size the payload should be (should be size of a free block)
  // whats the smallest size a whole block can have - (size of) blockinfo


   // malloc list_list_tail, should be pointing to the tail begins pointing to null 
  // -- begins pointing to null which is the linked list head since the linked list head is == null 
  // So the tail is pointing to null as the program begins


  // first step is to search the malloc list aka the heap for an empty block of sufficient size 
  // how do we call that, the head, the tail, how can we know where the heap starts


  // first_BLock function, wil give you a pointer to the beggingn of the heap -- get, head which is null, theres nothing to search so fail
  // this is searchList funciton --- should purely search the list
  // search for a block of size 16, didnt find because there no block so seaerch should return null 'none was found'

  
  // use PtrFreeBlock duh should it be the searchList going first I think so 


   //
  // YOUR CODE HERE!
  //

 // && length > 0


 Head
Checking mm_malloc for correctness, ERROR [trace 1, line 545]: Payload (0x7ffff6a250b0:0x7ffff6a26097) overlaps another payload (0x7ffff6a250a0:0x7ffff6a26087)


// coalesce need to help 


  //
  // YOUR CODE HERE!
  //

   // saving the initially passed in block into blockInfo 
  tmpBlock = blockInfo;