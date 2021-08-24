#ifndef RANGEMAP_H
#define RANGEMAP_H
#include <vector>
#include <map>
#include <math.h>

namespace MidiRoute {

class RangeDefinition {
public:
    int fromLBound = 0;
    int fromHBound = 0;
    int toLBound = 0;
    int toHBound = 0;
};

class RangeMap{
public:

    std::vector<RangeDefinition> rangeDefinitions;
    bool defaultAllMaped = true;
    //default all allowed 1==1 2==3 etc...
   RangeMap(){
   }





   void set(int i){
       RangeDefinition r;
       r.fromLBound = i;
       r.fromHBound = i;
       r.toLBound = 1;
       r.toHBound = 1;
       rangeDefinitions.push_back(std::move(r));
   }

   void set(int from, int to){
       RangeDefinition r;
       r.fromLBound = from;
       r.fromHBound = from;
       r.toLBound = to;
       r.toHBound = to;
       rangeDefinitions.push_back(std::move(r));
   }

  void set(int fromLBount, int fromHBound, int toLBound){
      RangeDefinition r;
      r.fromLBound = fromLBount;
      r.fromHBound = fromHBound;
      r.toLBound = toLBound;
      r.toHBound =  toLBound + (fromHBound - fromLBount);
      rangeDefinitions.push_back(std::move(r));
  }

  void set(int fromLBount, int fromHBound, int toLBound, int toHBound){
      RangeDefinition r;
      r.fromLBound = fromLBount;
      r.fromHBound = fromHBound;
      r.toLBound = toLBound;
      r.toHBound =  toHBound;
      rangeDefinitions.push_back(std::move(r));
  }

   void clear(){
       rangeDefinitions.clear();
       defaultAllMaped = false;

   }

   int getVal(int i){
       int ret_val = -1;
       if (defaultAllMaped) {ret_val = i;}


       for (RangeDefinition &rd : rangeDefinitions) {
           float dest  =  (( ret_val -rd.fromLBound)/(rd.fromHBound-rd.fromLBound)  )*(rd.toHBound-rd.toLBound)+rd.toLBound;
           ret_val=dest;
       }


       return ret_val;
   }

   bool isInRange(int i){
       return getVal(i) != -1;
   }


};

RangeMap setRangeMapObject(std::vector<int> &jv, RangeMap &rm);

}





#endif // RANGEMAP_H
