#ifndef __STRUCTURES_H_INCLUDED__
#define __STRUCTURES_H_INCLUDED__

#include <vector>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <utility>

using X = int;
using Y = int;

X MaskW=23;
Y MaskH=29;

// because array wants a size at compile time

//"Matrix" is a preliminary solution to later generalize the signatures
//will probably go from [][] to .at(x,y)
using matrix = std::vector<std::vector<int>>;
//ideas
//template <class T> using matrix = std::vector<std::vector<T>>;



struct point{
  X x;
  Y y;
};

struct xy_char{
  X x; //maybe better to have usign long..?
  Y y;
  char c;
  //opt padding or reduce x...?
};


//global
//std::vector<matrix> masks;

template<class M>
decltype(auto) resize_matrix(M && input, X tar_w, Y tar_h){
//decltype(auto) resize_matrix(M && input, M && res ...){
  Y cur_h=input.size();
  X cur_w=input[0].size();
//ratio only for compile time known stuff...
  double Dx = static_cast<double>(tar_w)/cur_w;
  double Dy = static_cast<double>(tar_h)/cur_h;
//  std::cout <<"cur_w:"<<cur_w<<" cur_h:"<<cur_h<<"\n";
//  std::cout <<"tar_w:"<<tar_w<<" tar_h:"<<tar_h<<"\n";
//  std::cout <<"Dx:"<<Dx<<" Dy:"<<Dy<<"\n";
  //initialize resuling matrix
  M res;
  //std::cout << "got a problem?\n";
  for (int i=0;i<tar_h;++i)
    res.push_back(std::vector<int> (tar_w));
  //res.reserve(tar_h);

  //std::transform..?
  for (int i=0;i<cur_h;++i){
    for (int j=0; j<cur_w;++j){
      //add value to corresponding element in resized matrix
      //std::cout << "adding " <<input[i][j]<<"\n";
      //fills up corresponding areas for upsizing
      for (int dx=0;dx<Dx;++dx)
        for (int dy=0;dy<Dy;++dy)
          res[i*Dy+dy][j*Dx+dx]=input[i][j];
        //accumulating solution not useful here...
        //  res[i*Dy+dy][j*Dx+dx]+=input[i][j]*Dx*Dy;
      //std::cout << "entry: " <<j*Dx <<" "<<i*Dy <<" is now " <<res[i*Dy][j*Dx]<<"\n";
    }
  }
  //average over elements
/*
  for (auto & v : res)
    for (auto & e : v)
    // smaller target has to get lower values<-> higher accumulation rate
      e=std::round(e*Dx*Dy); //Jacobi
*/
  return res;
}

#endif