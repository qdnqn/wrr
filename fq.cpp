#include <iostream>
#include "fq.hpp"

int main(){
  Queue q1, q2, q3;
  
  FairQueue fq({q1, q2, q3},{0,0,0}, 3);

  Packet p1{1,1000, 1, 0};
  Packet p2{2,1000, 1, 0};
  Packet p3{3,300, 2, 0};
  Packet p4{4,300, 2, 0};
  Packet p11{11,1000, 3, 0};
  Packet p5{5,300, 2, 0};
  Packet p6{6,300, 2, 0};
  Packet p7{7,300, 2, 0};
  Packet p8{8,300, 2, 0};
  Packet p9{9,300, 2, 0};
  Packet p10{10,300, 2, 0};
  Packet p12{12,1000, 3, 0};
  Packet p13{13,1000, 3, 0};

  fq.receive(p1);
  fq.receive(p2);
  fq.receive(p3);
  fq.receive(p4);
  fq.receive(p5);
  fq.receive(p6);
  fq.receive(p7);
  fq.receive(p8);
  fq.receive(p9);
  fq.receive(p11);
  fq.receive(p12);
  fq.receive(p13);

  while(fq.send() != -1){}

  std::cout << "Queue is clear." << std::endl;

  return 0;

}


