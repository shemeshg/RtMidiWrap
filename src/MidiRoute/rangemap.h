#ifndef RANGEMAP_H
#define RANGEMAP_H
#include <vector>
#include <map>

namespace MidiRoute {
class RangeMap{
public:
    int H_BOUND=0;
    std::map<int,int> rangeMap;


    //default all
   RangeMap(int hBound){
    H_BOUND = hBound;
    resetAll();
   }

   void resetAll(){
       for(int i=0;i<=H_BOUND;i++){
           rangeMap[i] = i;
       }
   }



   void set(int i){
       rangeMap[i] = i;
   }

   void set(int from, int to){
           rangeMap[from] = to;
   }

  void set(int fromLBount, int fromHBound, int toLBound){
      mapFromToRange(fromLBount, fromHBound, toLBound, toLBound + (fromHBound - fromLBount) );
  }

  void set(int fromLBount, int fromHBound, int toLBound, int toHBound){
      mapFromToRange(fromLBount, fromHBound, toLBound, toHBound );
  }

   void clear(){
       for(int i=0;i<=H_BOUND;i++){
           rangeMap[i] = -1;
       }
   }

   int getVal(int i){
       return rangeMap[i];
   }

   bool isInRange(int i){
       return rangeMap[i] != -1;
   }

   void mapFromToRange(float fromLBount, float fromHBound, float toLBound, float toHBound){
       for(float i=fromLBount;i<=fromHBound;i++){
           int dest = (( i -fromLBount)/(fromHBound-fromLBount)  )*(toHBound-toLBound)+toLBound;
           rangeMap[i] = dest;
       }
   }
};

RangeMap setRangeMapObject(std::vector<int> &jv, RangeMap &rm);

}





#endif // RANGEMAP_H
