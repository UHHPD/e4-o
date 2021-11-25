#include "Data.hh"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include <cmath>
#include <vector>


using namespace std;

Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;

  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }
  for (int i = 0; i < size; ++i) {
   double error;
   file >> error;
   m_errors.push_back(error);
  }

  
  
  
  // done! close the file
  file.close();

  assertSizes();
};

void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size()); }

int Data::checkCompatibility(const Data& in, int n) const {
    int schet = 0;
    int size = in.size();
    for (int i = 0; i < size; i++){
      double delta = in.measurement(i) - m_data[i];
      if (delta<0) {delta= (-1) * delta;}
      double er = sqrt((m_errors[i] * m_errors[i]) + (in.error(i) * in.error(i)))*n;
      if (delta - er > 0) {schet = schet + 1;}
      cout << delta-er <<"------->" << schet << endl; 
      
    }
  
   return schet;
  

  
}
  int Data:: avg_error(const Data& in1, int n, const Data& in2) const {
  int p = in2.checkCompatibility(in1, n) ; 
  if (p == 0) {
     int size = in1.size();
     for (int i=0; i < size;i++ ){
       double w1 = 1 / (m_errors[i] * m_errors[i]);
       double w2 = 1 / (in1.measurement(i) * in1.measurement(i));
       double data = (w1 * m_data[i] + w2 * in1.measurement(i)) / (w1 +w2); 
       double errors = sqrt( 1 / (w1+w2));
       cout << data << endl;
     }
  
  } else { cout << "Data of  not compatibility" << p << endl;  }


}


  int Data:: avg_data(const Data& in1, int n, const Data& in2) const {
  
  int f = in2.checkCompatibility(in1, n) ; 
  if (f == 0) {
     int size = in1.size();
     for (int i=0; i < size;i++ ){
       double w1 = 1 / (m_errors[i] * m_errors[i]);
       double w2 = 1 / (in1.measurement(i) * in1.measurement(i));
       double data = (w1 * m_data[i] + w2 * in1.measurement(i)) / (w1 +w2); 
       double errors = sqrt( 1 / (w1+w2));
       cout << errors << endl;
     }

  } else { cout << "Data of  not compatibility" << f << endl;  }
 
 
}