#ifndef TEST__OUTPUT
#define TEST__OUTPUT

#include <iostream>
#include <sstream>

#include <vector>
#include <deque>

UInt_t DebugTest(Int_t newLevel = -1) {
   static Bool_t debugLevel = 0;
   if (newLevel>=0) debugLevel = newLevel;
   return debugLevel;
}

void Unsupported(const std::string &what) {
   std::cerr << "ROOT " << ROOT_RELEASE << " does not support "
             << what << std::endl;
}

void TestError(const std::string &test, const char *msg) {
   std::cerr << "Error for '" << test << "' : " << msg << "\n";
}

void TestError(const std::string &test, const std::string &msg) {
   TestError(test,msg.c_str());
}

template <class T> void TestError(const std::string &test, 
                                  const std::vector<T> &/*orig*/, 
                                  const std::vector<T> &/*copy*/) {
   TestError(test,"Containers are not equivalent! See previous errors");
}

template <class T> void TestError(const std::string &test, 
                                  std::vector<T> *orig, 
                                  std::vector<T> *copy) {
   TestError(test,"Containers are not equivalent! See previous errors");
}

template <class T> void TestError(const std::string &test, 
                                  const std::deque<T> &/*orig*/, 
                                  const std::deque<T> &/*copy*/) {
   TestError(test,"Containers are not equivalent! See previous errors");
}

template <class T> void TestError(const std::string &test, 
                                  std::deque<T> *orig, 
                                  std::deque<T> *copy) {
   TestError(test,"Containers are not equivalent! See previous errors");
}

void TestError(const std::string &test, const Helper &orig, const Helper &copy) {
   TestError(test, Form("Helper object wrote %d and read %d\n",
                        orig.val,copy.val));
}

const char* GetEHelperStringValue(const EHelper &eval) {
   switch(eval) {
      case kZero: return "kZero";
      case kOne:  return "kOne";
      case kTwo:  return "kTwo";
      case kEnd:  return "kEnd";
      default:    return "unknown val";
   }
}
void TestError(const std::string &test, const EHelper &orig, const EHelper &copy) {
   std::stringstream s;
   s << "We wrote: " << GetEHelperStringValue(orig) 
     << " but read " << GetEHelperStringValue(copy) << std::ends;
   TestError(test, s.str());
}

void TestError(const std::string &test, const THelper &orig, const THelper &copy) {
   TestError(test, Form("THelper object wrote %d and read %d\n",
                        orig.val,copy.val));
}

void TestError(const std::string &test, const TNamed &orig, const TNamed &copy) {
   std::stringstream s;
   s << "We wrote: name=" << orig.GetName() << " title=" << orig.GetTitle() << " but read " 
     << "name=" << copy.GetName() << " title=" << copy.GetTitle() << std::ends;
   TestError(test, s.str());
}

template <class T> void TestError(const std::string &test, const T &orig, const T &copy) {
   std::stringstream s;
   s << "We wrote: " << orig << " but read " << copy << std::ends;
   TestError(test, s.str());
}

/*
void TestError(const std::string &test, Helper* orig, Helper* copy) {
   if (orig==0 || copy==0) {
      TestError(test,Form("For Helper, non-initialized pointer %p %p",orig,copy));
   } else {
      TestError(test, *orig, *copy); 
   }
}
*/

template <class T> void TestError(const std::string &test, T* orig, T* copy) {
   TClass *cl = gROOT->GetClass(typeid(T));
   const char* classname = cl?cl->GetName():typeid(T).name();   
   
   if (orig==0 || copy==0) {
      TestError(test,Form("For %s, non-initialized pointer %p %p",classname, orig,copy));
   } else {
      TestError(test, *orig, *copy); 
   }
}

#endif // TEST__OUTPUT
