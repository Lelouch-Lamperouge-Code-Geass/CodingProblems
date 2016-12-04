// Check whether a long number is power of 4 or not. Time complexity and space complexity should all be constant.

bool PowerOfFour(long number) {
  if (number<=0) return false; // Maker sure not negative or zero
  if ( number & (number-1) !=0 ) return false; // Make sure there is only one bit set
  return (0xAAAAAAAA & number) == 0 ; // 'A' bit form is 1010 <3 <3 <3
}



int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << (PowerOfFour(1) ? "TRUE" : "FALSE") << std::endl;
	std::cout << (PowerOfFour(2) ? "TRUE" : "FALSE") << std::endl;
	std::cout << (PowerOfFour(3) ? "TRUE" : "FALSE") << std::endl;
	std::cout << (PowerOfFour(4) ? "TRUE" : "FALSE") << std::endl;
	return 0;
}


