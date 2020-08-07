#include <iostream>
#include "fq.hpp"
#include "wrr.hpp"

int main(){
	
  /*
   * Class weights, add as many as you want
   */
   
  WRR weightrr({0.65, 0.25, 0.1});
  
  /*
   * Packet format(Packet ID, Size in bytes, Queue_id, virtual_finish, class_id)
   * class_id 1 -> 0.65 weight
   * class_id 2 -> 0.25 weight
   * class_id 3 -> 0.1 weight
   * 
   */ 
  
  Packet p1{1,1000, 1, 0, 1};
  Packet p2{2,1000, 1, 0, 1};
  Packet p3{3,300, 2, 0, 2};
  Packet p4{4,300, 2, 0, 2};
  Packet p5{5,300, 1, 0, 1};
  Packet p6{6,300, 1, 0, 1};
  Packet p7{7,300, 2, 0, 2};
  Packet p8{8,300, 2, 0, 2};
  Packet p9{9,300, 2, 0, 2};
  Packet p11{11,1000, 1, 0, 2};
  Packet p10{10,300, 2, 0, 2};
  Packet p12{12,1000, 3, 0, 3};
  Packet p13{13,1000, 3, 0, 3};
  
  weightrr.receive(p1);
  weightrr.receive(p2);
  weightrr.receive(p3);
  weightrr.receive(p4);
  weightrr.receive(p5);
  weightrr.receive(p6);
  weightrr.receive(p7);
  weightrr.receive(p8);
  weightrr.receive(p9);
  weightrr.receive(p10);
  weightrr.receive(p11);
  weightrr.receive(p12); 
  weightrr.receive(p13);  
  
  weightrr.process();

  std::cout << std::endl << "Now sending:" << std::endl;
  std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;

  while(weightrr.send() != -1){}
    
  std::cout << "Queue is now empty." << std::endl;

  return 0;

}


