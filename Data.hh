#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>
using namespace std;

class Data {
 public:
  Data(const std::string& filename);
  int checkCompatibility(const Data& in, int n) const;
  unsigned int size() const { return m_data.size(); }
  double measurement(int i) const { return m_data[i]; }
  double binCenter(int i) const { (m_bins[i]+m_bins[i+1])/2; }
  double binLow(int i) const { return m_bins[i]; }
  double binHigh(int i) const { return m_bins[i+1]; }
  double error(int i) const { return m_errors[i]; }
  int avg_error(  const Data& in1, int n, const Data& in2) const;
  int avg_data(  const Data& in1, int n, const Data& in2) const ;
  double func (double al, double be,double ga,double delta, int i) const;
  double testchi (const Data& in3, int i) ;
  void zapisdata (int i) const; 
  

 private:
  Data() {}  // disallow empty data set
  void assertSizes();
  std::vector<double> m_data;
  std::vector<double> m_bins;
  std::vector<double> m_errors;
  
};

#endif
