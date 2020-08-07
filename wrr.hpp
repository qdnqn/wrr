#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <limits>
#include <initializer_list>
#include <cmath>
#include "fq.hpp"

class WRR{
  private:
    std::vector<FairQueue*> f_queues;
    std::vector<Packet> packets;
    std::vector<float> weights;
    std::vector<int> queues_per_class;
  public:
    WRR(std::initializer_list<float> ws) : weights(ws){
      int i;
      
      for(i=0; i<weights.size(); i++){
  		  f_queues.push_back(new FairQueue());
  		  f_queues.back()->addQueue(new Queue);
  		  
  		  std::cout << "Added fqueue " << i << "!" << std::endl;
  	  }
      
      std::cout << "Added queues and classes to WRR!" << std::endl;
    };
    
    void receive(Packet p){
	   p.queue_id -= 1;
     packets.push_back(p);
    };
    
    void process(){
		 int i;

  		for(i=0; i<packets.size(); i++){
  			if(packets[i].queue_id >= f_queues[packets[i].class_id-1]->sizeQueues()){
  				int j;

  				for(j=0; j<1+packets[i].queue_id-f_queues[packets[i].class_id-1]->sizeQueues();j++){
            f_queues[packets[i].class_id-1]->addQueue(new Queue);
  				}
  			}
  		}

      for(i=0; i<packets.size(); i++){
        f_queues[packets[i].class_id-1]->receive(packets[i]);
      }
  	}
    
    int send(){
		int i,j, numOfPackets, flg = 0;
		
		for(i=0; i<weights.size(); i++){
			if(f_queues[i]->packetNumber() > 0){
				flg =1;
				
				numOfPackets = std::floor(weights[i]*f_queues[i]->packetNumber());
								
				if(numOfPackets < 1)
					numOfPackets = 1;
								
				for(j=0; j<numOfPackets; j++){
					f_queues[i]->send();
				}
			}
		}		
		
		if(flg == 0)
			return -1;
		else
			return 0;
	}
};
