#ifndef FQ_H
#define FQ_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <limits>
#include <initializer_list>

struct Packet {
  int id;
  int bits;
  int queue_id;
  long int virtual_finish;
  int class_id;
};

struct Queue {
  std::list<Packet> queue;
  int class_id;
};

class FairQueue{
  private:
    int queues_sz = 0;
    std::vector<Queue*> queues;
    std::vector<long int> last_virtual_finish;
    long int virtual_time = 0;
    long packets = 0;
  public:
	FairQueue(){};
    FairQueue(std::initializer_list<Queue*> qs, std::initializer_list<long int> times, int qs_sz) : queues(qs), last_virtual_finish(times){
      queues_sz = qs_sz;
      std::cout << "Added queues and last virtual times vectors!" << std::endl;
    };
    
    void addQueue(Queue *q){
  		queues_sz++;
  		queues.push_back(q);
  		last_virtual_finish.push_back(0);
  	}
	
	bool existsQueue(int id){
		if(queues.size() < id)
			return false;
			
		return true;
	}
	
	int sizeQueues(){
		return queues.size();
	}
	
	int packetNumber(){
		return packets;
	}

    void receive(Packet p){
	   packets++;     
	   queues[p.queue_id]->queue.push_back(p);
     updateVirtTime(queues[p.queue_id]->queue.back());
     std::cout << "Received packet to queue: " << p.queue_id+1 << ", Packet ID: " << p.id << ", Virtual finish: " << p.virtual_finish << ", Class: " << p.class_id << std::endl;
    };

    int send(){
      int queue = selectQueue();

      if(queues[queue]->queue.size() > 0){
        Packet p_temp = queues[queue]->queue.front();
        std::cout << "Dequeueing packet from queue: " << queue+1 << ", Packet ID: " << p_temp.id << ", Virtual finish: " << p_temp.virtual_finish << ", Class: " << p_temp.class_id << std::endl;
		virtual_time += p_temp.bits;
		
        queues[queue]->queue.pop_front();
        packets--;
        
        return queue;
      } else {
        return -1;
      }
    };
    
    int selectQueue(){
      int i = 0, queue = 0;
      long minVirFinish = std::numeric_limits<long>::max();

      while(i < queues_sz){
        if(queues[i]->queue.size() > 0 && queues[i]->queue.front().virtual_finish < minVirFinish){
          minVirFinish = queues[i]->queue.front().virtual_finish;
          queue = i;
        }

        i++;
      }

      return queue;
    };

    void updateVirtTime(Packet &p){
      int virtual_start = std::max(now(), last_virtual_finish[p.queue_id]);
      p.virtual_finish = p.bits + virtual_start;
      last_virtual_finish[p.queue_id] = p.virtual_finish;
    }
    
    long int now(){
      return virtual_time;
    }
};

#endif
