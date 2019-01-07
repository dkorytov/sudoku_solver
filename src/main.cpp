

#include <iostream>
inline int indx( int i, int j){
  return i+9*j;
}

class Sudoku{
  int* data;
public:
  Sudoku(){
     data = new int[81];
     for(int i =0;i<81;++i){
       data[i]=0;
     }
  }
  void print() const{
    std::cout<<"\n"<<std::endl;
    for(int i =0;i<9;++i){
      if(i%3 == 0)
	std::cout<<"-------------------------------"<<std::endl;
      for(int j =0;j<9;++j){
	if(j%3 == 0)
	  std::cout<<"|";
	int val = data[indx(i,j)];
	if(val !=0)
	  std::cout<<" "<<val<<" ";
	else
	  std::cout<<"   ";

      }
      std::cout<<"|"<<std::endl;
    }
    std::cout<<"-------------------------------"<<std::endl;
  }
  void print_validation() const{
    std::cout<<"\n"<<std::endl;
    std::cout<<"Validation: "<<std::endl;
    std::cout<<"----------------"<<std::endl;
    std::cout<<"Num Row Col Box"<<std::endl;
    std::cout<<"----------------"<<std::endl;
    for(int i =0;i<9;++i){
      std::cout<<i<<"   "<<valid_row(i)<<"    "<<valid_column(i)<<"    "<<valid_box(i)<<std::endl;
    }
    std::cout<<"----------------"<<std::endl<<std::endl;
  }
  bool valid() const{
    bool valid = true;
    for(int i =0;i<9 && valid;++i){
      valid = valid && valid_column(i) && valid_row(i) && valid_box(i);
    }
    return valid;
  }
  bool valid_column(int j) const{
    int counts[10];
    std::fill(counts, counts+10, 0);
    for(int i=0;i<9;++i){
      counts[data[indx(i,j)]]+=1; 
    }
    return valid_counts(counts);
  }
  bool valid_row(int i) const{
    int counts[10];
    std::fill(counts, counts+10, 0);
    for(int j=0;j<9;++j){
      counts[data[indx(i,j)]]+=1; 
    }
    return valid_counts(counts);
    
  }
  bool valid_box(int box_index) const{
    return valid_box(box_index/3, box_index%3);
  }
  bool valid_box(int box_i, int box_j) const{
    int counts[10];
    box_i*=3;
    box_j*=3;
    std::fill(counts, counts+10, 0);
    for(int i =0;i<3;++i){
      for(int j =0;j<3;++j){
	counts[data[indx(box_i+i,box_j+j)]]+=1;
      }
    }
    return valid_counts(counts);
  }
  inline bool valid_counts(int* counts) const{
    for(int i=1;i<10;++i){
      if(counts[i] >= 2)
	return false;
    }
    return true;
  }
  bool complete() const{
    for(int indx =0;indx<81;++indx){
      if(data[indx] ==0)
	return false;
    }
    return true;
  }
  int find_first_empty(int start =0){
    for(int i =start;i<81;++i){
      if( data[i] == 0)
	return i;
    }
    return -1;
  }
  bool solve1(int start,  int& attempts){
    attempts +=1;
    int indx = find_first_empty(start);
    // std::cout<<"start index: "<<indx<<std::endl;
    if(indx == -1){ //All filled
      // std::cout<<"AALL filled"<<std::endl;
      return valid(); // All filled & valid = answer
    }
    // print();
    // print_validation();
    for(int i =0;i<9;++i){
      data[indx] = i+1;
      if(valid()){
	if(solve1(indx+1, attempts))
	  return true;
	  
      }
    }
    data[indx] = 0; //dead end;
    return false;
  }
  void preset1(){
    data[0]=1;
  }
  void preset2(){
    data[indx(7,0)]=2;
    data[indx(8,0)]=8;
    data[indx(0,1)]=6;
    data[indx(1,1)]=9;
    data[indx(5,1)]=7;
    data[indx(4,2)]=5;
    data[indx(5,2)]=9;
    data[indx(2,3)]=6;
    data[indx(3,3)]=9;
    data[indx(0,4)]=1;
    data[indx(1,4)]=8;
    data[indx(2,4)]=2;
    data[indx(3,4)]=6;
    data[indx(6,5)]=4;
    data[indx(0,6)]=8;
    data[indx(1,6)]=6;
    data[indx(0,7)]=7;
    data[indx(7,7)]=8;
    data[indx(8,7)]=5;
    data[indx(4,8)]=2;
    data[indx(5,8)]=5;
    data[indx(8,8)]=1;
  }
  void preset3(){
    data[indx(0,0)]=2;
    data[indx(0,1)]=1;
    data[indx(0,6)]=4;
    data[indx(1,4)]=2;
    data[indx(1,5)]=8;
    data[indx(2,6)]=1;
    data[indx(2,8)]=6;
    data[indx(3,3)]=5;
    data[indx(3,5)]=7;
    data[indx(3,6)]=6;
    data[indx(3,8)]=8;
    data[indx(4,0)]=8;
    data[indx(4,1)]=3;
    data[indx(4,8)]=7;
    data[indx(5,4)]=1;
    data[indx(5,5)]=6;
    data[indx(5,8)]=3;
    data[indx(6,1)]=4;
    data[indx(6,2)]=2;
    data[indx(6,3)]=3;
    data[indx(7,1)]=5;
    data[indx(7,2)]=3;
    data[indx(7,7)]=7;
    data[indx(8,2)]=7;
    data[indx(8,3)]=9;
  }
};

Sudoku* load(char* file_name){
  return new Sudoku();
}


int main(int argc, char** argv){
  std::cout<<"\n\nSodoku Solver"<<std::endl;
  Sudoku s;
  s.preset3();
  s.print();
  s.print_validation();
  int attempts =0;
  bool result = s.solve1(0, attempts);
  std::cout<<result<<"  attempts: "<<attempts<<std::endl;
  s.print();
}
