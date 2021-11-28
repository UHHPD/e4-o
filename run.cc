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
  //cout << "========Объединение векторов!=============="<< endl;

  //  cout << "========Ошибка=============="<< endl;
  datA.avg_error(datD,2, datA);
  //  cout << "========Сечения=============="<< endl;
  datA.avg_data(datD,2, datA);
  double sumchi;
  sumchi = 0;
  for (int k = 0; k < 4; k++){
     for (int i=0; i < set_data[k].size(); i++) {

         sumchi = sumchi + set_data[k].testchi (datA, i);

     }
     double itogchi = sumchi / 52 ;
     cout << itogchi << endl;
     sumchi = 0;
  }
  //AB
  std:: vector <double> errorAB(datA.size());
  std:: vector <double> dataAB(datA.size());
  //std:: vector <double> sredn(4);
  std:: vector <double> binsAB(datA.size());
  // CD
  std:: vector <double> errorABC(datA.size());
  std:: vector <double> dataABC(datA.size());
  std:: vector <double> binsABC(datA.size());
  // ABCD 
  std:: vector <double> errorABCD(datA.size());
  std:: vector <double> dataABCD(datA.size());
  std:: vector <double> binsABCD(datA.size());
  std:: vector <double> funcABCD(datA.size());
  std:: vector <double> binABCD(datA.size());


   // Sum of vectors AB
  for (int i=0; i<56; i++) {
    //cout << "================================= " << i<< "----------------" <<endl;
     double wa = 1 / (datA.error(i)*datA.error(i));
     //cout << "wa = " << wa << "  datAerror "<< datA.error(i) <<endl;
     double wb = 1 / (datB.error(i)*datB.error(i));
    // cout << "wb = " << wb << "  datBerror "<< datB.error(i) <<endl;
     dataAB[i] = (wa * datA.measurement(i) + wb * datB.measurement(i))/(wa + wb);
    // cout <<"datA = "<< datA.measurement(i) <<"  datB = "<< datB.measurement(i) << "  Dataab i =  " << dataAB[i] <<endl;
     errorAB[i] = sqrt (1/(wa+wb));
     //cout << "error AB [i] = " << errorAB[i] <<endl;
  }
   // Sum of vectors ABC
    
  for (int i=0; i<56; i++) {
     double wab = 1 / (errorAB[i]*errorAB[i]);
     double wc = 1 / (datC.error(i)*datC.error(i));
     dataABC[i] = (wab * dataAB[i] + wc * datC.measurement(i))/(wab + wc);
     //cout << "Dataab i =  " << dataAB[i] <<endl;
     errorABC[i] = sqrt (1/(wab+wc));
     //cout << "error AB [i] = " << errorCD[i] <<endl;
  }
   // Sum of ABCD
   
  for (int i=0; i<56; i++) {
     //cout << "========================================" << i << endl;
     double wabc = 1 / (errorABC[i]*errorABC[i]);
     double wd = 1 / (datD.error(i)*datD.error(i));
     dataABCD[i] = (wabc * dataABC[i] + wd*datD.measurement(i))/(wabc + wd);
     errorABCD[i] = sqrt (1/(wabc+wd));
     binABCD[i] = datA.binLow(i);
     //cout <<"i = "<< i << " bin = " << binABCD[i]<< "dataABCD = " << dataABCD[i] <<endl; 
  }
  double alfaABCD = 0.005;
  double bettaABCD = -0.00001;
  double gammaABCD = 0.08;
  double deltaABCD = 0.015;
  //binABCD[56]=305; 
  for (int i=0; i<56; i++) {
    funcABCD[i] = alfaABCD + (bettaABCD * datA.binCenter(i)) + gammaABCD * exp((-1) * deltaABCD * datA.binCenter(i));
    cout << "I = "<< i << "Teor =   "<< funcABCD [i] <<"prakt =  " << dataABCD[i] << endl;
  }
  double sumchiABCD = 0;
  for (int i=0; i<56; i++) {
    double chiABCD = (dataABCD[i] - funcABCD[i])*(dataABCD[i] - funcABCD[i])/(errorABCD[i]*errorABCD[i]);
    sumchiABCD = sumchiABCD + chiABCD;
    
  }
  cout << sumchiABCD / 52 << endl;
  //cout << "itogchi = " << itogchi << endl;
  
  
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

  

