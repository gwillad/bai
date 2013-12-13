// BigAssInt
// For use in programming competitions.
// unbounded integer
// Adam Gwilliam
#include <iostream> 

size_t AZERO = '0';

size_t pow(size_t a, size_t b) {
  // calculates a^b
  size_t tot = 1;
  for (size_t i = 0; i < b; i++)
    tot *= a;
  return tot;
}

class bai {
public:
  
  bai(std::string s) {
    if (s.substr(0,1) == "-") {
      neg = true;
      val = s.substr(1);
    }
    else {
      neg = false;
      val = s;
    }
  }; 

  bai& operator+=(const bai& that) {
    //currently ignores negatives
    std::string big = val.size()>that.val.size()?val:that.val;
    std::string lil = val.size()<that.val.size()?val:that.val;
    std::string zeros(big.size() - lil.size() + 1, '0');
    lil = zeros + lil;
    big = "0" + big;
    
    int carry = 0;
    std::string s(big.size(), '0');
    bai sum(s);
    for (int i = big.size() - 1; i >= 0; i--) {
      sum.val[i] = (((big[i] - AZERO) + 
		     (lil[i] - AZERO) + 
		     carry) % 10) + AZERO;
      carry = (((big[i] - AZERO) + (lil[i] - AZERO) + carry) / 10);
    }
    if (sum.val[0] == '0')
      sum.val = sum.val.substr(1);
    val = sum.val;
    neg = sum.neg;
    return *this;
  };
  
  bai operator*(bai& that);
  bai& operator*=(bai& that);

  bai& operator++(){
    val = "0" + val;
    bool carry = true;
    for (int i = val.size() - 1; i >= 0; i--) {
      if (carry) val[i]++;
      else break;
      if (val[i] == AZERO + 10) {
	val[i] = '0';
	carry = true;
      }
      else carry = false;
    }
    if (val[0] == '0') val = val.substr(1);
    return *this;
  };

  bai operator++(int){
    bai tmp(val);
    operator++();
    return tmp;
  };

  bai& operator--(){
    bool cont = true;
    for (int i = val.size() - 1; i >=0; i--) {
      if (cont) val[i]--;
      else break;
      if (val[i] < AZERO) {
	val[i] = '9';
	cont = true;
      }
      else cont = false;
    }
    if (val[0] == '0') val = val.substr(1);
    return *this;
  };
  bai operator--(int) {
    bai tmp(val);
    operator--();
    return tmp;
  };

  bai operator-(bai& that);
  bai& operator-=(bai& that);

  void print(std::ostream & ostr){
    if (neg) {
      ostr << "-";
    }
    ostr << val << std::endl;
  }; 

  int getVal() {
    size_t n = val.size();
    int num = 0;
    for (size_t i = 0; i < n; i++) {
      num += (val[i] - AZERO) * pow(10, n-i-1);
    }
    return num;
  };


private:
  std::string val;
  bool neg;
};

inline bai operator+(bai lhs, const bai& rhs) {
  lhs += rhs;
  return lhs;
}

std::ostream& operator<<(std::ostream& ostr, bai& obj) {
  ostr << obj.getVal();
  return ostr;
};

int main() {
  bai val1("1");
  val1.print(std::cout);
  bai val2("999");
  val2.print(std::cout);
  bai val3 = val1 + val2;
  std::cout << val3 << std::endl;
  val3.print(std::cout);
  val3 += val2;
  val3.print(std::cout);
  ++val3;
  val3.print(std::cout);
  val3++;
  val3.print(std::cout);
  --val3;
  val3.print(std::cout);
  val3--;
  val3.print(std::cout);
}
