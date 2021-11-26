#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <cmath>

#include "Data.hh"

// generic function comparing two values of some type T used later for int and
// double
template <class T>
bool testEqual(const std::string& name, T expected, T real) {
  if (expected != real) {
    std::cout << "(" << name << ": <" << expected << ">"
              << ", " << real << ") ";
    return false;
  }
  return true;
}

bool testReadingSize() {
  std::cout << "testReadingSize...";
  Data datA("testA");
  return testEqual<int>("size", 1, datA.size());
}

bool testReadingMeasurement() {
  std::cout << "testReadingMeasurement...";
  Data datA("testA");
  return testEqual("measurement", 10., datA.measurement(0));
}

bool testReadingBinEdges() {
  std::cout << "testReadingBinEdges...";
  Data datA("testA");
  return testEqual("bin low", 0., datA.binLow(0)) &&
         testEqual("bin high", 1., datA.binHigh(0));
}

bool testReadingErrors() {
  std::cout << "testReadingErrors...";
  Data datA("testA");
  return testEqual("error", 2., datA.error(0));
}

bool testCopyConstructor() {
  std::cout << "testCopyConstructor...";
  Data a("testA");
  Data b(a);
  Data c = a;  // equivalent to Data c(a)
  return testEqual("measurement", 10., b.measurement(0)) &&
         testEqual("measurement", 10., c.measurement(0));
}

void runTests() {
  std::cout << "running tests...\n";
  std::vector<std::function<bool()> > tests(
      {testReadingSize, testReadingMeasurement, testReadingBinEdges,
       testReadingErrors, testCopyConstructor});
  for (auto test : tests)
    std::cout << (test() ? " ok" : " FAILED!") << std::endl;
}

int main() {
  using namespace std;
std:: vector <double> sredn(4);
  cout << "******************************************************" << endl;
  runTests();
  cout << "******************************************************" << endl;
  // create an object which holds data of experiment A
  std::vector<Data> set_data; 
  std::vector<Data> avg; 
  std::vector<Data> avg1; 
  Data datA("exp_A");
  set_data.push_back(datA);
  Data datB("exp_B");
  set_data.push_back(datB);
  Data datC("exp_C");
  set_data.push_back(datC);
  Data datD("exp_D");
  set_data.push_back(datD);
  for(int i = 0; i < 4; i++) {
    std::cout<< set_data[i].measurement(27) << endl;
  }
  //d für bins 27 A und B
  double er;
  int n;
  n = 1;
  double delta = set_data[0].measurement(27) - set_data[1].measurement(27);
  if (delta < 0) {delta = delta *(-1);}
  er = sqrt((set_data[0].error(27))*(set_data[0].error(27)) + (set_data[1].error(27))*(set_data[1].error(27)))*n;
  double dyer = delta - er; 
  if (dyer < 0) { cout<<"compatible  "<< dyer << endl;}
  else { cout <<"not compatible "<< dyer << endl; }
  //copabilite for all
   n = 2;
  cout << datA.checkCompatibility(datB, n) << " data points from set A and B differ by more than " << n << " s.d." << endl;
  cout << datA.checkCompatibility(datC, n) << " data points from set A and C differ by more than " << n << " s.d." << endl;
  cout << datA.checkCompatibility(datD, n) << " data points from set A and D differ by more than " << n << " s.d." << endl;
  n = 3;
  cout << datA.checkCompatibility(datB, n) << " data points from set A and B differ by more than " << n << " s.d." << endl;
  cout << datA.checkCompatibility(datC, n) << " data points from set A and C differ by more than " << n << " s.d." << endl;
  cout << datA.checkCompatibility(datD, n) << " data points from set A and D differ by more than " << n << " s.d." << endl;
  // average 
  cout << "========Объединение векторов!=============="<< endl;

    cout << "========Ошибка=============="<< endl;
  datA.avg_error(datB,2, datA);
    cout << "========Сечения=============="<< endl;
  datA.avg_data(datB,2, datA);
  double sumchi;
  sumchi = 0;
  for (int i=0; i < datB.size()-1; i++) {

  sumchi = sumchi + datB.testchi (datB, i);

  }
  double itogchi = sumchi / 52;

  cout << "itogchi = " << itogchi << endl;
  
  }
  //summ of all cross-section
  //for(int i = 0; i < 4; i++) {
  //  std::cout<< "___________________________" << endl; 
  //   std::cout<< "файл номер  " << i << endl; 
  //  for (int k=0; k < set_data[i].size(); k++ ) {
  //   sredn[i] = set_data[i].measurement(k) + sredn[i];
  //   std::cout<< "номер   " << k << "Данное  " << set_data[i].measurement(k)  << "сумма "<< sredn[i] << endl;
  //  }
  //  std::cout<< "Для файла  " << i << "значение среднего "<< sredn[i] << endl;
  //}
  


  // here is the data from experiment A
  //cout << "bin 27: from " << datA.binLow(26) << " to " << datA.binHigh(27)
 //      << endl;
 // cout << "measurement of experiment A in bin 27: " << datA.measurement(27)
//       << endl;

  

